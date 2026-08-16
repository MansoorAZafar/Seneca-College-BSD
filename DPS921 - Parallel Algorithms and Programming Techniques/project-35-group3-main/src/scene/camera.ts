// Note: This code doesn't use the 'dst' parameter of wgpu-matrix functions,
// so it produces many temporary vectors/matrices. This is intentional for readability.
import { Mat4, Vec3, Vec4, mat4, vec3 } from 'wgpu-matrix'
import Input from './input'

/** Common interface for camera implementations. */
export default interface Camera {
	/** Updates the camera from user input and returns the view matrix. */
	update(delta_time: number, input: Input): Mat4

	/** The camera matrix (inverse of the view matrix). */
	matrix: Mat4
	/** Column vector 0: right direction. */
	right: Vec4
	/** Column vector 1: up direction. */
	up: Vec4
	/** Column vector 2: back direction. */
	back: Vec4
	/** Column vector 3: position. */
	position: Vec4
}

/** Base class with shared camera matrix operations. */
class CameraBase {
	// Camera matrix (16 floats).
	private matrix_ = new Float32Array([
		1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
	])
	private readonly view_ = mat4.create()

	// Typed array views into matrix_ for column access.
	private right_ = new Float32Array(this.matrix_.buffer, 4 * 0, 4)
	private up_ = new Float32Array(this.matrix_.buffer, 4 * 4, 4)
	private back_ = new Float32Array(this.matrix_.buffer, 4 * 8, 4)
	private position_ = new Float32Array(this.matrix_.buffer, 4 * 12, 4)

	get matrix() {
		return this.matrix_
	}
	set matrix(mat: Mat4) {
		mat4.copy(mat, this.matrix_)
	}

	get view() {
		return this.view_
	}
	set view(mat: Mat4) {
		mat4.copy(mat, this.view_)
	}

	get right() {
		return this.right_
	}
	set right(vec: Vec3) {
		vec3.copy(vec, this.right_)
	}

	get up() {
		return this.up_
	}
	set up(vec: Vec3) {
		vec3.copy(vec, this.up_)
	}

	get back() {
		return this.back_
	}
	set back(vec: Vec3) {
		vec3.copy(vec, this.back_)
	}

	get position() {
		return this.position_
	}
	set position(vec: Vec3) {
		vec3.copy(vec, this.position_)
	}
}

/** First-person-shooter style camera (WASD + mouse look). */
export class WASDCamera extends CameraBase implements Camera {
	private pitch = 0
	private yaw = 0
	private readonly velocity_ = vec3.create()

	movementSpeed = 10
	rotationSpeed = 1
	/** Friction coefficient [0..1]: 0 = no friction, 1 = instant stop. */
	frictionCoefficient = 0.99

	get velocity() {
		return this.velocity_
	}
	set velocity(vec: Vec3) {
		vec3.copy(vec, this.velocity_)
	}

	constructor(options?: { position?: Vec3; target?: Vec3 }) {
		super()
		if (options && (options.position || options.target)) {
			const position = options.position ?? vec3.create(0, 0, -5)
			const target = options.target ?? vec3.create(0, 0, 0)
			const back = vec3.normalize(vec3.sub(position, target))
			this.recalculateAngles(back)
			this.position = position
		}
	}

	get matrix() {
		return super.matrix
	}

	set matrix(mat: Mat4) {
		super.matrix = mat
		this.recalculateAngles(this.back)
	}

	update(deltaTime: number, input: Input): Mat4 {
		const sign = (positive: boolean, negative: boolean) =>
			(positive ? 1 : 0) - (negative ? 1 : 0)

		this.yaw -= input.analog.x * deltaTime * this.rotationSpeed
		this.pitch -= input.analog.y * deltaTime * this.rotationSpeed

		// Keep yaw in [0..2π] to prevent large accumulation.
		this.yaw = mod(this.yaw, Math.PI * 2)
		// Clamp pitch to [-90°..+90°] to prevent somersaults.
		this.pitch = clamp(this.pitch, -Math.PI / 2, Math.PI / 2)

		const position = vec3.copy(this.position)

		// Rebuild rotation matrix from yaw/pitch.
		super.matrix = mat4.rotateX(mat4.rotationY(this.yaw), this.pitch)

		// Compute target velocity from digital input.
		const digital = input.digital
		const deltaRight = sign(digital.right, digital.left)
		const deltaUp = sign(digital.up, digital.down)
		const targetVelocity = vec3.create()
		const deltaBack = sign(digital.backward, digital.forward)
		vec3.addScaled(targetVelocity, this.right, deltaRight, targetVelocity)
		vec3.addScaled(targetVelocity, this.up, deltaUp, targetVelocity)
		vec3.addScaled(targetVelocity, this.back, deltaBack, targetVelocity)
		vec3.normalize(targetVelocity, targetVelocity)
		vec3.mulScalar(targetVelocity, this.movementSpeed, targetVelocity)

		// Lerp current velocity toward target (with friction).
		this.velocity = lerp(
			targetVelocity,
			this.velocity,
			Math.pow(1 - this.frictionCoefficient, deltaTime)
		)

		this.position = vec3.addScaled(position, this.velocity, deltaTime)

		// Invert camera matrix -> view matrix.
		this.view = mat4.invert(this.matrix)
		return this.view
	}

	/** Derives yaw/pitch from a direction vector. */
	recalculateAngles(dir: Vec3) {
		this.yaw = Math.atan2(dir[0], dir[2])
		this.pitch = -Math.asin(dir[1])
	}
}

function clamp(x: number, min: number, max: number): number {
	return Math.min(Math.max(x, min), max)
}

function mod(x: number, div: number): number {
	return x - Math.floor(Math.abs(x) / div) * div * Math.sign(x)
}

function lerp(a: Vec3, b: Vec3, s: number): Vec3 {
	return vec3.addScaled(a, vec3.sub(b, a), s)
}
