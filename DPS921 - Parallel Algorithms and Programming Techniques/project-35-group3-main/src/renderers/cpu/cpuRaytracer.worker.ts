/** Single-threaded CPU raytracer (port of the GPU raytracer), runs in a Web Worker. */

import type {
	CpuRaytraceRequest,
	CpuRaytraceMessage,
} from './cpuRaytracerShared'

const workerSelf = self as unknown as {
	onmessage: ((e: MessageEvent<CpuRaytraceRequest>) => void) | null
	postMessage: (
		message: CpuRaytraceMessage,
		transfer?: Transferable[]
	) => void
}

const NO_HIT = 0xffffffff
const BAND_ROWS = 16 // Rows per streamed band (balance overhead vs fill-in smoothness)
const QUAD_STRIDE = 20 // Floats per quad (matches scene.ts / the GPU Quad struct)
const SPHERE_STRIDE = 8 // Floats per sphere (matches scene.ts / the GPU Sphere struct)

// --- Module-level state (set once per request) ------------------------------
let quadData: Float32Array
let quadCount = 0
let sphereData: Float32Array
let sphereCount = 0
let lightmap: Float32Array
let lmSize = 0
let lightIntensity = 1
let missBrightness = 0
let checkerQuad = NO_HIT

// Per-call output (avoids allocation in the hot loop).
let hitQuad = NO_HIT
let hitIsSphere = 0 // 0 = quad, 1 = sphere
let hitPx = 0,
	hitPy = 0,
	hitPz = 0
let hitU = 0,
	hitV = 0
let hitNx = 0,
	hitNy = 0,
	hitNz = 0 // outward normal at hit

// Output from intersectOneSphere() — used by glass shading's inner walk.
let osHit = false
let osPx = 0,
	osPy = 0,
	osPz = 0
let osNx = 0,
	osNy = 0,
	osNz = 0

// Output from refract().
let refTIR = false
let refX = 0,
	refY = 0,
	refZ = 0

// Output from shadeGlass().
let glassR = 0,
	glassG = 0,
	glassB = 0

let shR = 0,
	shG = 0,
	shB = 0
let lmR = 0,
	lmG = 0,
	lmB = 0
let rusX = 0,
	rusY = 0,
	rusZ = 0
let rndX = 0,
	rndY = 0,
	rndZ = 0
let seed0 = 0,
	seed1 = 0,
	seed2 = 0

/** Decodes an IEEE-754 half-float (rgba16float format) to a number. */
function decodeHalf(h: number): number {
	const sign = h & 0x8000 ? -1 : 1
	const exp = (h & 0x7c00) >> 10
	const frac = h & 0x03ff
	if (exp === 0) return sign * frac * 5.960464477539063e-8
	if (exp === 0x1f) return frac ? NaN : sign * Infinity
	return sign * (1024 + frac) * Math.pow(2, exp - 25)
}

// Mirrors common.wgsl: init_rand, rand, rand_unit_sphere.
function initRand(ix: number, iy: number, iz: number) {
	rndX = (Math.imul(ix, 1757325859) ^ seed0) >>> 0
	rndY = (Math.imul(iy, 2947058881) ^ seed1) >>> 0
	rndZ = (Math.imul(iz, 89742002) ^ seed2) >>> 0
}

function rand(): number {
	const nx = (Math.imul(rndX, 567242861) ^ (rndY >>> 4)) >>> 0
	const ny = (Math.imul(rndY, 658659763) ^ (rndZ >>> 4)) >>> 0
	const nz = (Math.imul(rndZ, 74953335) ^ (rndX >>> 4)) >>> 0
	rndX = nx
	rndY = ny
	rndZ = nz
	return ((rndX ^ rndY) >>> 0) / 4294967295
}

function randUnitSphere() {
	const u = rand()
	const v = rand()
	const theta = u * 2.0 * Math.PI
	const phi = Math.acos(2.0 * v - 1.0)
	const r = Math.pow(rand(), 1.0 / 3.0)
	rusX = r * Math.sin(theta) * Math.sin(phi)
	rusY = r * Math.sin(phi) * Math.cos(theta)
	rusZ = r * Math.cos(phi)
}

