/** WebGPU capability checks and user-friendly error dialogs. */

// Catches any unhandled errors that slip through explicit checks.
globalThis.addEventListener('unhandledrejection', (ev) => {
	fail(`unhandled promise rejection, please report a bug!
  https://github.com/webgpu/webgpu-samples/issues/new\n${ev.reason}`)
})
globalThis.addEventListener('error', (ev) => {
	fail(`uncaught exception, please report a bug!
  https://github.com/webgpu/webgpu-samples/issues/new\n${ev.error}`)
})

/** Checks that a GPU adapter was obtained. Shows an error and throws if not. */
export function quitIfAdapterNotAvailable(
	adapter: GPUAdapter | null
): asserts adapter {
	if (!('gpu' in navigator)) {
		fail(
			'navigator.gpu is not defined - WebGPU not available in this browser'
		)
	}

	if (!adapter) {
		fail(
			"requestAdapter returned null - this sample can't run on this system"
		)
	}
}

/** Checks that the adapter meets a minimum limit. Adds it to `limits` for device creation. */
export function quitIfLimitLessThan(
	adapter: GPUAdapter,
	limit: string,
	requiredValue: number,
	limits: Record<string, GPUSize32>
) {
	if (limit in adapter.limits) {
		const limitKey = limit as keyof GPUSupportedLimits
		const limitValue = adapter.limits[limitKey] as number
		if (limitValue < requiredValue) {
			fail(
				`This sample can't run on this system. ${limit} is ${limitValue}, and this sample requires at least ${requiredValue}.`
			)
		}
		limits[limit] = requiredValue
	}
}

/** Checks that all required GPU features are supported by the adapter. */
export function quitIfFeaturesNotAvailable(
	adapter: GPUAdapter | null,
	requiredFeatures: GPUFeatureName[]
): asserts adapter {
	quitIfAdapterNotAvailable(adapter)

	for (const feature of requiredFeatures) {
		if (!adapter.features.has(feature)) {
			fail(
				`This sample requires the '${feature}' feature, which is not supported by this system.`
			)
			return
		}
	}
}

/** Tests whether the device supports binding buffers directly in a bind group. */
function supportsDirectBufferBinding(device: GPUDevice): boolean {
	const buffer = device.createBuffer({
		size: 16,
		usage: GPUBufferUsage.UNIFORM,
	})
	const layout = device.createBindGroupLayout({
		entries: [
			{ binding: 0, visibility: GPUShaderStage.FRAGMENT, buffer: {} },
		],
	})

	try {
		device.createBindGroup({
			layout,
			entries: [{ binding: 0, resource: buffer }],
		})
		return true
	} catch {
		return false
	} finally {
		buffer.destroy()
	}
}

/** Tests whether the device supports binding textures directly in a bind group. */
function supportsDirectTextureBinding(device: GPUDevice): boolean {
	const texture = device.createTexture({
		size: [1],
		usage: GPUTextureUsage.TEXTURE_BINDING,
		format: 'rgba8unorm',
	})
	const layout = device.createBindGroupLayout({
		entries: [
			{ binding: 0, visibility: GPUShaderStage.FRAGMENT, texture: {} },
		],
	})

	try {
		device.createBindGroup({
			layout,
			entries: [{ binding: 0, resource: texture }],
		})
		return true
	} catch {
		return false
	} finally {
		texture.destroy()
	}
}

/** Tests whether the device supports rendering directly to textures (multisampled attachments). */
function supportsDirectTextureAttachments(device: GPUDevice): boolean {
	const texture = device.createTexture({
		size: [1],
		usage: GPUTextureUsage.RENDER_ATTACHMENT,
		format: 'rgba8unorm',
		sampleCount: 4,
	})
	const resolveTarget = device.createTexture({
		size: [1],
		usage: GPUTextureUsage.RENDER_ATTACHMENT,
		format: 'rgba8unorm',
	})
	const depthTexture = device.createTexture({
		size: [1],
		usage: GPUTextureUsage.RENDER_ATTACHMENT,
		format: 'depth16unorm',
		sampleCount: 4,
	})
	const encoder = device.createCommandEncoder()
	try {
		const pass = encoder.beginRenderPass({
			colorAttachments: [
				{
					view: texture,
					resolveTarget,
					loadOp: 'load',
					storeOp: 'store',
				},
			],
			depthStencilAttachment: {
				view: depthTexture,
				depthLoadOp: 'load',
				depthStoreOp: 'store',
			},
		})
		pass.end()
		return true
	} catch (e) {
		console.error(e)
		return false
	} finally {
		encoder.finish()
		texture.destroy()
		resolveTarget.destroy()
	}
}

/**
 * Comprehensive WebGPU availability check.
 * Verifies a device was created, sets up loss/error listeners, and tests
 * core capabilities (direct buffer/texture binding, texture attachments).
 */
export function quitIfWebGPUNotAvailableOrMissingFeatures(
	adapter: GPUAdapter | null,
	device: GPUDevice | null
): asserts device {
	if (!device) {
		quitIfAdapterNotAvailable(adapter)
		fail('Unable to get a device for an unknown reason')
		return
	}

	device.lost.then((reason) => {
		fail(`Device lost ("${reason.reason}"):\n${reason.message}`)
	})

	device.addEventListener('uncapturederror', (ev) => {
		fail(`Uncaptured error:\n${ev.error.message}`)
	})

	if (
		!supportsDirectBufferBinding(device) ||
		!supportsDirectTextureBinding(device) ||
		!supportsDirectTextureAttachments(device)
	) {
		fail(
			'Core features of WebGPU are unavailable. Please update your browser to a newer version.'
		)
	}
}

/** Shows a modal error dialog in the browser (or logs in workers) and throws. */
const fail = (() => {
	type ErrorOutput = { show(msg: string): void }

	function createErrorOutput() {
		if (typeof document === 'undefined') {
			return {
				show(msg: string) {
					console.error(msg)
				},
			}
		}

		const dialogBox = document.createElement('dialog')
		dialogBox.close()
		document.body.append(dialogBox)

		const dialogText = document.createElement('pre')
		dialogText.style.whiteSpace = 'pre-wrap'
		dialogBox.append(dialogText)

		const closeBtn = document.createElement('button')
		closeBtn.textContent = 'OK'
		closeBtn.onclick = () => dialogBox.close()
		dialogBox.append(closeBtn)

		return {
			show(msg: string) {
				// Don't overwrite while the dialog is still open.
				if (!dialogBox.open) {
					dialogText.textContent = msg
					dialogBox.showModal()
				}
			},
		}
	}

	let output: ErrorOutput | undefined

	return (message: string) => {
		if (!output) output = createErrorOutput()

		output.show(message)
		throw new Error(message)
	}
})()
