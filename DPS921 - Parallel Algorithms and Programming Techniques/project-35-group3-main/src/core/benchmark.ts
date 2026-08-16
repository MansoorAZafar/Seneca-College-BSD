import { GUI, GUIController } from 'dat.gui'

/* How many frames to render for each backend during a benchmark. */
export interface RunCounts {
	gpu: number
	cpuSequential: number
	cpuParallel: number
}

/* Per-run samples */
export interface ModeResult {
	label: string
	key: string
	width: number
	height: number
	/* Wall-clock time per run (ms). */
	wallMs: number[]
	/* GPU pass time per run (ms), or null for CPU modes. */
	gpuMs: (number | null)[] | null
	/* CPU cores used (1 for sequential, N for parallel), or null when N/A (GPU). */
	cores: number | null
}

export interface BenchmarkResults {
	modes: ModeResult[]
	/* Render settings in effect during the run; one per CSV row. */
	settings: Record<string, string | number>
}

interface SliderSpec {
	key: keyof RunCounts
	label: string
	min: number
	max: number
	value: number
}

const SLIDERS: SliderSpec[] = [
	{ key: 'gpu', label: 'GPU runs', min: 0, max: 50, value: 10 },
	{
		key: 'cpuSequential',
		label: 'CPU sequential runs',
		min: 0,
		max: 20,
		value: 3,
	},
	{
		key: 'cpuParallel',
		label: 'CPU parallel runs',
		min: 0,
		max: 20,
		value: 3,
	},
]

export default class Benchmark {
	private readonly counts: RunCounts = {
		gpu: 10,
		cpuSequential: 3,
		cpuParallel: 3,
	}
	private readonly state = { status: 'idle' }
	private readonly folder: GUI
	private readonly runController: GUIController
	private readonly summary: Record<string, string> = {}
	private resultControllers: GUIController[] = []
	private lastResults: BenchmarkResults | null = null

	constructor(
		gui: GUI,
		private readonly onRun: (counts: RunCounts) => void
	) {
		this.folder = gui.addFolder('Benchmark')

		for (const spec of SLIDERS) {
			this.counts[spec.key] = spec.value
			this.folder
				.add(this.counts, spec.key, spec.min, spec.max, 1)
				.name(spec.label)
		}

		const actions = {
			run: () => this.onRun(this.getCounts()),
			exportCsv: () => this.exportCsv(),
		}
		this.runController = this.folder
			.add(actions, 'run')
			.name('Run benchmark')

		const statusController = this.folder
			.add(this.state, 'status')
			.name('Status')
			.listen()
		makeReadOnly(statusController)

		this.folder.add(actions, 'exportCsv').name('Export CSV')

		this.folder.open()
	}

	/* state of the slider values. */
	getCounts(): RunCounts {
		return { ...this.counts }
	}

	setRunning(running: boolean) {
		this.runController.name(running ? 'Running…' : 'Run benchmark')
	}

	setStatus(text: string) {
		this.state.status = text
	}

	setResults(results: BenchmarkResults) {
		this.lastResults = results

		for (const controller of this.resultControllers) {
			this.folder.remove(controller)
		}
		this.resultControllers = []

		for (const mode of results.modes) {
			if (mode.wallMs.length === 0) continue
			// Prefer precise GPU pass times when every run reported one.
			const series = pickSeries(mode)
			this.summary[mode.key] =
				`${avg(series.values).toFixed(2)} ms (avg. of ${series.values.length})`

			const controller = this.folder
				.add(this.summary, mode.key)
				.name(`${mode.label}${series.suffix}`)
			makeReadOnly(controller)
			this.resultControllers.push(controller)
		}
	}

	private exportCsv() {
		if (!this.lastResults) {
			this.setStatus('nothing to export yet')
			return
		}

		// settings
		const settingKeys = Object.keys(this.lastResults.settings)
		const settingValues = settingKeys.map((k) =>
			csvCell(this.lastResults!.settings[k])
		)

		const header = [
			'mode',
			'run',
			'wall_ms',
			'gpu_ms',
			'cpu_cores',
			'width',
			'height',
			...settingKeys,
		]
		const rows: string[] = [header.join(',')]
		for (const mode of this.lastResults.modes) {
			for (let i = 0; i < mode.wallMs.length; i++) {
				const gpu = mode.gpuMs?.[i]
				const gpuCell = gpu != null ? gpu.toFixed(4) : ''
				rows.push(
					[
						mode.key,
						i + 1,
						mode.wallMs[i].toFixed(4),
						gpuCell,
						mode.cores ?? '',
						mode.width,
						mode.height,
						...settingValues,
					].join(',')
				)
			}
		}

		const blob = new Blob([rows.join('\n') + '\n'], {
			type: 'text/csv',
		})
		const url = URL.createObjectURL(blob)
		const a = document.createElement('a')
		a.href = url
		a.download = `${this.buildFileName()}.csv`
		a.click()
		URL.revokeObjectURL(url)
	}

	// name of the csv file for parsing
	private buildFileName(): string {
		const counts = this.runCountsFromResults()
		const settings = this.lastResults!.settings
		const settingTokens = Object.keys(settings).map(
			(key) => `${abbreviate(key)}${fileSafe(settings[key])}`
		)
		return [
			'benchmark',
			`gpu${counts.gpu}`,
			`cpuS${counts.cpuSequential}`,
			`cpuP${counts.cpuParallel}`,
			...settingTokens,
		].join('_')
	}

	private runCountsFromResults(): RunCounts {
		const samples = (key: string) =>
			this.lastResults!.modes.find((m) => m.key === key)?.wallMs.length ??
			0
		return {
			gpu: samples('gpu'),
			cpuSequential: samples('cpu_sequential'),
			cpuParallel: samples('cpu_parallel'),
		}
	}
}

function makeReadOnly(controller: GUIController) {
	const input = controller.domElement.querySelector('input')
	if (input) input.readOnly = true
}

function abbreviate(key: string): string {
	return key
		.split('_')
		.map((word) => word[0] ?? '')
		.join('')
}

/* Strips characters that are awkward in file names, keeping alphanumerics and dots. */
function fileSafe(value: string | number): string {
	return String(value).replace(/[^0-9a-zA-Z.]/g, '')
}

/* Renders a CSV cell, quoting values that contain a comma or double-quote. */
function csvCell(value: string | number): string {
	const s = String(value)
	return /[",\n]/.test(s) ? `"${s.replace(/"/g, '""')}"` : s
}

/* Pick GPU pass times if available. */
function pickSeries(mode: ModeResult): { values: number[]; suffix: string } {
	if (mode.gpuMs && mode.gpuMs.length === mode.wallMs.length) {
		const gpu = mode.gpuMs.filter((v): v is number => v != null)
		if (gpu.length === mode.wallMs.length) {
			return { values: gpu, suffix: ' (GPU pass)' }
		}
	}
	return { values: mode.wallMs, suffix: '' }
}

function avg(xs: number[]): number {
	return xs.length ? xs.reduce((a, b) => a + b, 0) / xs.length : 0
}