/** Nearest intersection of a ray with all quads + spheres. (Mirrors common.wgsl raytrace.) */
function raytrace(
	sx: number,
	sy: number,
	sz: number,
	dx: number,
	dy: number,
	dz: number
) {
	let closest = 1e20
	let cq = NO_HIT
	let cIsSphere = 0
	let cpx = 0,
		cpy = 0,
		cpz = 0,
		cu = 0,
		cv = 0
	let cnx = 0,
		cny = 0,
		cnz = 0

	for (let q = 0; q < quadCount; q++) {
		const b = q * QUAD_STRIDE
		const pnx = quadData[b],
			pny = quadData[b + 1],
			pnz = quadData[b + 2],
			pw = quadData[b + 3]

		const planeDist = pnx * sx + pny * sy + pnz * sz + pw
		const rayDist = planeDist / -(pnx * dx + pny * dy + pnz * dz)
		const posx = sx + dx * rayDist,
			posy = sy + dy * rayDist,
			posz = sz + dz * rayDist

		const u =
			(quadData[b + 4] * posx +
				quadData[b + 5] * posy +
				quadData[b + 6] * posz +
				quadData[b + 7]) *
				0.5 +
			0.5
		const v =
			(quadData[b + 8] * posx +
				quadData[b + 9] * posy +
				quadData[b + 10] * posz +
				quadData[b + 11]) *
				0.5 +
			0.5

		if (
			planeDist > 0 &&
			rayDist > 0 &&
			rayDist < closest &&
			u > 0 &&
			u < 1 &&
			v > 0 &&
			v < 1
		) {
			closest = rayDist
			cq = q
			cIsSphere = 0
			cpx = posx
			cpy = posy
			cpz = posz
			cu = u
			cv = v
			cnx = pnx
			cny = pny
			cnz = pnz
		}
	}

	for (let s = 0; s < sphereCount; s++) {
		const b = s * SPHERE_STRIDE
		const cx = sphereData[b],
			cy = sphereData[b + 1],
			cz = sphereData[b + 2]
		const rad = sphereData[b + 3]
		if (rad <= 0) continue // skip the empty-scene placeholder slot
		const ocx = sx - cx,
			ocy = sy - cy,
			ocz = sz - cz
		const bb = ocx * dx + ocy * dy + ocz * dz
		const cc = ocx * ocx + ocy * ocy + ocz * ocz - rad * rad
		const disc = bb * bb - cc
		if (disc <= 0) continue
		const sqrtDisc = Math.sqrt(disc)
		const t0 = -bb - sqrtDisc
		const t1 = -bb + sqrtDisc
		let t: number
		if (t0 > 1e-4) t = t0
		else if (t1 > 1e-4) t = t1
		else continue
		if (t >= closest) continue
		closest = t
		cq = s
		cIsSphere = 1
		cpx = sx + dx * t
		cpy = sy + dy * t
		cpz = sz + dz * t
		cu = 0
		cv = 0
		cnx = (cpx - cx) / rad
		cny = (cpy - cy) / rad
		cnz = (cpz - cz) / rad
	}

	hitQuad = cq
	hitIsSphere = cIsSphere
	hitPx = cpx
	hitPy = cpy
	hitPz = cpz
	hitU = cu
	hitV = cv
	hitNx = cnx
	hitNy = cny
	hitNz = cnz
}

/** Intersect ray with ONE specific sphere — used by glass shading's inner walk
 *  without clobbering the global raytrace() output. */
