import { vec3, Vec3 } from 'wgpu-matrix'

// The scene is a list of flat rectangles ("quads"). Every wall, box face, light
// panel, and floor is one Quad. Renderers intersect rays against this list.

/** Returns the component-wise reciprocal of `v`, scaled by 1/|v|². Used to
 *  project a point onto a quad edge, yielding UVs in [-1..1]. */
function reciprocal(v: Vec3) {
	const s = 1 / vec3.lenSq(v)
	return vec3.mul(vec3.fromValues(s, s, s), v)
}

/** A flat rectangle in space. `center` ± `right` ± `up` gives the four corners;
 *  cross(right, up) gives the facing normal. */
interface Quad {
	center: Vec3 // World-space center
	right: Vec3 // Half-edge along local U (length = half-width)
	up: Vec3 // Half-edge along local V (length = half-height)
	color: Vec3 // Diffuse surface color
	emissive?: number // 0 = normal, 1 = light emitter
	metallic?: number // 0 = non-metal (dielectric), 1 = reflective
	roughness?: number // 0 = smooth (sharp reflections), 1 = rough (diffuse reflection)
}

/** A glass (dielectric) sphere. Refracts rays via Snell's law and reflects via Fresnel. */
interface Sphere {
	center: Vec3
	radius: number
	color: Vec3 // Tint of transmitted/reflected light; (1,1,1) = clear glass
	ior: number // Index of refraction (1.5 ≈ window glass)
}

//      ─────────┐
//     ╱  +Y    ╱│
//    ┌────────┐ │
//    │        │+X
//    │   +Z   │ │
//    │        │╱
//    └────────┘
// The six faces of a cuboid, in the order `box()` emits them.
enum CubeFace {
	PositiveX,
	PositiveY,
	PositiveZ,
	NegativeX,
	NegativeY,
	NegativeZ,
}

/**
 * Builds a cuboid as six Quads.
 * @param type - "concave" (normals inward, for a hollow room) or "convex" (outward, for a solid block)
 * @param rotation - Y-axis spin in radians
 * @param color - single color or per-face array
 */
function box(params: {
	center: Vec3
	width: number
	height: number
	depth: number
	rotation: number
	color: Vec3 | Vec3[]
	type: 'convex' | 'concave'
	metallic?: number
	roughness?: number
}): Quad[] {
	const x = vec3.fromValues(
		Math.cos(params.rotation) * (params.width / 2),
		0,
		Math.sin(params.rotation) * (params.depth / 2)
	)
	const y = vec3.fromValues(0, params.height / 2, 0)
	const z = vec3.fromValues(
		Math.sin(params.rotation) * (params.width / 2),
		0,
		-Math.cos(params.rotation) * (params.depth / 2)
	)
	const colors =
		params.color instanceof Array
			? params.color
			: new Array(6).fill(params.color)
	// Flip `right` for convex boxes so the normal points outward.
	const sign = (v: Vec3) => {
		return params.type === 'concave' ? v : vec3.negate(v)
	}
	const faces: Quad[] = [
		{
			center: vec3.add(params.center, x),
			right: sign(vec3.negate(z)),
			up: y,
			color: colors[CubeFace.PositiveX],
		},
		{
			center: vec3.add(params.center, y),
			right: sign(x),
			up: vec3.negate(z),
			color: colors[CubeFace.PositiveY],
		},
		{
			center: vec3.add(params.center, z),
			right: sign(x),
			up: y,
			color: colors[CubeFace.PositiveZ],
		},
		{
			center: vec3.sub(params.center, x),
			right: sign(z),
			up: y,
			color: colors[CubeFace.NegativeX],
		},
		{
			center: vec3.sub(params.center, y),
			right: sign(x),
			up: z,
			color: colors[CubeFace.NegativeY],
		},
		{
			center: vec3.sub(params.center, z),
			right: sign(vec3.negate(x)),
			up: y,
			color: colors[CubeFace.NegativeZ],
		},
	]
	return faces.map((face) => ({
		...face,
		metallic: params.metallic,
		roughness: params.roughness,
	}))
}

