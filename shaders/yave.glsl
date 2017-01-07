
const float pi = 3.1415926535897932384626433832795;
const float epsilon = 0.001;

float saturate(float x) {
	return min(1.0, max(0.0, x));
}

float sqr(float x) {
	return x * x;
}

float noise(vec2 co) {
	return fract(sin(dot(co.xy, vec2(12.9898,78.233))) * 43758.5453);
}

vec3 unproject(vec2 uv, float depth, mat4 inv_matrix) {
	vec3 ndc = vec3(uv * 2.0 - vec2(1.0), depth);
	vec4 p = inv_matrix * vec4(ndc, 1.0);
	return p.xyz / p.w;
}