function intersectOneSphere(
	sphereIdx: number,
	sx: number,
	sy: number,
	sz: number,
	dx: number,
	dy: number,
	dz: number
) {
	const b = sphereIdx * SPHERE_STRIDE
	const cx = sphereData[b],
		cy = sphereData[b + 1],
		cz = sphereData[b + 2]
	const rad = sphereData[b + 3]
	const ocx = sx - cx,
		ocy = sy - cy,
		ocz = sz - cz
	const bb = ocx * dx + ocy * dy + ocz * dz
	const cc = ocx * ocx + ocy * ocy + ocz * ocz - rad * rad
	const disc = bb * bb - cc
	if (disc <= 0) {
		osHit = false
		return
	}
	const sqrtDisc = Math.sqrt(disc)
	const t0 = -bb - sqrtDisc
	const t1 = -bb + sqrtDisc
	let t: number
	if (t0 > 1e-4) t = t0
	else if (t1 > 1e-4) t = t1
	else {
		osHit = false
		return
	}
	osPx = sx + dx * t
	osPy = sy + dy * t
	osPz = sz + dz * t
	osNx = (osPx - cx) / rad
	osNy = (osPy - cy) / rad
	osNz = (osPz - cz) / rad
	osHit = true
}

/** Scalar refract — eta = n1/n2. Writes refX/Y/Z; sets refTIR=true on total
 *  internal reflection (in which case refX/Y/Z are zeroed). Mirrors WGSL's refract(). */
function refract(
	ix: number,
	iy: number,
	iz: number,
	nx: number,
	ny: number,
	nz: number,
	eta: number
) {
	const ndi = nx * ix + ny * iy + nz * iz
	const k = 1 - eta * eta * (1 - ndi * ndi)
	if (k < 0) {
		refTIR = true
		refX = 0
		refY = 0
		refZ = 0
		return
	}
	refTIR = false
	const s = eta * ndi + Math.sqrt(k)
	refX = eta * ix - nx * s
	refY = eta * iy - ny * s
	refZ = eta * iz - nz * s
}

/** Bilinear, clamp-to-edge lightmap sample (matches GPU sampler). */
function sampleLightmap(layer: number, u: number, v: number) {
	const S = lmSize
	const cu = u < 0 ? 0 : u > 1 ? 1 : u
	const cv = v < 0 ? 0 : v > 1 ? 1 : v
	const fx = cu * S - 0.5,
		fy = cv * S - 0.5
	const ix = Math.floor(fx),
		iy = Math.floor(fy)
	const tx = fx - ix,
		ty = fy - iy

	const x0 = ix < 0 ? 0 : ix > S - 1 ? S - 1 : ix
	const x1 = ix + 1 < 0 ? 0 : ix + 1 > S - 1 ? S - 1 : ix + 1
	const y0 = iy < 0 ? 0 : iy > S - 1 ? S - 1 : iy
	const y1 = iy + 1 < 0 ? 0 : iy + 1 > S - 1 ? S - 1 : iy + 1

	const layerOff = layer * S * S * 4
	const i00 = layerOff + (y0 * S + x0) * 4
	const i10 = layerOff + (y0 * S + x1) * 4
	const i01 = layerOff + (y1 * S + x0) * 4
	const i11 = layerOff + (y1 * S + x1) * 4

	for (let ch = 0; ch < 3; ch++) {
		const top = lightmap[i00 + ch] * (1 - tx) + lightmap[i10 + ch] * tx
		const bot = lightmap[i01 + ch] * (1 - tx) + lightmap[i11 + ch] * tx
		const value = top * (1 - ty) + bot * ty
		if (ch === 0) lmR = value
		else if (ch === 1) lmG = value
		else lmB = value
	}
}

/** Samples the hit primitive's leaf color. For spheres, returns the tint —
 *  glass shading on sphere hits is dispatched at the call site instead, so
 *  this acts as the recursion floor (matches raytracer.wgsl sample_hit). */