// 2×2 emissive panel just below the ceiling (y = 9.95). The only light source.
const light: Quad = {
	center: vec3.fromValues(0, 9.95, 0),
	right: vec3.fromValues(1, 0, 0),
	up: vec3.fromValues(0, 0, 1),
	color: vec3.fromValues(5.0, 5.0, 5.0),
	emissive: 1.0,
}

// Ground plane below the box. Checkerboard drawn procedurally in shaders.
// const floor: Quad = {
// 	center: vec3.fromValues(0, -0.02, 0),
// 	right: vec3.fromValues(20, 0, 0),
// 	up: vec3.fromValues(0, 0, -20),
// 	color: vec3.fromValues(0.5, 0.5, 0.5),
// }

/** Holds the Cornell-box scene geometry as a flat list of quads. */
export default class Scene {
	readonly quadBuffer: GPUBuffer
	/** CPU-side copy of packed quad data (16 floats per quad), matching the GPU buffer. */
	readonly quadData: Float32Array
	readonly sphereBuffer: GPUBuffer
	/** CPU-side copy of packed sphere data (8 floats per sphere). */
	readonly sphereData: Float32Array
	readonly spheres: Sphere[] = [
		// Glass sphere resting on top of the short blue cube. Cube top is at y=3
		// (cube center y=1.5 + height 3 / 2); sphere bottom at y=2.95 sinks 0.05
		// into the cube to read as "resting" without z-fighting at the contact.
		{
			center: vec3.fromValues(1.5, 4.0, 1),
			radius: 1.05,
			color: vec3.fromValues(1, 1, 1),
			ior: 1.5,
		},
	]
	readonly quads = [
		// 10×10×10 hollow room centered at (0,5,0). Two opposing walls are colored
		// (classic Cornell red/green); the rest are neutral gray.
		...box({
			center: vec3.fromValues(0, 5, 0),
			width: 10,
			height: 10,
			depth: 10,
			rotation: 0,
			color: [
				vec3.fromValues(0.0, 0.5, 0.0), // +X: green
				vec3.fromValues(0.5, 0.5, 0.5), // +Y: ceiling (gray)
				vec3.fromValues(0.5, 0.5, 0.5), // +Z: gray
				vec3.fromValues(0.5, 0.0, 0.0), // -X: red
				vec3.fromValues(0.5, 0.5, 0.5), // -Y: floor (gray)
				vec3.fromValues(0.5, 0.5, 0.5), // -Z: gray
			],
			type: 'concave',
		}),
		// Short block : 3x3x3
		// Brushed metal: rough blurry reflection
		...box({
			center: vec3.fromValues(1.5, 1.5, 1),
			width: 3,
			height: 3,
			depth: 3,
			rotation: 0.3,
			color: vec3.fromValues(0.3, 0.3, 0.9),
			type: 'convex',
			metallic: 0.6,
			roughness: 0.15,
		}),
		// Tall block: 3×6×3
		// Polished mirror metal
		...box({
			center: vec3.fromValues(-2, 3, -2),
			width: 3,
			height: 6,
			depth: 3,
			rotation: -0.4,
			color: vec3.fromValues(0.8, 0.8, 0.8),
			type: 'convex',
			metallic: 0.9,
			roughness: 0.0,
		}),
		light,
		// floor, // TEMPORARILY DISABLED
	]
	readonly lightCenter = light.center
	readonly lightWidth = vec3.len(light.right) * 2
	readonly lightHeight = vec3.len(light.up) * 2
	// TEMPORARILY 0xffffffff (no quad) while floor is disabled.
	readonly checkerboardQuadIndex = 0xffffffff

