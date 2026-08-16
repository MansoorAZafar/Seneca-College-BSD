import { readFile } from 'node:fs/promises'
import { fileURLToPath } from 'node:url'
import { defineConfig, Plugin } from 'vite'

// The Cornell shaders are authored as standalone `.wgsl` files and imported in
// TypeScript as plain strings, e.g.  `import code from './shader.wgsl'`.
// Vite does not know about `.wgsl` out of the box, so this small plugin reads
// the file from disk and hands it back as a default-exported string.
function wgsl(): Plugin {
	return {
		name: 'vite-plugin-wgsl',
		// Run before Vite's built-in asset handling so we own `.wgsl` resolution.
		enforce: 'pre',
		async load(id) {
			const [path] = id.split('?')
			if (path.endsWith('.wgsl')) {
				const source = await readFile(path, 'utf-8')
				return `export default ${JSON.stringify(source)};`
			}
		},
	}
}

export default defineConfig({
	plugins: [wgsl()],
	resolve: {
		alias: {
			'@': fileURLToPath(new URL('./src', import.meta.url)),
		},
	},
	// `main.ts` uses top-level `await` (to request the GPU adapter/device), so
	// target a JS version that supports it.
	build: {
		target: 'esnext',
	},
	esbuild: {
		target: 'esnext',
	},
})
