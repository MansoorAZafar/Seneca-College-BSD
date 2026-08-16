import { mat4, Mat4 } from 'wgpu-matrix'
import commonWGSL from '@/shaders/common.wgsl'

/** Holds the shared WGSL code and uniform buffer used by all compute pipelines. */
export default class Common {
	/** The WGSL source string with the common structs and helpers. */
	readonly wgsl = commonWGSL
	/** Bind group and layout for the common uniform buffer + quad storage. */
	readonly uniforms: {
		bindGroupLayout: GPUBindGroupLayout
		bindGroup: GPUBindGroup
	}

	/** Index of the checkerboard floor quad (set by main.ts). 0xffffffff = none. */
	checkerQuad = 0xffffffff

	/** Light brightness multiplier (1 = default), applied to the lightmap on render. */
	lightIntensity = 1

	/** Background color for rays that escape the scene. 1 = light (live view),
	 *  0 = dark (snapshot). */
	missBrightness = 1

	/** Inverse MVP from the latest update(). Used by the CPU raytracer to build rays. */
	readonly invMvp: Mat4 = mat4.create()

	private readonly device: GPUDevice
	private readonly uniformBuffer: GPUBuffer

	constructor(device: GPUDevice, quads: GPUBuffer, spheres: GPUBuffer) {
		this.device = device
		this.uniformBuffer = device.createBuffer({
			label: 'Common.uniformBuffer',
			size:
				0 + //
				4 * 16 + // mvp
				4 * 16 + // inv_mvp
				4 * 4 + // seed (vec3u) + checker_quad share one 16-byte slot
				4 * 4, // light_intensity + padding
			usage: GPUBufferUsage.UNIFORM | GPUBufferUsage.COPY_DST,
		})

		const bindGroupLayout = device.createBindGroupLayout({
			label: 'Common.bindGroupLayout',
			entries: [
				{
					binding: 0,
					visibility: GPUShaderStage.COMPUTE,
					buffer: { type: 'uniform' },
				},
				{
					binding: 1,
					visibility: GPUShaderStage.COMPUTE,
					buffer: { type: 'read-only-storage' },
				},
				{
					binding: 2,
					visibility: GPUShaderStage.COMPUTE,
					buffer: { type: 'read-only-storage' },
				},
			],
		})

		const bindGroup = device.createBindGroup({
			label: 'Common.bindGroup',
			layout: bindGroupLayout,
			entries: [
				{
					binding: 0,
					resource: { buffer: this.uniformBuffer },
				},
				{
					binding: 1,
					resource: { buffer: quads },
				},
				{
					binding: 2,
					resource: { buffer: spheres },
				},
			],
		})

		this.uniforms = { bindGroupLayout, bindGroup }
	}

	/**
	 * Writes the MVP + inverse-MVP matrices and per-frame random seed to the
	 * uniform buffer. The view matrix comes from the interactive camera rather
	 * than a fixed auto-rotation (unlike the original Cornell sample).
	 */
	update(params: { view: Mat4; aspect: number }) {
		const projectionMatrix = mat4.perspective(
			(2 * Math.PI) / 8,
			params.aspect,
			0.5,
			100
		)

		const mvp = mat4.multiply(projectionMatrix, params.view)
		const invMVP = mat4.invert(mvp)
		mat4.copy(invMVP, this.invMvp)

		const uniformDataF32 = new Float32Array(this.uniformBuffer.size / 4)
		const uniformDataU32 = new Uint32Array(uniformDataF32.buffer)
		for (let i = 0; i < 16; i++) {
			uniformDataF32[i] = mvp[i]
		}
		for (let i = 0; i < 16; i++) {
			uniformDataF32[i + 16] = invMVP[i]
		}
		uniformDataU32[32] = 0xffffffff * Math.random()
		uniformDataU32[33] = 0xffffffff * Math.random()
		uniformDataU32[34] = 0xffffffff * Math.random()
		uniformDataU32[35] = this.checkerQuad
		uniformDataF32[36] = this.lightIntensity
		uniformDataF32[37] = this.missBrightness

		this.device.queue.writeBuffer(
			this.uniformBuffer,
			0,
			uniformDataF32.buffer,
			uniformDataF32.byteOffset,
			uniformDataF32.byteLength
		)
	}
}
