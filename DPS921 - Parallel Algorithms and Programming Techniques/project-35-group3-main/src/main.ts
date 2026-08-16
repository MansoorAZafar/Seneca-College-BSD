import { GUI } from 'dat.gui'
import { mat4, vec3 } from 'wgpu-matrix'

import Scene from './scene/scene'
import Common from './core/common'
import Radiosity from './renderers/gpu/radiosity'
import Tonemapper from './renderers/gpu/tonemapper'
import Raytracer from './renderers/gpu/raytracer'
import Diagnostics, { SnapshotResult, CpuResult } from './core/diagnostics'
import Benchmark, {
	RunCounts,
	ModeResult,
	BenchmarkResults,
} from './core/benchmark'
import CpuRaytracer from './renderers/cpu/cpuRaytracer'
import type {
	CpuRaytraceRequest,
	CpuRequestType,
} from './renderers/cpu/cpuRaytracerShared'

import { WASDCamera } from './scene/camera'
import { createInputHandler } from './scene/input'

import {
	quitIfAdapterNotAvailable,
	quitIfWebGPUNotAvailableOrMissingFeatures,
	quitIfLimitLessThan,
} from './core/util'
import {
	ParallelCpuRender,
	SequentialCpuRender,
} from './renderers/cpu/cpuRayTracerStrategies'

const canvas = document.querySelector('canvas') as HTMLCanvasElement

// --- Input & Camera Setup ---------------------------------------------------

// Watches keyboard and mouse/touch on the canvas; returns a snapshot each frame.
const inputHandler = createInputHandler(window, canvas)

// Start outside the box (spans -5:5 on X/Z, 0:10 on Y), looking at the center.
const initialCameraPosition = vec3.create(0, 5, 17)
const headOnTarget = vec3.create(0, 5, 0)

let camera = new WASDCamera({
	position: initialCameraPosition,
	target: headOnTarget,
})

/** Resets the camera to the canonical head-on view for reproducible framing. */
function resetView() {
	dismissOverlay()
	camera = new WASDCamera({
		position: initialCameraPosition,
		target: headOnTarget,
	})
}

// --- WebGPU Device Setup ----------------------------------------------------

const adapter = await navigator.gpu?.requestAdapter({
	featureLevel: 'compatibility',
})
quitIfAdapterNotAvailable(adapter)

const features: GPUFeatureName[] = []
let presentationFormat = navigator.gpu.getPreferredCanvasFormat()
if (presentationFormat == 'bgra8unorm') {
	if (adapter.features.has('bgra8unorm-storage')) {
		features.push('bgra8unorm-storage')
	} else {
		// Adapter doesn't support bgra8unorm-storage (e.g., Compatibility mode),
		// so use rgba8unorm for both (slower but works).
		presentationFormat = 'rgba8unorm'
	}
}

// Optional 'timestamp-query' lets us measure GPU pass duration for snapshots.
const canTimestamp = adapter.features.has('timestamp-query')
if (canTimestamp) {
	features.push('timestamp-query')
}

const limits: Record<string, GPUSize32> = {}
quitIfLimitLessThan(adapter, 'maxComputeWorkgroupSizeX', 256, limits)
quitIfLimitLessThan(adapter, 'maxComputeInvocationsPerWorkgroup', 256, limits)
const device = await adapter?.requestDevice({
	requiredFeatures: features,
	requiredLimits: limits,
})
quitIfWebGPUNotAvailableOrMissingFeatures(adapter, device)

// Two timestamp queries (start + end) written to querySet, resolved via resolveBuffer.
const timestamp = canTimestamp
	? {
			querySet: device.createQuerySet({ type: 'timestamp', count: 2 }),
			resolveBuffer: device.createBuffer({
				size: 2 * 8,
				usage: GPUBufferUsage.QUERY_RESOLVE | GPUBufferUsage.COPY_SRC,
			}),
			resultBuffer: device.createBuffer({
				size: 2 * 8,
				usage: GPUBufferUsage.COPY_DST | GPUBufferUsage.MAP_READ,
			}),
		}
	: null

