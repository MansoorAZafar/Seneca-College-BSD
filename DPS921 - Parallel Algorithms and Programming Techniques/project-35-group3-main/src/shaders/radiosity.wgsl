// Accumulation buffer (u32 atomics): R, G, B per lightmap texel per quad.
@group(1) @binding(0)
var<storage, read_write> accumulation : array<atomic<u32>>;

// Output lightmap texture.
@group(1) @binding(1)
var lightmap : texture_storage_2d_array<rgba16float, write>;

// --- Uniforms for accumulation-to-lightmap conversion -----------------------

struct Uniforms {
  accumulation_to_lightmap_scale : f32, // Scalar to convert accumulation -> lightmap
  accumulation_buffer_scale : f32,      // Buffer rescaling (prevents u32 overflow)
  light_width : f32,    // Width of the emissive light panel
  light_height : f32,   // Height of the emissive light panel
  light_center : vec3f, // Center position of the light panel
}

@group(1) @binding(2) var<uniform> uniforms : Uniforms;

override PhotonsPerWorkgroup : u32;
override PhotonEnergy : f32;

const PhotonBounces = 4;
const LightAbsorbtion = 0.5; // Fraction absorbed per bounce

// --- Radiosity compute shader: photon tracing ---------------------------------

/** Each invocation emits a photon from the light and accumulates bounce lighting. */
@compute @workgroup_size(PhotonsPerWorkgroup)
fn radiosity(@builtin(global_invocation_id) invocation_id : vec3u) {
  init_rand(invocation_id);
  photon();
}

/** Traces a single photon through the scene, accumulating energy on each bounce. */
fn photon() {
  var ray = new_light_ray();
  var color = PhotonEnergy * vec3f(1, 0.8, 0.6);

  // Cap on consecutive sphere passes per photon — protects against the
  // pathological case where a refracted ray keeps re-entering glass and we
  // never accumulate any energy.
  var transparent_passes = 0;

  for (var i = 0; i < (PhotonBounces+1); i++) {
    let hit = raytrace(ray);
    if (hit.quad == kNoHit) {
      return;
    }

    if (hit.is_sphere == 1u && transparent_passes < 4) {
      // Refract the photon through the glass sphere. Light passes through
      // without losing energy (no accumulate, no bounce consumed).
      let new_ray = refract_through_sphere(ray, hit);
      ray = new_ray;
      transparent_passes++;
      i--;
      continue;
    }
    if (hit.is_sphere == 1u) {
      // Bail out if the photon is stuck refracting — drop it.
      return;
    }

    let quad = quads[hit.quad];

    // Reflect the ray off the hit surface with some randomness.
    ray.start = hit.pos + quad.plane.xyz * 1e-5;
    ray.dir = normalize(reflect(ray.dir, quad.plane.xyz) + rand_unit_sphere() * 0.75);

    color *= quad.color;
    accumulate(hit.uv, hit.quad, color * LightAbsorbtion);
    color *= 1 - LightAbsorbtion;
  }
}

/** Refracts a photon entering and exiting a sphere; returns the outgoing ray. */
fn refract_through_sphere(in_ray : Ray, hit : HitInfo) -> Ray {
  let sphere = spheres[hit.quad];
  let ior = sphere.color_ior.w;

  var enter_dir = refract(in_ray.dir, hit.normal, 1.0 / ior);
  if (all(enter_dir == vec3f(0.0))) {
    // TIR on entry can't happen physically (air→glass), but guard anyway.
    enter_dir = reflect(in_ray.dir, hit.normal);
    return Ray(hit.pos + hit.normal * 1e-4, enter_dir);
  }

  let inside_start = hit.pos + enter_dir * 1e-4;
  var inside_hit = HitInfo();
  inside_hit.dist = 1e20;
  inside_hit.quad = kNoHit;
  inside_hit.is_sphere = 0u;
  inside_hit = intersect_ray_sphere(Ray(inside_start, enter_dir), hit.quad, inside_hit);

  if (inside_hit.quad == kNoHit) {
    return Ray(inside_start, enter_dir);
  }

  let exit_normal = -inside_hit.normal;
  var exit_dir = refract(enter_dir, exit_normal, ior);
  if (all(exit_dir == vec3f(0.0))) {
    // Total internal reflection — bounce inside, exit along reflected dir.
    exit_dir = reflect(enter_dir, exit_normal);
  }
  return Ray(inside_hit.pos + exit_dir * 1e-4, exit_dir);
}

/** Atomically adds `color` into the accumulation buffer at the given UV/quad. */
fn accumulate(uv : vec2f, quad : u32, color : vec3f) {
  let dims = textureDimensions(lightmap);
  let base_idx = accumulation_base_index(vec2u(uv * vec2f(dims)), quad);
  atomicAdd(&accumulation[base_idx + 0], u32(color.r + 0.5));
  atomicAdd(&accumulation[base_idx + 1], u32(color.g + 0.5));
  atomicAdd(&accumulation[base_idx + 2], u32(color.b + 0.5));
}

/** Returns the base element index in the accumulation buffer for a texel + quad. */
fn accumulation_base_index(coord : vec2u, quad : u32) -> u32 {
  let dims = textureDimensions(lightmap);
  let c = min(vec2u(dims) - 1, coord);
  return 3 * (c.x + dims.x * c.y + dims.x * dims.y * quad);
}

/** Creates a ray from a random point on the light panel in a random downward direction. */
fn new_light_ray() -> Ray {
  let center = uniforms.light_center;
  let pos = center + vec3f(uniforms.light_width * (rand() - 0.5),
                            0,
                            uniforms.light_height * (rand() - 0.5));
  var dir = rand_cosine_weighted_hemisphere().xzy;
  dir.y = -dir.y;
  return Ray(pos, dir);
}

// --- Accumulation -> lightmap copy shader ------------------------------------

override AccumulationToLightmapWorkgroupSizeX : u32;
override AccumulationToLightmapWorkgroupSizeY : u32;

/** Copies the atomic accumulation buffer to the lightmap texture, with optional overflow scaling. */
@compute @workgroup_size(AccumulationToLightmapWorkgroupSizeX, AccumulationToLightmapWorkgroupSizeY)
fn accumulation_to_lightmap(@builtin(global_invocation_id) invocation_id : vec3u,
                            @builtin(workgroup_id)         workgroup_id  : vec3u) {
  let dims = textureDimensions(lightmap);
  let quad = workgroup_id.z; // Workgroup Z encodes the quad index.
  let coord = invocation_id.xy;
  if (all(coord < dims)) {
    let base_idx = accumulation_base_index(coord, quad);
    let color = vec3(f32(atomicLoad(&accumulation[base_idx + 0])),
                     f32(atomicLoad(&accumulation[base_idx + 1])),
                     f32(atomicLoad(&accumulation[base_idx + 2])));

    textureStore(lightmap, coord, quad, vec4(color * uniforms.accumulation_to_lightmap_scale, 1));

    // Scale back accumulation values to prevent u32 overflow.
    if (uniforms.accumulation_buffer_scale != 1.0) {
      let scaled = color * uniforms.accumulation_buffer_scale + 0.5;
      atomicStore(&accumulation[base_idx + 0], u32(scaled.r));
      atomicStore(&accumulation[base_idx + 1], u32(scaled.g));
      atomicStore(&accumulation[base_idx + 2], u32(scaled.b));
    }
  }
}