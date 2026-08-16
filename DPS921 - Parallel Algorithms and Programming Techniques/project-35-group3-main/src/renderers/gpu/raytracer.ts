import raytracerWGSL from '@/shaders/raytracer.wgsl'

import Common from '@/core/common'
import Radiosity from './radiosity'

export interface RaytracerOptions {
	workgroupSizeX: number
	workgroupSizeY: number
	numReflectionRays: number
}

export const RAYTRACER_DEFAULTS: RaytracerOptions = {
	workgroupSizeX: 16,
	workgroupSizeY: 16,
	numReflectionRays: 5,
}

/** GPU compute pipeline that ray-traces the scene using the radiosity lightmap. */
export default class Raytracer {
	private readonly common: Common
	private readonly framebuffer: GPUTexture
	private readonly pipeline: GPUComputePipeline
	private readonly bindGroup: GPUBindGroup

	private readonly workgroupSizeX: number
	private readonly workgroupSizeY: number

	constructor(
		device: GPUDevice,
		common: Common,
		radiosity: Radiosity,
		framebuffer: GPUTexture,
		options: RaytracerOptions = RAYTRACER_DEFAULTS
	) {
		this.workgroupSizeX = options.workgroupSizeX
		this.workgroupSizeY = options.workgroupSizeY
		this.common = common
		this.framebuffer = framebuffer
		const bindGroupLayout = device.createBindGroupLayout({
			label: 'Raytracer.bindGroupLayout',
			entries: [
				{
					binding: 0,
					visibility:
						GPUShaderStage.FRAGMENT | GPUShaderStage.COMPUTE,
					texture: { viewDimension: '2d-array' },
				},
				{
					binding: 1,
					visibility:
						GPUShaderStage.FRAGMENT | GPUShaderStage.COMPUTE,
					sampler: {},
				},
				{
					binding: 2,
					visibility: GPUShaderStage.COMPUTE,
					storageTexture: {
						access: 'write-only',
						format: framebuffer.format,
						viewDimension: '2d',
					},
				},
			],
		})

		this.bindGroup = device.createBindGroup({
			label: 'rendererBindGroup',
			layout: bindGroupLayout,
			entries: [
				{
					binding: 0,
					resource: radiosity.lightmap.createView(),
				},
				{
					binding: 1,
					resource: device.createSampler({
						addressModeU: 'clamp-to-edge',
						addressModeV: 'clamp-to-edge',
						addressModeW: 'clamp-to-edge',
						magFilter: 'linear',
						minFilter: 'linear',
					}),
				},
				{
					binding: 2,
					resource: framebuffer.createView(),
				},
			],
		})

		this.pipeline = device.createComputePipeline({
			label: 'raytracerPipeline',
			layout: device.createPipelineLayout({
				bindGroupLayouts: [
					common.uniforms.bindGroupLayout,
					bindGroupLayout,
				],
			}),
			compute: {
				module: device.createShaderModule({
					code: raytracerWGSL + common.wgsl,
				}),
				constants: {
					WorkgroupSizeX: this.workgroupSizeX,
					WorkgroupSizeY: this.workgroupSizeY,
					NumReflectionRays: options.numReflectionRays,
				},
			},
		})
	}

	/**
	 * Dispatches the raytrace compute pass.
	 * @param timestampWrites - Optional GPU timestamp queries for measuring pass duration.
	 */
	run(
		commandEncoder: GPUCommandEncoder,
		timestampWrites?: GPUComputePassTimestampWrites
	) {
		const passEncoder = commandEncoder.beginComputePass(
			timestampWrites ? { timestampWrites } : undefined
		)
		passEncoder.setPipeline(this.pipeline)
		passEncoder.setBindGroup(0, this.common.uniforms.bindGroup)
		passEncoder.setBindGroup(1, this.bindGroup)
		passEncoder.dispatchWorkgroups(
			Math.ceil(this.framebuffer.width / this.workgroupSizeX),
			Math.ceil(this.framebuffer.height / this.workgroupSizeY)
		)
		passEncoder.end()
	}
}
