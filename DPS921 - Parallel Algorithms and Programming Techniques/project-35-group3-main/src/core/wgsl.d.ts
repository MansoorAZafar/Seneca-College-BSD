// Lets TypeScript understand `import code from './shader.wgsl'`.
// The actual string is provided at build time by the wgsl plugin in
// vite.config.ts.
declare module '*.wgsl' {
	const shader: string
	export default shader
}
