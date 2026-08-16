// Linear-light input framebuffer (HDR)
@group(0) @binding(0) var input  : texture_2d<f32>;
@group(0) @binding(1) var smpl   : sampler;

// Tonemapped, gamma-corrected output framebuffer (LDR)
@group(0) @binding(2) var output : texture_storage_2d<{OUTPUT_FORMAT}, write>;

const TonemapExposure = 0.5;
const Gamma = 2.2;

override WorkgroupSizeX : u32;
override WorkgroupSizeY : u32;

/** Applies Reinhard tonemap + gamma correction to each pixel. */
@compute @workgroup_size(WorkgroupSizeX, WorkgroupSizeY)
fn main(@builtin(global_invocation_id) invocation_id : vec3u) {
  let dims = textureDimensions(output);
  if (any(invocation_id.xy >= dims)) { return; }
  let uv = (vec2f(invocation_id.xy) + vec2f(0.5)) / vec2f(dims);
  let color = textureSampleLevel(input, smpl, uv, 0.0).rgb;
  let tonemapped = reinhard_tonemap(color);
  textureStore(output, invocation_id.xy, vec4f(tonemapped, 1));
}

fn reinhard_tonemap(linearColor: vec3f) -> vec3f {
  let color = linearColor * TonemapExposure;
  let mapped = color / (1+color);
  return pow(mapped, vec3f(1 / Gamma));
}