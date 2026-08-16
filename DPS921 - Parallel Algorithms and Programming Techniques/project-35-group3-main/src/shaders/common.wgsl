const pi = 3.14159265359;

// --- Quad struct ------------------------------------------------------------

/** 2D rectangle on a plane. */
struct Quad {
  // Surface plane: (normal.xyz, -dot(normal, center))
  plane    : vec4f,
  // Plane with normal in the 'u' direction, at right-angles to the surface.
  // dot(right, vec4(pos,1)) ranges [-1..1] if the projected point is within the quad.
  right    : vec4f,
  // Plane with normal in the 'v' direction, at right-angles to the surface.
  up       : vec4f,
  // Diffuse surface color
  color    : vec3f,
  // Emissive value (0 = none, 1 = full)
  emissive : f32,
  // surface material (.x = metallic, .y = roughness, .z&w = reserved )
  material : vec4f,
};

// --- Ray + HitInfo structs --------------------------------------------------

/** A ray with a start point and direction. */
struct Ray {
  start : vec3f,
  dir   : vec3f,
}

/** No-intersection sentinel value. */
const kNoHit = 0xffffffff;

/** Describes a ray–primitive intersection (quad or sphere). */
struct HitInfo {
  dist     : f32,   // Distance along the ray to the intersection
  quad     : u32,   // Hit primitive index (quad index if is_sphere==0, sphere index otherwise)
  pos      : vec3f, // World-space hit position
  uv       : vec2f, // Quad UVs (unused for spheres)
  normal   : vec3f, // Outward surface normal at the hit
  is_sphere: u32,   // 0 = quad hit, 1 = sphere hit
}

// --- Common uniform buffer --------------------------------------------------

struct CommonUniforms {
  mvp          : mat4x4f, // Model-View-Projection matrix
  inv_mvp      : mat4x4f, // Inverse of mvp
  seed         : vec3u,   // Per-frame random seed
  checker_quad : u32,     // Index of the checkerboard floor quad (0xffffffff = none)
  light_intensity : f32,  // User-controlled brightness multiplier
  miss_brightness : f32,  // Background color for rays that hit nothing (0=dark, 1=light)
}

@group(0) @binding(0) var<uniform> common_uniforms : CommonUniforms;

// --- Quad storage buffer ----------------------------------------------------

@group(0) @binding(1) var<storage> quads : array<Quad>;

// --- Sphere struct + storage buffer -----------------------------------------

/** A glass (dielectric) sphere primitive. */
struct Sphere {
  center_radius : vec4f, // xyz = center, w = radius
  color_ior     : vec4f, // xyz = tint, w = index of refraction
}

@group(0) @binding(2) var<storage> spheres : array<Sphere>;

// --- Geometry intersection helpers ------------------------------------------

/** Returns a black/white checker color for the given quad UVs (floor pattern). */
fn checkerboard(uv : vec2f) -> vec3f {
  const squares = 16.0;
  let cell = floor(uv * squares);
  let odd = (cell.x + cell.y) - 2.0 * floor((cell.x + cell.y) * 0.5);
  return select(vec3f(1.6), vec3f(0.06), odd > 0.5);
}

/** Tests ray `r` against quad `q`. If closer than `closest`, returns the hit info. */
fn intersect_ray_quad(r : Ray, quad : u32, closest : HitInfo) -> HitInfo {
  let q = quads[quad];
  let plane_dist = dot(q.plane, vec4(r.start, 1));
  let ray_dist = plane_dist / -dot(q.plane.xyz, r.dir);
  let pos = r.start + r.dir * ray_dist;
  let uv = vec2(dot(vec4f(pos, 1), q.right),
                dot(vec4f(pos, 1), q.up)) * 0.5 + 0.5;
  let hit = plane_dist > 0 &&
            ray_dist > 0 &&
            ray_dist < closest.dist &&
            all((uv > vec2f()) & (uv < vec2f(1)));
  return HitInfo(
    select(closest.dist,      ray_dist,   hit),
    select(closest.quad,      quad,       hit),
    select(closest.pos,       pos,        hit),
    select(closest.uv,        uv,         hit),
    select(closest.normal,    q.plane.xyz,hit),
    select(closest.is_sphere, 0u,         hit),
  );
}

/** Tests ray `r` against sphere `sphere_idx`. Picks the nearest positive root.
 *  Handles rays starting inside the sphere (returns the exit point with an
 *  inward-pointing normal flipped to outward). */