const gpuInfo = (() => {
	const info = adapter.info
	const parts = [info?.architecture, info?.vendor].filter(Boolean)
	const name = parts.length ? parts.join(' / ') : 'WebGPU device'
	return canTimestamp ? name : `${name} (no timer)`
})()

// --- GUI --------------------------------------------------------------------

const RAYTRACER_WG_CHOICES = ['8x8', '8x16', '16x8', '16x16', '32x8']
const PHOTONS_PER_WG_CHOICES = [32, 64, 128, 256]

// Logical cores reported by the browser (fallback 4); used to bound the slider.
const maxCpuCores = navigator.hardwareConcurrency ?? 4

const params = {
	lightIntensity: 1,
	reflectionRays: 5,
	radiosityWorkgroupsPerFrame: 1024,
	renderScale: 1.0,
	raytracerWorkgroup: '16x16',
	photonsPerWorkgroup: 256,
	// Worker threads for the parallel CPU renderer; default leaves one for the app.
	cpuCores: Math.max(1, maxCpuCores - 1),
}

function scaledRenderSize(): [number, number] {
	const w = Math.max(1, Math.floor(canvas.width * params.renderScale))
	const h = Math.max(1, Math.floor(canvas.height * params.renderScale))
	return [w, h]
}

function parseWg(s: string): [number, number] {
	const [x, y] = s.split('x').map((n) => parseInt(n, 10))
	return [x, y]
}
function currentRaytracerOptions() {
	const [x, y] = parseWg(params.raytracerWorkgroup)
	return {
		workgroupSizeX: x,
		workgroupSizeY: y,
		numReflectionRays: params.reflectionRays,
	}
}
function currentRadiosityOptions() {
	return {
		photonsPerWorkgroup: params.photonsPerWorkgroup,
		workgroupsPerFrame: params.radiosityWorkgroupsPerFrame,
	}
}

const gui = new GUI({ width: 300 })
gui.domElement.classList.add('friendly-gui')

const lightFolder = gui.addFolder('Light')
lightFolder.add(params, 'lightIntensity', 0, 3, 0.05).name('Intensity')

const qualityFolder = gui.addFolder('Quality')
qualityFolder
	.add(params, 'reflectionRays', 1, 32, 1)
	.name('Reflection rays/px')
	.onChange(() => {
		pendingRaytracerRebuild = true
	})
qualityFolder
	.add(params, 'radiosityWorkgroupsPerFrame', 16, 4096, 16)
	.name('Photon workgroups/frame')
	.onChange(() => {
		radiosity.workgroupsPerFrame = params.radiosityWorkgroupsPerFrame
	})
qualityFolder
	.add(params, 'renderScale', 0.01, 2, 0.01)
	.name('Render scale')
	.onChange(() => {
		pendingFramebufferRebuild = true
	})

const gpuFolder = gui.addFolder('GPU')
gpuFolder
	.add(params, 'raytracerWorkgroup', RAYTRACER_WG_CHOICES)
	.name('Raytracer workgroup')
	.onChange(() => {
		pendingRaytracerRebuild = true
	})
gpuFolder
	.add(params, 'photonsPerWorkgroup', PHOTONS_PER_WG_CHOICES)
	.name('Photons/workgroup')
	.onChange(() => {
		pendingRadiosityRebuild = true
	})

const cpuFolder = gui.addFolder('CPU')
cpuFolder
	.add(params, 'cpuCores', 1, maxCpuCores, 1)
	.name('CPU cores (parallel)')

// Snapshot button handlers (defined below, captured lazily).
const snapshotActions = {
	run: () => void runRaytraceSnapshot(),
	cpu: () => void runCpuRender(),
	cpuParallel: () => void runCpuRender('parallel'),
}
const snapshotFolder = gui.addFolder('Snapshot')
snapshotFolder.add(snapshotActions, 'run').name('Render 1 frame on GPU')
snapshotFolder
	.add(snapshotActions, 'cpu')
	.name('Render 1 frame sequentially on CPU')
snapshotFolder
	.add(snapshotActions, 'cpuParallel')
	.name('Render 1 frame concurrently on the CPU')

