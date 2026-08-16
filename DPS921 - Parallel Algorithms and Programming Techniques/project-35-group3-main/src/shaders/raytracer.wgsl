// Lightmap (radiosity data for each quad's surface)
@group(1) @binding(0) var lightmap : texture_2d_array<f32>;
// Sampler for the lightmap
@group(1) @binding(1) var smpl : sampler;
// Output HDR framebuffer
@group(1) @binding(2) var framebuffer : texture_storage_2d<rgba16float, write>;

override WorkgroupSizeX : u32;
override WorkgroupSizeY : u32;
override NumReflectionRays : i32;

@compute @workgroup_size(WorkgroupSizeX, WorkgroupSizeY)
fn main(@builtin(global_invocation_id) invocation_id : vec3u) {
  if (all(invocation_id.xy < textureDimensions(framebuffer))) {
    init_rand(invocation_id);

    // Compute NDC coordinates at the near and far clip planes for this pixel.
    let uv = vec2f(invocation_id.xy) / vec2f(textureDimensions(framebuffer).xy);
    let ndcXY = (uv - 0.5) * vec2(2, -2);

    // Transform back to world space to get the ray origin and direction.
    var near = common_uniforms.inv_mvp * vec4f(ndcXY, 0.0, 1);
    var far = common_uniforms.inv_mvp * vec4f(ndcXY, 1, 1);
    near /= near.w;
    far /= far.w;

    let ray = Ray(near.xyz, normalize(far.xyz - near.xyz));
    let hit = raytrace(ray);

    var color : vec3f;
    if (hit.quad == kNoHit) {
      color = vec3f(common_uniforms.miss_brightness);
    } else if (hit.is_sphere == 1u) {
      color = shade_glass(ray, hit);
    } else {
      color = shade_quad(ray, hit);
    }

    textureStore(framebuffer, invocation_id.xy, vec4(color, 1));
  }
}

/** Shades a ray–quad hit: lightmap + emissive + jittered metallic reflections. */
fn shade_quad(ray : Ray, hit : HitInfo) -> vec3f {
  let hit_color = sample_hit(hit);
  let quad = quads[hit.quad];
  let normal = quad.plane.xyz;
  let metallic = quad.material.x;
  let roughness = quad.material.y;

  // fire jittered reflection rays and average them.
  let bounce = reflect(ray.dir, normal);
  var reflection : vec3f;
  for (var i = 0; i < NumReflectionRays; i++) {
    // roughness controls how wide the jitter cone is
    let reflection_dir = normalize(bounce + rand_unit_sphere() * roughness);
    let reflection_ray = Ray(hit.pos + bounce * 1e-5, reflection_dir);
    let reflection_hit = raytrace(reflection_ray);
    // Reflection rays that land on the glass sphere need full glass shading,
    // otherwise the sphere appears as a flat white blob in mirror surfaces.
    if (reflection_hit.quad == kNoHit) {
      // missed
    } else if (reflection_hit.is_sphere == 1u) {
      reflection += shade_glass(reflection_ray, reflection_hit);
    } else {
      reflection += sample_hit(reflection_hit);
    }
  }
  let tinted_reflection = (reflection / f32(NumReflectionRays)) * quad.color;
  return mix(hit_color, tinted_reflection, metallic);
}

/** Shades a ray–sphere hit with a dielectric glass material (Snell + Fresnel + TIR). */
fn shade_glass(ray : Ray, hit : HitInfo) -> vec3f {
  let sphere = spheres[hit.quad];
  let ior = sphere.color_ior.w;
  let tint = sphere.color_ior.xyz;

  let n_dot_d = dot(ray.dir, hit.normal);
  let cos_theta = max(0.0, -n_dot_d);
  // Schlick Fresnel
  let r0 = pow((1.0 - ior) / (1.0 + ior), 2.0);
  let fresnel = r0 + (1.0 - r0) * pow(1.0 - cos_theta, 5.0);

  // Front-face reflection: bounces back into the scene.
  let reflect_dir = reflect(ray.dir, hit.normal);
  let reflect_ray = Ray(hit.pos + hit.normal * 1e-4, reflect_dir);
  let reflect_color = sample_hit(raytrace(reflect_ray));

  // Refraction into the sphere. refract() returns vec3(0) on TIR — at this
  // angle (going from air n=1 into glass n>1) TIR cannot occur, but guard
  // anyway for numerical safety.
  let enter_dir = refract(ray.dir, hit.normal, 1.0 / ior);
  if (all(enter_dir == vec3f(0.0))) {
    return reflect_color * tint;
  }

  // Walk through the glass: trace ONLY against this same sphere to find the
  // back face. Starting position is nudged inside the sphere along enter_dir.
  let inside_start = hit.pos + enter_dir * 1e-4;
  var inside_hit = HitInfo();
  inside_hit.dist = 1e20;
  inside_hit.quad = kNoHit;
  inside_hit.is_sphere = 0u;
  inside_hit = intersect_ray_sphere(Ray(inside_start, enter_dir), hit.quad, inside_hit);

  var transmit_color : vec3f;
  if (inside_hit.quad == kNoHit) {
    // Numerical edge case: pretend we never re-entered the glass and just
    // sample the scene along the refracted direction.
    transmit_color = sample_hit(raytrace(Ray(inside_start, enter_dir)));
  } else {
    // intersect_ray_sphere returns the outward normal at the exit point; for
    // refracting OUT we need the inward-facing normal (pointing into the medium
    // we're leaving), so negate.
    let exit_normal = -inside_hit.normal;
    var exit_dir = refract(enter_dir, exit_normal, ior);
    if (all(exit_dir == vec3f(0.0))) {
      // Total internal reflection on the back face: bounce inside the glass
      // and exit along the reflected direction (single bounce — no recursion).
      exit_dir = reflect(enter_dir, exit_normal);
    }
    let exit_ray = Ray(inside_hit.pos + exit_dir * 1e-4, exit_dir);
    transmit_color = sample_hit(raytrace(exit_ray));
  }

  return mix(transmit_color, reflect_color, fresnel) * tint;
}

/** Samples the hit quad's lightmap + emissive + optional checkerboard. */
fn sample_hit(hit : HitInfo) -> vec3f {
  if (hit.quad == kNoHit) {
    return vec3f(common_uniforms.miss_brightness);
  }
  if (hit.is_sphere == 1u) {
    // Secondary rays hitting another sphere just return its tint — keeps the
    // shader non-recursive while still producing something reasonable.
    return spheres[hit.quad].color_ior.xyz;
  }
  let quad = quads[hit.quad];
  var color = (textureSampleLevel(lightmap, smpl, hit.uv, hit.quad, 0).rgb +
               quad.emissive * quad.color) * common_uniforms.light_intensity;
  // The floor (outside the closed box) gets a self-lit checkerboard pattern.
  if (hit.quad == common_uniforms.checker_quad) {
    color += checkerboard(hit.uv);
  }
  return color;
}