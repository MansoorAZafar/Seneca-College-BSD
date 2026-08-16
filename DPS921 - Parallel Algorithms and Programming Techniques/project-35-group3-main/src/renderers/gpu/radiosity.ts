import Common from '@/core/common'
import radiosityWGSL from '@/shaders/radiosity.wgsl'
import Scene from '@/scene/scene'

export interface RadiosityOptions {
	photonsPerWorkgroup: number
	workgroupsPerFrame: number
}

export const RADIOSITY_DEFAULTS: RadiosityOptions = {
	photonsPerWorkgroup: 256,
	workgroupsPerFrame: 1024,
}

/** Computes a lightmap via GPU-based photon tracing for global illumination. */
export default class Radiosity {
	static readonly lightmapFormat = 'rgba16float'
	static readonly lightmapWidth = 256
	static readonly lightmapHeight = 256

	readonly lightmap: GPUTexture

	private readonly photonsPerWorkgroup: number
	workgroupsPerFrame: number
	// Max value added to accumulation per photon across all texels.
	private readonly kPhotonEnergy = 100000
	private readonly kTotalLightmapTexels

	private readonly kAccumulationToLightmapWorkgroupSizeX = 16
	private readonly kAccumulationToLightmapWorkgroupSizeY = 16

	private readonly device: GPUDevice
	private readonly common: Common
	private readonly scene: Scene
	private readonly radiosityPipeline: GPUComputePipeline
	private readonly accumulationToLightmapPipeline: GPUComputePipeline
	private readonly bindGroup: GPUBindGroup
	private readonly accumulationBuffer: GPUBuffer
	private readonly uniformBuffer: GPUBuffer

	private accumulationMean = 0

	// When accumulationMean exceeds this, values are halved to prevent u32 overflow.
	private readonly kAccumulationMeanMax = 0x10000000

	constructor(
		device: GPUDevice,
		common: Common,
		scene: Scene,
		options: RadiosityOptions = RADIOSITY_DEFAULTS
	) {
		this.device = device
		this.common = common
		this.scene = scene
		this.photonsPerWorkgroup = options.photonsPerWorkgroup
		this.workgroupsPerFrame = options.workgroupsPerFrame
		this.lightmap = device.createTexture({
			label: 'Radiosity.lightmap',
			size: {
				width: Radiosity.lightmapWidth,
				height: Radiosity.lightmapHeight,
				depthOrArrayLayers: scene.quads.length,
			},
			format: Radiosity.lightmapFormat,
			usage:
				GPUTextureUsage.TEXTURE_BINDING |
				GPUTextureUsage.STORAGE_BINDING |
				GPUTextureUsage.COPY_SRC, // For CPU raytracer readback
		})
		this.accumulationBuffer = device.createBuffer({
			label: 'Radiosity.accumulationBuffer',
			size:
				Radiosity.lightmapWidth *
				Radiosity.lightmapHeight *
				scene.quads.length *
				16,
			usage: GPUBufferUsage.STORAGE,
		})
		this.kTotalLightmapTexels =
			Radiosity.lightmapWidth *
			Radiosity.lightmapHeight *
			scene.quads.length
		this.uniformBuffer = device.createBuffer({
			label: 'Radiosity.uniformBuffer',
			size: 8 * 4,
			usage: GPUBufferUsage.UNIFORM | GPUBufferUsage.COPY_DST,
		})
		const bindGroupLayout = device.createBindGroupLayout({
			label: 'Radiosity.bindGroupLayout',
			entries: [
				{
					binding: 0,
					visibility: GPUShaderStage.COMPUTE,
					buffer: { type: 'storage' },
				},
				{
					binding: 1,
					visibility: GPUShaderStage.COMPUTE,
					storageTexture: {
						access: 'write-only',
						format: Radiosity.lightmapFormat,
						viewDimension: '2d-array',
					},
				},
				{
					binding: 2,
					visibility: GPUShaderStage.COMPUTE,
					buffer: { type: 'uniform' },
				},
			],
		})
		this.bindGroup = device.createBindGroup({
			label: 'Radiosity.bindGroup',
			layout: bindGroupLayout,
			entries: [
				{
					binding: 0,
					resource: this.accumulationBuffer,
				},
				{
					binding: 1,
					resource: this.lightmap.createView(),
				},
				{
					binding: 2,
					resource: this.uniformBuffer,
				},
			],
		})

		const mod = device.createShaderModule({
			code: radiosityWGSL + common.wgsl,
		})
		const pipelineLayout = device.createPipelineLayout({
			label: 'Radiosity.accumulatePipelineLayout',
			bindGroupLayouts: [
				common.uniforms.bindGroupLayout,
				bindGroupLayout,
			],
		})

		this.radiosityPipeline = device.createComputePipeline({
			label: 'Radiosity.radiosityPipeline',
			layout: pipelineLayout,
			compute: {
				module: mod,
				entryPoint: 'radiosity',
				constants: {
					PhotonsPerWorkgroup: this.photonsPerWorkgroup,
					PhotonEnergy: this.kPhotonEnergy,
				},
			},
		})

		this.accumulationToLightmapPipeline = device.createComputePipeline({
			label: 'Radiosity.accumulationToLightmapPipeline',
			layout: pipelineLayout,
			compute: {
				module: mod,
				entryPoint: 'accumulation_to_lightmap',
				constants: {
					AccumulationToLightmapWorkgroupSizeX:
						this.kAccumulationToLightmapWorkgroupSizeX,
					AccumulationToLightmapWorkgroupSizeY:
						this.kAccumulationToLightmapWorkgroupSizeY,
				},
			},
		})
	}

