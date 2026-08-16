/** Main-thread side of the CPU sequential raytracer (owns the worker + overlay canvas). */

import type { CpuRaytraceRequest } from './cpuRaytracerShared'
import {
	CpuRenderStrategy,
	SequentialCpuRender,
} from './cpuRayTracerStrategies'

export default class CpuRaytracer {
	// private readonly workers: Worker[];
	private renderStrategy: CpuRenderStrategy
	private readonly canvas: HTMLCanvasElement
	private readonly ctx: CanvasRenderingContext2D
	private busy = false

	constructor() {
		// Default strategy is Sequential
		this.setStrategy(new SequentialCpuRender())

		this.canvas = document.createElement('canvas')
		this.canvas.className = 'cpu-overlay'
		this.canvas.style.display = 'none'
		document.body.append(this.canvas)
		this.ctx = this.canvas.getContext('2d')!
	}

	/** Whether the CPU-rendered frame is currently displayed over the live view. */
	get isShowing(): boolean {
		return this.canvas.style.display !== 'none'
	}

	setStrategy(strategy: CpuRenderStrategy) {
		this.renderStrategy = strategy
	}

	hide() {
		this.canvas.style.display = 'none'
	}

	setBusy(state: boolean) {
		this.busy = state
	}

	/**
	 * Renders one frame on the worker. Streams bands back as they finish so the
	 * overlay fills in live. Resolves with the pure compute time (ms).
	 */
	render(
		request: CpuRaytraceRequest,
		onProgress: (value: number) => void
	): Promise<number> {
		if (this.busy) {
			return Promise.reject(new Error('CPU raytracer is already running'))
		}
		this.busy = true

		const { width, height } = request

		this.canvas.width = width
		this.canvas.height = height
		this.ctx.clearRect(0, 0, width, height)
		this.canvas.style.display = 'block'

		return this.renderStrategy.render({
			request,
			onProgress,
			canvas: this.canvas,
			ctx: this.ctx,
			hide: this.hide.bind(this),
			setBusy: this.setBusy.bind(this),
		})
	}
}
