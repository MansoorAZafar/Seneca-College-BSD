import { CpuRaytraceMessage, CpuRaytraceRequest } from './cpuRaytracerShared'
type RenderProps = {
	request: CpuRaytraceRequest
	onProgress: (value: number) => void
	canvas: HTMLCanvasElement
	ctx: CanvasRenderingContext2D
	hide: () => void
	setBusy: (state: boolean) => void
}

interface CpuRenderStrategy {
	render(props: RenderProps): Promise<number>
}

class SequentialCpuRender implements CpuRenderStrategy {
	private readonly worker: Worker

	constructor() {
		this.worker = new Worker(
			new URL('./cpuRaytracer.worker.ts', import.meta.url),
			{ type: 'module' }
		)
	}

	render(req: RenderProps) {
		const { width, height } = req.request
		const pending: Extract<CpuRaytraceMessage, { type: 'band' }>[] = []
		let rafHandle = 0

		const flush = () => {
			rafHandle = 0
			for (const band of pending) {
				const image = req.ctx.createImageData(width, band.height)
				image.data.set(band.pixels)

				req.ctx.putImageData(image, 0, band.y)
			}
			pending.length = 0
		}

		return new Promise<number>((resolve, reject) => {
			const cleanup = () => {
				this.worker.removeEventListener('message', onMessage)
				this.worker.removeEventListener('error', onError)

				req.setBusy(false)
			}
			const onMessage = (event: MessageEvent<CpuRaytraceMessage>) => {
				const msg = event.data
				if (msg.type === 'band') {
					pending.push(msg)
					req.onProgress((msg.y + msg.height) / height)

					if (!rafHandle) rafHandle = requestAnimationFrame(flush)
					return
				}
				cleanup()
				if (rafHandle) cancelAnimationFrame(rafHandle)

				flush()
				resolve(msg.ms)
			}
			const onError = (err: ErrorEvent) => {
				cleanup()
				if (rafHandle) cancelAnimationFrame(rafHandle)

				req.hide()
				reject(err.error ?? new Error(err.message))
			}

			this.worker.addEventListener('message', onMessage)
			this.worker.addEventListener('error', onError)

			this.worker.postMessage(req.request, [req.request.lightmap.buffer])
		})
	}
}

class ParallelCpuRender implements CpuRenderStrategy {
	private readonly workers: Worker[]

	constructor(cores?: number) {
		const nthreads = Math.max(
			1,
			cores ?? (navigator.hardwareConcurrency ?? 4) - 1
		)

		// prealloc size cuz its better
		this.workers = new Array(nthreads)

		for (let i = 0; i < nthreads; ++i) {
			this.workers[i] = new Worker(
				new URL('./cpuRaytracer.worker.ts', import.meta.url),
				{ type: 'module' }
			)
		}
	}

	render(req: RenderProps) {
		const { width, height } = req.request
		const pending: Extract<CpuRaytraceMessage, { type: 'band' }>[] = []
		let rafHandle = 0

		const flush = () => {
			rafHandle = 0
			for (const band of pending) {
				const image = req.ctx.createImageData(width, band.height)
				image.data.set(band.pixels)

				req.ctx.putImageData(image, 0, band.y)
			}
			pending.length = 0
		}

		const numberOfWorkers = this.workers.length
		const rowsPerWorker = Math.ceil(height / numberOfWorkers)

		return new Promise<number>((resolve, reject) => {
			let numberOfFinishedWorkers = 0
			let totalTimeTaken = 0
			let completedRows = 0

			const cleanup = () => {
				for (const worker of this.workers) {
					worker.removeEventListener('message', onMessage)
					worker.removeEventListener('error', onError)
				}

				req.setBusy(false)
			}

			const onMessage = (event: MessageEvent<CpuRaytraceMessage>) => {
				const msg = event.data
				if (msg.type === 'band') {
					pending.push(msg)
					completedRows += msg.height
					req.onProgress(completedRows / height)

					if (!rafHandle) rafHandle = requestAnimationFrame(flush)
					return
				}

				++numberOfFinishedWorkers
				totalTimeTaken = Math.max(totalTimeTaken, msg.ms)

				if (numberOfFinishedWorkers == numberOfWorkers) {
					// Cleanup ONLY when all workers are done
					cleanup()
					if (rafHandle) cancelAnimationFrame(rafHandle)

					flush()
					resolve(totalTimeTaken)
				}
			}

			const onError = (err: ErrorEvent) => {
				cleanup()
				if (rafHandle) cancelAnimationFrame(rafHandle)

				req.hide()
				reject(err.error ?? new Error(err.message))
			}

			for (let i = 0; i < numberOfWorkers; ++i) {
				this.workers[i].addEventListener('message', onMessage)
				this.workers[i].addEventListener('error', onError)

				const startY = i * rowsPerWorker
				const endY = Math.min(height, startY + rowsPerWorker)

				const lightmapBufferCpy = new Uint16Array(req.request.lightmap)
				const request: CpuRaytraceRequest = {
					...req.request,
					startY,
					endY,
				}
				const workerRequest = {
					...request,
					lightmap: lightmapBufferCpy,
				}

				this.workers[i].postMessage(workerRequest)
			}
		})
	}
}

export { type CpuRenderStrategy, SequentialCpuRender, ParallelCpuRender }