const cameraFolder = gui.addFolder('Camera')
const cameraActions = {
	reset: () => resetView(),
}
cameraFolder.add(cameraActions, 'reset').name('Reset to head-on view')

lightFolder.open()
qualityFolder.open()
gpuFolder.open()
cpuFolder.open()
cameraFolder.open()
snapshotFolder.open()

const diagnostics = new Diagnostics()
const benchmark = new Benchmark(gui, (counts) => void runBenchmark(counts))
const cpuRaytracer = new CpuRaytracer()

// --- Canvas & Render Resources ----------------------------------------------

/** Sizes canvas backing store to CSS size × device pixel ratio for crisp rendering. */
function sizeCanvasToWindow() {
	const dpr = window.devicePixelRatio
	canvas.width = Math.max(1, Math.floor(canvas.clientWidth * dpr))
	canvas.height = Math.max(1, Math.floor(canvas.clientHeight * dpr))
}
sizeCanvasToWindow()

const context = canvas.getContext('webgpu')
context.configure({
	device,
	format: presentationFormat,
	usage: GPUTextureUsage.RENDER_ATTACHMENT | GPUTextureUsage.STORAGE_BINDING,
})

/** Creates an offscreen HDR framebuffer sized to canvas × renderScale. The
 *  tonemapper upscales it to canvas resolution. */
function createFramebuffer() {
	return device.createTexture({
		label: 'framebuffer',
		size: scaledRenderSize(),
		format: 'rgba16float',
		usage:
			GPUTextureUsage.RENDER_ATTACHMENT |
			GPUTextureUsage.STORAGE_BINDING |
			GPUTextureUsage.TEXTURE_BINDING,
	})
}

const scene = new Scene(device)
const common = new Common(device, scene.quadBuffer, scene.sphereBuffer)
common.checkerQuad = scene.checkerboardQuadIndex
let radiosity = new Radiosity(device, common, scene, currentRadiosityOptions())

let framebuffer = createFramebuffer()
let raytracer = new Raytracer(
	device,
	common,
	radiosity,
	framebuffer,
	currentRaytracerOptions()
)

let pendingRaytracerRebuild = false
let pendingRadiosityRebuild = false
let pendingFramebufferRebuild = false

function rebuildRaytracer() {
	raytracer = new Raytracer(
		device,
		common,
		radiosity,
		framebuffer,
		currentRaytracerOptions()
	)
}
function rebuildRadiosity() {
	radiosity = new Radiosity(device, common, scene, currentRadiosityOptions())
	rebuildRaytracer()
}
function rebuildFramebuffer() {
	framebuffer.destroy()
	framebuffer = createFramebuffer()
	rebuildRaytracer()
}

window.addEventListener('resize', () => {
	sizeCanvasToWindow()
	rebuildFramebuffer()
})

// --- Render Loop ------------------------------------------------------------

let lastFrameMS = Date.now()
let frameMsEma = 16.7 // Smoothed frame time for stable FPS readout.
const lastView = mat4.create() // Frozen view for snapshot re-rendering.

let rafHandle = 0
function scheduleNextFrame() {
	rafHandle = requestAnimationFrame(frame)
}
function pauseLoop() {
	if (rafHandle) {
		cancelAnimationFrame(rafHandle)
		rafHandle = 0
	}
}
function resumeLoop() {
	lastFrameMS = Date.now()
	if (!rafHandle) scheduleNextFrame()
}

function frame() {
	rafHandle = 0

	if (pendingFramebufferRebuild) {
		rebuildFramebuffer()
		pendingFramebufferRebuild = false
		pendingRaytracerRebuild = false
	}
	if (pendingRadiosityRebuild) {
		rebuildRadiosity()
		pendingRadiosityRebuild = false
		pendingRaytracerRebuild = false
	} else if (pendingRaytracerRebuild) {
		rebuildRaytracer()
		pendingRaytracerRebuild = false
	}

	const now = Date.now()
	const deltaMs = now - lastFrameMS
	lastFrameMS = now
	const deltaTime = deltaMs / 1000
	frameMsEma = frameMsEma * 0.9 + deltaMs * 0.1 // Exponential moving average

	const viewMatrix = camera.update(deltaTime, inputHandler())
	mat4.copy(viewMatrix, lastView)

	const canvasTexture = context.getCurrentTexture()
	const commandEncoder = device.createCommandEncoder()

	common.lightIntensity = params.lightIntensity
	common.missBrightness = 1 // light background for the live continuous view
	common.update({
		view: viewMatrix,
		aspect: canvas.width / canvas.height,
	})
	radiosity.run(commandEncoder)
	raytracer.run(commandEncoder)

	const tonemapper = new Tonemapper(
		device,
		common,
		framebuffer,
		canvasTexture
	)
	tonemapper.run(commandEncoder)

	device.queue.submit([commandEncoder.finish()])
	updateDiagnostics()
	scheduleNextFrame()
}