	/** Fires photons and updates the lightmap for one frame. */
	run(commandEncoder: GPUCommandEncoder) {
		const photonsPerFrame =
			this.photonsPerWorkgroup * this.workgroupsPerFrame
		this.accumulationMean +=
			(photonsPerFrame * this.kPhotonEnergy) / this.kTotalLightmapTexels

		const accumulationToLightmapScale = 1 / this.accumulationMean
		// Halve accumulation if it risks u32 overflow.
		const accumulationBufferScale =
			this.accumulationMean > 2 * this.kAccumulationMeanMax ? 0.5 : 1
		this.accumulationMean *= accumulationBufferScale

		const uniformDataF32 = new Float32Array(this.uniformBuffer.size / 4)
		uniformDataF32[0] = accumulationToLightmapScale
		uniformDataF32[1] = accumulationBufferScale
		uniformDataF32[2] = this.scene.lightWidth
		uniformDataF32[3] = this.scene.lightHeight
		uniformDataF32[4] = this.scene.lightCenter[0]
		uniformDataF32[5] = this.scene.lightCenter[1]
		uniformDataF32[6] = this.scene.lightCenter[2]
		this.device.queue.writeBuffer(
			this.uniformBuffer,
			0,
			uniformDataF32.buffer,
			uniformDataF32.byteOffset,
			uniformDataF32.byteLength
		)

		const passEncoder = commandEncoder.beginComputePass()
		passEncoder.setBindGroup(0, this.common.uniforms.bindGroup)
		passEncoder.setBindGroup(1, this.bindGroup)
		passEncoder.setPipeline(this.radiosityPipeline)
		passEncoder.dispatchWorkgroups(this.workgroupsPerFrame)

		// Copy accumulation buffer data to the lightmap texture.
		passEncoder.setPipeline(this.accumulationToLightmapPipeline)
		passEncoder.dispatchWorkgroups(
			Math.ceil(
				Radiosity.lightmapWidth /
					this.kAccumulationToLightmapWorkgroupSizeX
			),
			Math.ceil(
				Radiosity.lightmapHeight /
					this.kAccumulationToLightmapWorkgroupSizeY
			),
			this.lightmap.depthOrArrayLayers
		)
		passEncoder.end()
	}

	/** Reads the lightmap back to the CPU (rgba16float half-float texels). */
	async readLightmap(): Promise<{
		data: Uint16Array
		size: number
		layers: number
	}> {
		const size = Radiosity.lightmapWidth
		const layers = this.lightmap.depthOrArrayLayers
		const bytesPerRow = size * 4 * 2

		const readBuffer = this.device.createBuffer({
			size: bytesPerRow * size * layers,
			usage: GPUBufferUsage.COPY_DST | GPUBufferUsage.MAP_READ,
		})

		const encoder = this.device.createCommandEncoder()
		encoder.copyTextureToBuffer(
			{ texture: this.lightmap },
			{ buffer: readBuffer, bytesPerRow, rowsPerImage: size },
			{ width: size, height: size, depthOrArrayLayers: layers }
		)
		this.device.queue.submit([encoder.finish()])

		await readBuffer.mapAsync(GPUMapMode.READ)
		const data = new Uint16Array(readBuffer.getMappedRange().slice(0))
		readBuffer.unmap()
		readBuffer.destroy()

		return { data, size, layers }
	}
}
