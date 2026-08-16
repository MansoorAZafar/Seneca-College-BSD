import Common from '@/core/common'
import tonemapperWGSL from '@/shaders/tonemapper.wgsl'

/** Applies Reinhard tonemapping + gamma correction to convert HDR -> LDR for display. */
export default class Tonemapper {
	private readonly bindGroup: GPUBindGroup
	private readonly pipeline: GPUComputePipeline
	private readonly width: number
	private readonly height: number
	private readonly kWorkgroupSizeX = 16
	private readonly kWorkgroupSizeY = 16

	constructor(
		device: GPUDevice,
		common: Common,
		input: GPUTexture,
		output: GPUTexture
	) {
		this.width = output.width
		this.height = output.height
		const bindGroupLayout = device.createBindGroupLayout({
			label: 'Tonemapper.bindGroupLayout',
			entries: [
				{
					binding: 0,
					visibility: GPUShaderStage.COMPUTE,
					texture: { viewDimension: '2d' },
				},
				{
					binding: 1,
					visibility: GPUShaderStage.COMPUTE,
					sampler: {},
				},
				{
					binding: 2,
					visibility: GPUShaderStage.COMPUTE,
					storageTexture: {
						access: 'write-only',
						format: output.format,
						viewDimension: '2d',
					},
				},
			],
		})
		this.bindGroup = device.createBindGroup({
			label: 'Tonemapper.bindGroup',
			layout: bindGroupLayout,
			entries: [
				{
					binding: 0,
					resource: input.createView(),
				},
				{
					binding: 1,
					resource: device.createSampler({
						magFilter: 'linear',
						minFilter: 'linear',
						addressModeU: 'clamp-to-edge',
						addressModeV: 'clamp-to-edge',
					}),
				},
				{
					binding: 2,
					resource: output.createView(),
				},
			],
		})

		const mod = device.createShaderModule({
			code:
				tonemapperWGSL.replace('{OUTPUT_FORMAT}', output.format) +
				common.wgsl,
		})
		const pipelineLayout = device.createPipelineLayout({
			label: 'Tonemap.pipelineLayout',
			bindGroupLayouts: [bindGroupLayout],
		})

		this.pipeline = device.createComputePipeline({
			label: 'Tonemap.pipeline',
			layout: pipelineLayout,
			compute: {
				module: mod,
				constants: {
					WorkgroupSizeX: this.kWorkgroupSizeX,
					WorkgroupSizeY: this.kWorkgroupSizeY,
				},
			},
		})
	}

	/** Dispatches the tonemap compute shader for the current framebuffer. */
	run(commandEncoder: GPUCommandEncoder) {
		const passEncoder = commandEncoder.beginComputePass()
		passEncoder.setBindGroup(0, this.bindGroup)
		passEncoder.setPipeline(this.pipeline)
		passEncoder.dispatchWorkgroups(
			Math.ceil(this.width / this.kWorkgroupSizeX),
			Math.ceil(this.height / this.kWorkgroupSizeY)
		)
		passEncoder.end()
	}
}