function sampleHit(quad: number, isSphere: number, u: number, v: number) {
	if (quad === NO_HIT) {
		// Ray escaped the scene — matches the GPU sample_hit miss color.
		shR = missBrightness
		shG = missBrightness
		shB = missBrightness
		return
	}
	if (isSphere === 1) {
		const b = quad * SPHERE_STRIDE
		shR = sphereData[b + 4]
		shG = sphereData[b + 5]
		shB = sphereData[b + 6]
		return
	}
	sampleLightmap(quad, u, v)
	const b = quad * QUAD_STRIDE
	const colR = quadData[b + 12],
		colG = quadData[b + 13],
		colB = quadData[b + 14],
		em = quadData[b + 15]

	let r = (lmR + em * colR) * lightIntensity
	let g = (lmG + em * colG) * lightIntensity
	let bch = (lmB + em * colB) * lightIntensity

	if (quad === checkerQuad) {
		const cell = Math.floor(u * 16) + Math.floor(v * 16)
		const odd = cell - 2 * Math.floor(cell * 0.5)
		const c = odd > 0.5 ? 0.06 : 1.6
		r += c
		g += c
		bch += c
	}

	shR = r
	shG = g
	shB = bch
}

/** Glass shading at a ray–sphere hit: Schlick Fresnel + Snell refraction +
 *  TIR fallback. Writes the final RGB into glassR/G/B. Mirrors raytracer.wgsl
 *  shade_glass. */
function shadeGlass(
	dx: number,
	dy: number,
	dz: number,
	sphereIdx: number,
	nx: number,
	ny: number,
	nz: number,
	hpx: number,
	hpy: number,
	hpz: number
) {
	const sb = sphereIdx * SPHERE_STRIDE
	const tintR = sphereData[sb + 4],
		tintG = sphereData[sb + 5],
		tintB = sphereData[sb + 6]
	const ior = sphereData[sb + 7]

	// Schlick Fresnel
	const ndi = nx * dx + ny * dy + nz * dz
	const cos_theta = Math.max(0, -ndi)
	const r0 = Math.pow((1 - ior) / (1 + ior), 2)
	const fresnel = r0 + (1 - r0) * Math.pow(1 - cos_theta, 5)

	// Front-face reflection
	const d2 = 2 * ndi
	const reflectDx = dx - d2 * nx,
		reflectDy = dy - d2 * ny,
		reflectDz = dz - d2 * nz
	raytrace(
		hpx + nx * 1e-4,
		hpy + ny * 1e-4,
		hpz + nz * 1e-4,
		reflectDx,
		reflectDy,
		reflectDz
	)
	sampleHit(hitQuad, hitIsSphere, hitU, hitV)
	const reflR = shR,
		reflG = shG,
		reflB = shB

	// Refraction (entry: air -> glass)
	refract(dx, dy, dz, nx, ny, nz, 1 / ior)
	let transR: number, transG: number, transB: number
	if (refTIR) {
		// TIR on entry can't happen physically going air→glass, but guard.
		transR = reflR
		transG = reflG
		transB = reflB
	} else {
		const enterDx = refX,
			enterDy = refY,
			enterDz = refZ
		const insideSx = hpx + enterDx * 1e-4,
			insideSy = hpy + enterDy * 1e-4,
			insideSz = hpz + enterDz * 1e-4
		intersectOneSphere(
			sphereIdx,
			insideSx,
			insideSy,
			insideSz,
			enterDx,
			enterDy,
			enterDz
		)
		if (!osHit) {
			// Numerical fallback: just trace the enter direction against the scene.
			raytrace(insideSx, insideSy, insideSz, enterDx, enterDy, enterDz)
			sampleHit(hitQuad, hitIsSphere, hitU, hitV)
			transR = shR
			transG = shG
			transB = shB
		} else {
			// Exit refraction (glass -> air). intersectOneSphere normal is outward,
			// but refract() expects the inward-facing normal for an outgoing ray.
			const exitNx = -osNx,
				exitNy = -osNy,
				exitNz = -osNz
			const exitPx = osPx,
				exitPy = osPy,
				exitPz = osPz
			refract(enterDx, enterDy, enterDz, exitNx, exitNy, exitNz, ior)
			let exitDx: number, exitDy: number, exitDz: number
			if (refTIR) {
				// TIR on back face — reflect inside the glass, exit along reflected dir.
				const dd =
					2 * (exitNx * enterDx + exitNy * enterDy + exitNz * enterDz)
				exitDx = enterDx - dd * exitNx
				exitDy = enterDy - dd * exitNy
				exitDz = enterDz - dd * exitNz
			} else {
				exitDx = refX
				exitDy = refY
				exitDz = refZ
			}
			raytrace(
				exitPx + exitDx * 1e-4,
				exitPy + exitDy * 1e-4,
				exitPz + exitDz * 1e-4,
				exitDx,
				exitDy,
				exitDz
			)
			sampleHit(hitQuad, hitIsSphere, hitU, hitV)
			transR = shR
			transG = shG
			transB = shB
		}
	}

	glassR = (transR * (1 - fresnel) + reflR * fresnel) * tintR
	glassG = (transG * (1 - fresnel) + reflG * fresnel) * tintG
	glassB = (transB * (1 - fresnel) + reflB * fresnel) * tintB
}