fn intersect_ray_sphere(r : Ray, sphere_idx : u32, closest : HitInfo) -> HitInfo {
  let s = spheres[sphere_idx];
  let center = s.center_radius.xyz;
  let radius = s.center_radius.w;
  let oc = r.start - center;
  let b = dot(oc, r.dir);
  let c = dot(oc, oc) - radius * radius;
  let disc = b * b - c;
  // Nearest positive t (entry hit). If disc < 0 no real roots.
  let sqrt_disc = sqrt(max(disc, 0.0));
  let t0 = -b - sqrt_disc;
  let t1 = -b + sqrt_disc;
  // Use t0 if positive (we're outside the sphere), else t1 (we're inside).
  let t = select(t1, t0, t0 > 1e-4);
  let pos = r.start + r.dir * t;
  let outward = (pos - center) / radius;
  let hit = disc > 0.0 && t > 1e-4 && t < closest.dist;
  return HitInfo(
    select(closest.dist,      t,          hit),
    select(closest.quad,      sphere_idx, hit),
    select(closest.pos,       pos,        hit),
    select(closest.uv,        vec2f(0),   hit),
    select(closest.normal,    outward,    hit),
    select(closest.is_sphere, 1u,         hit),
  );
}

/** Finds the closest intersecting primitive (quad or sphere) for the given ray. */
fn raytrace(ray : Ray) -> HitInfo {
  var hit = HitInfo();
  hit.dist = 1e20;
  hit.quad = kNoHit;
  hit.is_sphere = 0u;
  for (var quad = 0u; quad < arrayLength(&quads); quad++) {
    hit = intersect_ray_quad(ray, quad, hit);
  }
  for (var sphere = 0u; sphere < arrayLength(&spheres); sphere++) {
    hit = intersect_ray_sphere(ray, sphere, hit);
  }
  return hit;
}

// --- Pseudo-random number generator -----------------------------------------

var<private> rnd : vec3u;

fn init_rand(invocation_id : vec3u) {
  const A = vec3(1741651 * 1009,
                 140893  * 1609 * 13,
                 6521    * 983  * 7 * 2);
  rnd = (invocation_id * A) ^ common_uniforms.seed;
}

/** Returns a random number in [0, 1). */
fn rand() -> f32 {
  const C = vec3(60493  * 9377,
                 11279  * 2539 * 23,
                 7919   * 631  * 5 * 3);

  rnd = (rnd * C) ^ (rnd.yzx >> vec3(4u));
  return f32(rnd.x ^ rnd.y) / f32(0xffffffff);
}

/** Returns a random point within a unit sphere at (0,0,0). */
fn rand_unit_sphere() -> vec3f {
    var u = rand();
    var v = rand();
    var theta = u * 2.0 * pi;
    var phi = acos(2.0 * v - 1.0);
    var r = pow(rand(), 1.0/3.0);
    var sin_theta = sin(theta);
    var cos_theta = cos(theta);
    var sin_phi = sin(phi);
    var cos_phi = cos(phi);
    var x = r * sin_phi * sin_theta;
    var y = r * sin_phi * cos_theta;
    var z = r * cos_phi;
    return vec3f(x, y, z);
}

/** Returns a random point on a unit disk with concentric mapping (for cosine-weighted hemisphere sampling). */
fn rand_concentric_disk() -> vec2f {
    let u = vec2f(rand(), rand());
    let uOffset = 2.f * u - vec2f(1, 1);

    if (uOffset.x == 0 && uOffset.y == 0){
        return vec2f(0, 0);
    }

    var theta = 0.0;
    var r = 0.0;
    if (abs(uOffset.x) > abs(uOffset.y)) {
        r = uOffset.x;
        theta = (pi / 4) * (uOffset.y / uOffset.x);
    } else {
        r = uOffset.y;
        theta = (pi / 2) - (pi / 4) * (uOffset.x / uOffset.y);
    }
    return r * vec2f(cos(theta), sin(theta));
}

/** Returns a random direction in a hemisphere weighted by cosine (for diffuse light sampling). */
fn rand_cosine_weighted_hemisphere() -> vec3f {
    let d = rand_concentric_disk();
    let z = sqrt(max(0.0, 1.0 - d.x * d.x - d.y * d.y));
    return vec3f(d.x, d.y, z);
}