	constructor(device: GPUDevice) {
		const quadFloats = 20
		const quadStride = quadFloats * 4
		const quadBuffer = device.createBuffer({
			size: quadStride * this.quads.length,
			usage: GPUBufferUsage.STORAGE,
			mappedAtCreation: true,
		})
		// 20 floats per quad, layout:
		//   [0..3]   plane: (normal.xyz, -dot(normal, center))
		//   [4..7]   right plane: projects point to U coordinate
		//   [8..11]  up plane: projects point to V coordinate
		//   [12..14] diffuse color
		//   [15]     emissive
		//   [16..19] material: (metallic, roughness, reserved, reserved)
		const quadData = new Float32Array(quadFloats * this.quads.length)
		let quadDataOffset = 0
		for (let quadIdx = 0; quadIdx < this.quads.length; quadIdx++) {
			const quad = this.quads[quadIdx]

			const normal = vec3.normalize(vec3.cross(quad.right, quad.up))
			quadData[quadDataOffset++] = normal[0]
			quadData[quadDataOffset++] = normal[1]
			quadData[quadDataOffset++] = normal[2]
			quadData[quadDataOffset++] = -vec3.dot(normal, quad.center)

			const invRight = reciprocal(quad.right)
			quadData[quadDataOffset++] = invRight[0]
			quadData[quadDataOffset++] = invRight[1]
			quadData[quadDataOffset++] = invRight[2]
			quadData[quadDataOffset++] = -vec3.dot(invRight, quad.center)

			const invUp = reciprocal(quad.up)
			quadData[quadDataOffset++] = invUp[0]
			quadData[quadDataOffset++] = invUp[1]
			quadData[quadDataOffset++] = invUp[2]
			quadData[quadDataOffset++] = -vec3.dot(invUp, quad.center)

			quadData[quadDataOffset++] = quad.color[0]
			quadData[quadDataOffset++] = quad.color[1]
			quadData[quadDataOffset++] = quad.color[2]
			quadData[quadDataOffset++] = quad.emissive ?? 0

			quadData[quadDataOffset++] = quad.metallic ?? 0
			quadData[quadDataOffset++] = quad.roughness ?? 0.05
			quadData[quadDataOffset++] = 0 // reserved
			quadData[quadDataOffset++] = 0 // reserved
		}

		new Float32Array(quadBuffer.getMappedRange()).set(quadData)
		quadBuffer.unmap()
		this.quadData = quadData
		this.quadBuffer = quadBuffer

		// Sphere buffer: 8 floats per sphere
		//   [0..3] (center.xyz, radius)
		//   [4..7] (color.xyz, ior)
		// Pad to at least one slot so a sphere-less scene still produces a
		// valid (non-empty) storage buffer; a zero-radius sphere never hits.
		const sphereFloats = 8
		const sphereStride = sphereFloats * 4
		const sphereCount = Math.max(1, this.spheres.length)
		const sphereBuffer = device.createBuffer({
			size: sphereStride * sphereCount,
			usage: GPUBufferUsage.STORAGE,
			mappedAtCreation: true,
		})
		const sphereData = new Float32Array(sphereFloats * sphereCount)
		let sphereDataOffset = 0
		for (const sphere of this.spheres) {
			sphereData[sphereDataOffset++] = sphere.center[0]
			sphereData[sphereDataOffset++] = sphere.center[1]
			sphereData[sphereDataOffset++] = sphere.center[2]
			sphereData[sphereDataOffset++] = sphere.radius
			sphereData[sphereDataOffset++] = sphere.color[0]
			sphereData[sphereDataOffset++] = sphere.color[1]
			sphereData[sphereDataOffset++] = sphere.color[2]
			sphereData[sphereDataOffset++] = sphere.ior
		}
		new Float32Array(sphereBuffer.getMappedRange()).set(sphereData)
		sphereBuffer.unmap()
		this.sphereData = sphereData
		this.sphereBuffer = sphereBuffer
	}
}
