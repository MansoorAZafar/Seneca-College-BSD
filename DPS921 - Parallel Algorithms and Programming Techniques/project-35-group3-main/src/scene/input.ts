/** Keyboard, mouse, and touch input handler with a frame-snapshot pattern. */

export default interface Input {
	/** Digital input state - true if key is currently held down. */
	readonly digital: {
		readonly forward: boolean // W
		readonly backward: boolean // S
		readonly left: boolean // A
		readonly right: boolean // D
		readonly up: boolean // Space
		readonly down: boolean // Shift/Ctrl/C
	}
	/** Analog input accumulated since last frame. */
	readonly analog: {
		readonly x: number // Horizontal mouse/touch delta (pixels)
		readonly y: number // Vertical mouse/touch delta (pixels)
		readonly zoom: number // Scroll wheel delta (-1, 0, +1)
		readonly touching: boolean // Mouse button down or touch active
	}
}

/** Function that returns the current Input snapshot and clears analog accumulators. */
export type InputHandler = () => Input

/**
 * Creates an input handler with keyboard + pointer event listeners.
 * Returns a function called each frame to get the current input state.
 * Analog values accumulate between frames and are cleared on read,
 * giving frame-rate-independent mouse deltas.
 */
export function createInputHandler(
	window: Window,
	canvas: HTMLCanvasElement
): InputHandler {
	const digital = {
		forward: false,
		backward: false,
		left: false,
		right: false,
		up: false,
		down: false,
	}

	const analog = {
		x: 0,
		y: 0,
		zoom: 0,
	}
	let mouseDown = false

	// Maps physical key codes (e.code) so WASD works regardless of keyboard layout.
	const setDigital = (e: KeyboardEvent, value: boolean) => {
		switch (e.code) {
			case 'KeyW':
				digital.forward = value
				e.preventDefault()
				e.stopPropagation()
				break
			case 'KeyS':
				digital.backward = value
				e.preventDefault()
				e.stopPropagation()
				break
			case 'KeyA':
				digital.left = value
				e.preventDefault()
				e.stopPropagation()
				break
			case 'KeyD':
				digital.right = value
				e.preventDefault()
				e.stopPropagation()
				break
			case 'Space':
				digital.up = value
				e.preventDefault()
				e.stopPropagation()
				break
			case 'ShiftLeft':
			case 'ControlLeft':
			case 'KeyC':
				digital.down = value
				e.preventDefault()
				e.stopPropagation()
				break
		}
	}

	window.addEventListener('keydown', (e) => setDigital(e, true))
	window.addEventListener('keyup', (e) => setDigital(e, false))

	canvas.style.touchAction = 'pinch-zoom'

	canvas.addEventListener('pointerdown', () => {
		mouseDown = true
	})
	canvas.addEventListener('pointerup', () => {
		mouseDown = false
	})
	canvas.addEventListener('pointermove', (e) => {
		// For mouse: only track when left button is held.
		mouseDown = e.pointerType == 'mouse' ? (e.buttons & 1) !== 0 : true
		if (mouseDown) {
			analog.x += e.movementX
			analog.y += e.movementY
		}
	})

	canvas.addEventListener(
		'wheel',
		(e) => {
			mouseDown = (e.buttons & 1) !== 0
			if (mouseDown) {
				// Only care about direction, use sign to normalize across browsers.
				analog.zoom += Math.sign(e.deltaY)
				e.preventDefault()
				e.stopPropagation()
			}
		},
		{ passive: false }
	)

	// Returns snapshot of current state, then clears analog accumulators.
	return () => {
		const out = {
			digital,
			analog: {
				x: analog.x,
				y: analog.y,
				zoom: analog.zoom,
				touching: mouseDown,
			},
		}
		analog.x = 0
		analog.y = 0
		analog.zoom = 0
		return out
	}
}