/** Pushes current stats into the diagnostics panel. */
function updateDiagnostics() {
	diagnostics.update({
		fps: 1000 / frameMsEma,
		frameMs: frameMsEma,
		width: canvas.width,
		height: canvas.height,
		cameraPosition: camera.position,
		lightIntensity: params.lightIntensity,
		gpuInfo,
		snapshotStatus,
		snapshot: lastSnapshot,
		cpuStatus,
		cpu: lastCpu,
	})
}

// --- Raytrace Snapshot ------------------------------------------------------
// Renders one or more fully-raytraced frames with the loop paused, reporting
// both GPU pass time (via timestamp-query) and wall-clock time.

let snapshotStatus = ''
let lastSnapshot: SnapshotResult | null = null
let snapshotBusy = false

async function runRaytraceSnapshot() {
	if (snapshotBusy || cpuBusy || benchmarkBusy) return
	dismissOverlay()
	snapshotBusy = true
	snapshotStatus = 'measuring…'
	pauseLoop()
	updateDiagnostics()

	// Freeze the uniforms at the stored camera view.
	common.lightIntensity = params.lightIntensity
	common.missBrightness = 0 // dark background for the snapshot
	common.update({ view: lastView, aspect: canvas.width / canvas.height })

	try {
		// One warm-up frame (not timed).
		await renderRaytraceFrame(false)

		// Average several timed runs.
		const runs = 5
		let wallSum = 0
		let gpuSum = 0
		let gpuValid = canTimestamp
		for (let i = 0; i < runs; i++) {
			const result = await renderRaytraceFrame(canTimestamp)
			wallSum += result.wallMs
			if (result.gpuMs != null) gpuSum += result.gpuMs
			else gpuValid = false
		}

		lastSnapshot = {
			wallMs: wallSum / runs,
			gpuMs: gpuValid ? gpuSum / runs : null,
			width: framebuffer.width,
			height: framebuffer.height,
		}
	} finally {
		snapshotStatus = ''
		snapshotBusy = false
		resumeLoop()
	}
}

/**
 * Renders a single raytraced frame. Optionally brackets the pass with GPU
 * timestamps for a precise compute-pass duration.
 */
async function renderRaytraceFrame(
	measureGpu: boolean
): Promise<{ wallMs: number; gpuMs: number | null }> {
	const useTimestamps = measureGpu && timestamp != null

	const canvasTexture = context.getCurrentTexture()
	const encoder = device.createCommandEncoder()

	const t0 = performance.now()
	raytracer.run(
		encoder,
		useTimestamps
			? {
					querySet: timestamp!.querySet,
					beginningOfPassWriteIndex: 0,
					endOfPassWriteIndex: 1,
				}
			: undefined
	)
	const tonemapper = new Tonemapper(
		device,
		common,
		framebuffer,
		canvasTexture
	)
	tonemapper.run(encoder)

	if (useTimestamps) {
		encoder.resolveQuerySet(
			timestamp!.querySet,
			0,
			2,
			timestamp!.resolveBuffer,
			0
		)
		encoder.copyBufferToBuffer(
			timestamp!.resolveBuffer,
			0,
			timestamp!.resultBuffer,
			0,
			timestamp!.resultBuffer.size
		)
	}

	device.queue.submit([encoder.finish()])
	await device.queue.onSubmittedWorkDone()
	const wallMs = performance.now() - t0

	let gpuMs: number | null = null
	if (useTimestamps) {
		await timestamp!.resultBuffer.mapAsync(GPUMapMode.READ)
		const times = new BigInt64Array(
			timestamp!.resultBuffer.getMappedRange()
		)
		const deltaNs = Number(times[1] - times[0])
		timestamp!.resultBuffer.unmap()
		if (deltaNs > 0) gpuMs = deltaNs / 1e6
	}

	return { wallMs, gpuMs }
}