/** Reinhard tonemap + gamma (mirrors tonemapper.wgsl). */
function tonemap(c: number): number {
	const x = c * 0.5
	const mapped = x / (1 + x)
	return Math.pow(mapped < 0 ? 0 : mapped, 1 / 2.2)
}

/** Renders the frame in horizontal bands. Posts each band back as it finishes. */
function render(req: CpuRaytraceRequest): number {
	const { width, height, invMvp, reflectionRays, startY, endY } = req

	quadData = req.quadData
	quadCount = req.quadCount
	sphereData = req.sphereData
	sphereCount = req.sphereCount
	lmSize = req.lightmapSize
	lightIntensity = req.lightIntensity
	missBrightness = req.missBrightness
	checkerQuad = req.checkerQuad
	seed0 = req.seed[0]
	seed1 = req.seed[1]
	seed2 = req.seed[2]

	// Decode half-float lightmap -> linear floats.
	lightmap = new Float32Array(req.lightmap.length)
	for (let i = 0; i < req.lightmap.length; i++) {
		lightmap[i] = decodeHalf(req.lightmap[i])
	}

	const m = invMvp
	let computeMs = 0

	for (let y0 = startY; y0 < endY; y0 += BAND_ROWS) {
		const rows = Math.min(BAND_ROWS, endY - y0)
		const band = new Uint8ClampedArray(width * rows * 4)
		const bandStart = performance.now()

		for (let y = y0; y < y0 + rows; y++) {
			for (let x = 0; x < width; x++) {
				initRand(x, y, 0)

				// Pixel -> NDC (Y-flipped).
				const ndcX = (x / width - 0.5) * 2
				const ndcY = (y / height - 0.5) * -2

				// Near (NDC z=0) and far (NDC z=1) in world space via inv_mvp.
				let nx = m[0] * ndcX + m[4] * ndcY + m[12]
				let ny = m[1] * ndcX + m[5] * ndcY + m[13]
				let nz = m[2] * ndcX + m[6] * ndcY + m[14]
				const nw = m[3] * ndcX + m[7] * ndcY + m[15]
				nx /= nw
				ny /= nw
				nz /= nw

				let fx = m[0] * ndcX + m[4] * ndcY + m[8] + m[12]
				let fy = m[1] * ndcX + m[5] * ndcY + m[9] + m[13]
				let fz = m[2] * ndcX + m[6] * ndcY + m[10] + m[14]
				const fw = m[3] * ndcX + m[7] * ndcY + m[11] + m[15]
				fx /= fw
				fy /= fw
				fz /= fw

				let dx = fx - nx,
					dy = fy - ny,
					dz = fz - nz
				const dlen = Math.hypot(dx, dy, dz) || 1
				dx /= dlen
				dy /= dlen
				dz /= dlen

				// Primary ray.
				raytrace(nx, ny, nz, dx, dy, dz)
				const primQuad = hitQuad
				const primIsSphere = hitIsSphere
				const primU = hitU,
					primV = hitV
				const hpx = hitPx,
					hpy = hitPy,
					hpz = hitPz
				const hnx = hitNx,
					hny = hitNy,
					hnz = hitNz

				let cr: number, cg: number, cb: number
				if (primQuad === NO_HIT) {
					// Ray escaped the scene — background color.
					cr = missBrightness
					cg = missBrightness
					cb = missBrightness
				} else if (primIsSphere === 1) {
					// Glass sphere — Fresnel-mixed reflect/refract.
					shadeGlass(
						dx,
						dy,
						dz,
						primQuad,
						hnx,
						hny,
						hnz,
						hpx,
						hpy,
						hpz
					)
					cr = glassR
					cg = glassG
					cb = glassB
				} else {
					// Quad: lightmap sample + jittered metallic reflections.
					sampleHit(primQuad, 0, primU, primV)
					const hcR = shR,
						hcG = shG,
						hcB = shB

					const b = primQuad * QUAD_STRIDE
					const metallic = quadData[b + 16]
					const roughness = quadData[b + 17]
					const colR = quadData[b + 12],
						colG = quadData[b + 13],
						colB = quadData[b + 14]

					const d2 = 2 * (hnx * dx + hny * dy + hnz * dz)
					const bx = dx - d2 * hnx,
						by = dy - d2 * hny,
						bz = dz - d2 * hnz

					let reflR = 0,
						reflG = 0,
						reflB = 0
					for (let i = 0; i < reflectionRays; i++) {
						randUnitSphere()
						let rdx = bx + rusX * roughness,
							rdy = by + rusY * roughness,
							rdz = bz + rusZ * roughness
						const rlen = Math.hypot(rdx, rdy, rdz) || 1
						rdx /= rlen
						rdy /= rlen
						rdz /= rlen
						raytrace(
							hpx + bx * 1e-5,
							hpy + by * 1e-5,
							hpz + bz * 1e-5,
							rdx,
							rdy,
							rdz
						)
						// Reflection rays that land on the glass sphere need full
						// glass shading — otherwise the sphere shows up as a flat
						// white blob in mirror reflections.
						if (hitQuad === NO_HIT) {
							// missed → contribute 0
						} else if (hitIsSphere === 1) {
							const ghx = hitPx,
								ghy = hitPy,
								ghz = hitPz
							const gnx = hitNx,
								gny = hitNy,
								gnz = hitNz
							const gIdx = hitQuad
							shadeGlass(
								rdx,
								rdy,
								rdz,
								gIdx,
								gnx,
								gny,
								gnz,
								ghx,
								ghy,
								ghz
							)
							reflR += glassR
							reflG += glassG
							reflB += glassB
						} else {
							sampleHit(hitQuad, 0, hitU, hitV)
							reflR += shR
							reflG += shG
							reflB += shB
						}
					}
					const inv = 1 / reflectionRays
					// Tint reflections by the surface color so metallic surfaces
					// retain their hue in their own reflection (matches GPU).
					const tR = reflR * inv * colR
					const tG = reflG * inv * colG
					const tB = reflB * inv * colB
					cr = hcR * (1 - metallic) + tR * metallic
					cg = hcG * (1 - metallic) + tG * metallic
					cb = hcB * (1 - metallic) + tB * metallic
				}

				const o = ((y - y0) * width + x) * 4
				band[o] = tonemap(cr) * 255
				band[o + 1] = tonemap(cg) * 255
				band[o + 2] = tonemap(cb) * 255
				band[o + 3] = 255
			}
		}

		computeMs += performance.now() - bandStart

		workerSelf.postMessage(
			{ type: 'band', y: y0, height: rows, pixels: band },
			[band.buffer]
		)
	}

	return computeMs
}

workerSelf.onmessage = (event: MessageEvent<CpuRaytraceRequest>) => {
	const ms = render(event.data)
	workerSelf.postMessage({ type: 'done', ms })
}
