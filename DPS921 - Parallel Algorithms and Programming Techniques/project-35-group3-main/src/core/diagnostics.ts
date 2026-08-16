/** A plain-DOM stats panel (FPS, resolution, camera, snapshot timing). */

export interface SnapshotResult {
	/** GPU raytrace pass time (ms), null if 'timestamp-query' unavailable. */
	gpuMs: number | null
	/** Wall-clock time from submit to completion. */
	wallMs: number
	/** Resolution the snapshot was rendered at. */
	width: number
	height: number
}

export interface CpuResult {
	ms: number
	width: number
	height: number
}

export interface DiagnosticsStats {
	fps: number
	frameMs: number
	width: number
	height: number
	cameraPosition: ArrayLike<number>
	lightIntensity: number
	gpuInfo: string
	snapshotStatus: string
	snapshot: SnapshotResult | null
	cpuStatus: string
	cpu: CpuResult | null
}

export default class Diagnostics {
	private readonly values: Record<string, HTMLElement> = {}
	private readonly spark: HTMLCanvasElement
	private readonly sparkCtx: CanvasRenderingContext2D
	private readonly history: number[] = []
	private readonly historyMax = 120

	constructor() {
		const root = document.createElement('div')
		root.className = 'diagnostics'

		const title = document.createElement('div')
		title.className = 'diagnostics-title'
		title.textContent = 'Diagnostics'
		root.append(title)

		this.spark = document.createElement('canvas')
		this.spark.className = 'diagnostics-spark'
		this.spark.width = 220
		this.spark.height = 40
		root.append(this.spark)
		this.sparkCtx = this.spark.getContext('2d')!

		for (const key of [
			'FPS',
			'Frame',
			'Resolution',
			'Camera',
			'Light',
			'GPU',
			'GPU snapshot',
			'CPU render',
			'Speedup',
		]) {
			const row = document.createElement('div')
			row.className = 'diagnostics-row'
			const label = document.createElement('span')
			label.className = 'diagnostics-label'
			label.textContent = key
			const value = document.createElement('span')
			value.className = 'diagnostics-value'
			value.textContent = '—'
			row.append(label, value)
			root.append(row)
			this.values[key] = value
		}

		document.body.append(root)
	}

	/** Refreshes all panel values and redraws the frame-time sparkline. */
	update(stats: DiagnosticsStats) {
		this.pushFrameTime(stats.frameMs)

		const [x, y, z] = [
			stats.cameraPosition[0],
			stats.cameraPosition[1],
			stats.cameraPosition[2],
		]
		const megaPixels = (stats.width * stats.height) / 1e6

		this.values['FPS'].textContent = stats.fps.toFixed(1)
		this.values['Frame'].textContent = `${stats.frameMs.toFixed(1)} ms`
		this.values['Resolution'].textContent =
			`${stats.width}×${stats.height} (${megaPixels.toFixed(1)} MP)`
		this.values['Camera'].textContent =
			`${x.toFixed(1)}, ${y.toFixed(1)}, ${z.toFixed(1)}`
		this.values['Light'].textContent = `${stats.lightIntensity.toFixed(2)}×`
		this.values['GPU'].textContent = stats.gpuInfo
		this.values['GPU snapshot'].textContent = formatSnapshot(
			stats.snapshotStatus,
			stats.snapshot
		)
		this.values['CPU render'].textContent = formatCpu(
			stats.cpuStatus,
			stats.cpu
		)
		this.values['Speedup'].textContent = formatSpeedup(
			stats.snapshot,
			stats.cpu
		)
	}

	private pushFrameTime(ms: number) {
		this.history.push(ms)
		if (this.history.length > this.historyMax) this.history.shift()
		this.drawSparkline()
	}

	/** Draws a mini sparkline chart of recent frame times. */
	private drawSparkline() {
		const ctx = this.sparkCtx
		const w = this.spark.width
		const h = this.spark.height
		ctx.clearRect(0, 0, w, h)

		// Scale so the tallest recent frame fills the graph, with a minimum 33ms range.
		const maxMs = Math.max(33, ...this.history)

		// Reference line at 16.7 ms (60 FPS).
		const y60 = h - (16.7 / maxMs) * h
		ctx.strokeStyle = 'rgba(255,255,255,0.18)'
		ctx.lineWidth = 1
		ctx.beginPath()
		ctx.moveTo(0, y60)
		ctx.lineTo(w, y60)
		ctx.stroke()

		ctx.strokeStyle = '#6c7bff'
		ctx.lineWidth = 1.5
		ctx.beginPath()
		this.history.forEach((ms, i) => {
			const x = (i / (this.historyMax - 1)) * w
			const y = h - Math.min(1, ms / maxMs) * h
			if (i === 0) ctx.moveTo(x, y)
			else ctx.lineTo(x, y)
		})
		ctx.stroke()
	}
}

function formatSnapshot(
	status: string,
	snapshot: SnapshotResult | null
): string {
	if (status) return status
	if (!snapshot) return 'press the button'
	const res = `@ ${snapshot.width}×${snapshot.height}`
	if (snapshot.gpuMs != null) {
		return `${snapshot.gpuMs.toFixed(2)} ms GPU · ${snapshot.wallMs.toFixed(1)} ms total ${res}`
	}
	return `${snapshot.wallMs.toFixed(1)} ms total (CPU-timed) ${res}`
}

function formatCpu(status: string, cpu: CpuResult | null): string {
	if (status) return status
	if (!cpu) return 'press the button'
	return `${cpu.ms.toFixed(1)} ms @ ${cpu.width}×${cpu.height}`
}

/** Compares CPU vs GPU time, preferring the precise GPU pass time when available. */
function formatSpeedup(
	snapshot: SnapshotResult | null,
	cpu: CpuResult | null
): string {
	if (!snapshot || !cpu) return 'run both above'
	if (snapshot.width !== cpu.width || snapshot.height !== cpu.height) {
		return 'resolutions differ'
	}
	const gpuMs = snapshot.gpuMs ?? snapshot.wallMs
	if (gpuMs <= 0) return '—'
	const factor = cpu.ms / gpuMs
	const basis = snapshot.gpuMs != null ? 'GPU pass' : 'GPU total'
	return `${factor.toFixed(0)}× faster on GPU (${basis})`
}