// --- CPU Sequential Render --------------------------------------------------
// Renders the same frame one pixel at a time on a single CPU core (in a Web
// Worker), as a sequential baseline for GPU speedup comparison.

let cpuStatus = ''
let lastCpu: CpuResult | null = null
let cpuBusy = false

/* Assembles a CPU raytrace request from the current scene and parameters. */
function buildCpuRequest(
	type: CpuRequestType,
	lightmap: Uint16Array,
	lightmapSize: number,
	lightmapLayers: number,
	[renderW, renderH]: [number, number]
): CpuRaytraceRequest {
	// Sequential renders the whole image; parallel splits rows at runtime.
	const [startY, endY] = type === 'sequential' ? [0, renderH] : [-1, -1]
	return {
		width: renderW,
		height: renderH,
		invMvp: new Float32Array(common.invMvp),
		quadData: scene.quadData,
		quadCount: scene.quads.length,
		sphereData: scene.sphereData,
		sphereCount: scene.spheres.length,
		lightmap,
		lightmapSize,
		lightmapLayers,
		lightIntensity: params.lightIntensity,
		checkerQuad: scene.checkerboardQuadIndex,
		seed: new Uint32Array([
			(Math.random() * 0xffffffff) >>> 0,
			(Math.random() * 0xffffffff) >>> 0,
			(Math.random() * 0xffffffff) >>> 0,
		]),
		reflectionRays: params.reflectionRays, // Match GPU's NumReflectionRays
		missBrightness: 0, // CPU snapshot — dark background
		type,
		startY,
		endY,
	}
}

async function runCpuRender(type: CpuRequestType = 'sequential') {
	if (cpuBusy || snapshotBusy || benchmarkBusy) return
	cpuBusy = true
	cpuStatus = 'reading lightmap…'
	dismissOverlay()
	pauseLoop()
	updateDiagnostics()

	try {
		common.lightIntensity = params.lightIntensity
		common.missBrightness = 0 // dark background for the snapshot
		common.update({ view: lastView, aspect: canvas.width / canvas.height })

		const lm = await radiosity.readLightmap()

		const [renderW, renderH] = scaledRenderSize()
		const request = buildCpuRequest(type, lm.data, lm.size, lm.layers, [
			renderW,
			renderH,
		])

		cpuRaytracer.setStrategy(
			type === 'sequential'
				? new SequentialCpuRender()
				: new ParallelCpuRender(params.cpuCores)
		)

		cpuStatus = 'rendering… 0%'
		updateDiagnostics()

		const ms = await cpuRaytracer.render(request, (value) => {
			cpuStatus = `rendering… ${Math.round(value * 100)}%`
			updateDiagnostics()
		})

		lastCpu = { ms, width: request.width, height: request.height }
		cpuStatus = ''
		updateDiagnostics()

		armOverlayDismissal()
	} catch (err) {
		console.error(err)
		cpuStatus = 'failed (see console)'
		updateDiagnostics()
		resumeLoop()
	} finally {
		cpuBusy = false
	}
}

/** Hides the CPU overlay and resumes the live render loop. */
function dismissOverlay() {
	if (!cpuRaytracer.isShowing) return
	cpuRaytracer.hide()
	window.removeEventListener('pointerdown', dismissOverlay)
	window.removeEventListener('keydown', dismissOverlay)
	window.removeEventListener('wheel', dismissOverlay)
	resumeLoop()
}

function armOverlayDismissal() {
	window.addEventListener('pointerdown', dismissOverlay)
	window.addEventListener('keydown', dismissOverlay)
	window.addEventListener('wheel', dismissOverlay)
}

// --- Benchmark ---
// Renders multiple frames of the same image

