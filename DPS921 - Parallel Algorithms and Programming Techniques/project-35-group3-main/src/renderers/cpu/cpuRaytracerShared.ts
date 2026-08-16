/** Message types shared between the main thread and the CPU raytracer worker. */

/** Everything the worker needs to render one CPU frame. Mirrors the GPU shader inputs. */
export interface CpuRaytraceRequest {
	width: number
	height: number
	/** Inverse model-view-projection, 16 floats, column-major. */
	invMvp: Float32Array
	/** 20 floats per quad: plane(4), right-plane(4), up-plane(4), color(3), emissive(1), materia(4). */
	quadData: Float32Array
	quadCount: number
	/** 8 floats per sphere: (center.xyz, radius), (color.xyz, ior). */
	sphereData: Float32Array
	sphereCount: number
	/** Lightmap texels as rgba16float, laid out [layer][row][col][channel]. */
	lightmap: Uint16Array
	lightmapSize: number // width == height == 256
	lightmapLayers: number
	lightIntensity: number
	checkerQuad: number
	/** RNG seed (3 x u32), mirroring the GPU's per-frame seed. */
	seed: Uint32Array
	/** Reflection rays per pixel — must match GPU's NumReflectionRays. */
	reflectionRays: number
	/** Background brightness for rays that escape the scene. 0 = dark, 1 = light. */
	missBrightness: number
	// For CPU Parallel implementation threads (workers)
	type: CpuRequestType
	startY: number
	endY: number
}

/** Worker -> main messages. Image streams back as bands; a final `done` carries timing. */
export type CpuRaytraceMessage =
	/** Horizontal strip of finished pixels: rows [y, y+height). */
	| { type: 'band'; y: number; height: number; pixels: Uint8ClampedArray }
	/** All bands sent; `ms` is the pure pixel-compute time. */
	| { type: 'done'; ms: number }

export type CpuRequestType = 'sequential' | 'parallel'