let benchmarkBusy = false

async function runBenchmark(counts: RunCounts) {
	if (benchmarkBusy || snapshotBusy || cpuBusy) return
	benchmarkBusy = true
	dismissOverlay()
	pauseLoop()
	benchmark.setRunning(true)
	benchmark.setStatus('preparing…')
	updateDiagnostics()

	// get settings
	common.lightIntensity = params.lightIntensity
	common.missBrightness = 0 // dark background for snapshots in the benchmark
	common.update({ view: lastView, aspect: canvas.width / canvas.height })

	const modes: ModeResult[] = []

	try {
		if (counts.gpu > 0) {
			modes.push(await benchmarkGpu(counts.gpu))
		}
		if (counts.cpuSequential > 0) {
			modes.push(await benchmarkCpu('sequential', counts.cpuSequential))
		}
		if (counts.cpuParallel > 0) {
			modes.push(await benchmarkCpu('parallel', counts.cpuParallel))
		}

		const results: BenchmarkResults = {
			modes,
			settings: snapshotSettings(),
		}
		benchmark.setResults(results)
		benchmark.setStatus(`done — ${describeResults(results)}`)
	} catch (err) {
		console.error(err)
		benchmark.setStatus('failed (see console)')
	} finally {
		benchmark.setRunning(false)
		benchmarkBusy = false
		dismissOverlay()
		resumeLoop()
	}
}

/* Times `runs` GPU raytrace frames. */
async function benchmarkGpu(runs: number): Promise<ModeResult> {
	// await renderRaytraceFrame(false) // warm-up

	const wallMs: number[] = []
	const gpuMs: (number | null)[] = []
	for (let i = 0; i < runs; i++) {
		benchmark.setStatus(`GPU run ${i + 1}/${runs}…`)
		const result = await renderRaytraceFrame(canTimestamp)
		wallMs.push(result.wallMs)
		gpuMs.push(result.gpuMs)
	}

	return {
		label: 'GPU',
		key: 'gpu',
		width: framebuffer.width,
		height: framebuffer.height,
		wallMs,
		gpuMs,
		cores: null,
	}
}

/* Times `runs` CPU raytrace frames for the given `type`. */
async function benchmarkCpu(
	type: CpuRequestType,
	runs: number
): Promise<ModeResult> {
	const cores = type === 'sequential' ? 1 : params.cpuCores
	cpuRaytracer.setStrategy(
		type === 'sequential'
			? new SequentialCpuRender()
			: new ParallelCpuRender(cores)
	)

	const [renderW, renderH] = scaledRenderSize()
	const wallMs: number[] = []

	for (let i = 0; i < runs; i++) {
		benchmark.setStatus(`CPU ${type} run ${i + 1}/${runs}…`)
		// Read a fresh lightmap each run: the sequential worker transfers (and
		// neuters) the lightmap buffer it is handed.
		const lm = await radiosity.readLightmap()
		const request = buildCpuRequest(type, lm.data, lm.size, lm.layers, [
			renderW,
			renderH,
		])
		const ms = await cpuRaytracer.render(request, () => {})
		wallMs.push(ms)
	}

	return {
		label: type === 'sequential' ? 'CPU sequential' : 'CPU parallel',
		key: type === 'sequential' ? 'cpu_sequential' : 'cpu_parallel',
		width: renderW,
		height: renderH,
		wallMs,
		gpuMs: null,
		cores,
	}
}

/** Captures the render settings in effect, for the CSV's per-row context columns. */
function snapshotSettings(): Record<string, string | number> {
	return {
		light_intensity: params.lightIntensity,
		reflection_rays: params.reflectionRays,
		radiosity_workgroups_per_frame: params.radiosityWorkgroupsPerFrame,
		render_scale: params.renderScale,
		raytracer_workgroup: params.raytracerWorkgroup,
		photons_per_workgroup: params.photonsPerWorkgroup,
	}
}

function describeResults(results: BenchmarkResults): string {
	return results.modes
		.filter((m) => m.wallMs.length > 0)
		.map((m) => `${m.label}×${m.wallMs.length}`)
		.join(', ')
}

resumeLoop()
