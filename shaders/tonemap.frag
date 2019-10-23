#version 450

#include "yave.glsl"

layout(set = 0, binding = 0) uniform sampler2D in_color;
layout(set = 0, binding = 1) uniform ToneMapping {
	ToneMappingParams params;
} params;

layout(location = 0) in vec2 in_uv;

layout(location = 0) out vec4 out_color;

const float gamma = 2.0;
const float inv_gamma = 1.0 / gamma;

// https://64.github.io/tonemapping/
// https://mynameismjp.wordpress.com/2010/04/30/a-closer-look-at-tone-mapping/
// https://www.academia.edu/24772316/Programming_Vertex_Geometry_and_Pixel_Shaders_Screenshots_of_Alan_Wake_courtesy_of_Remedy_Entertainment
// https://imdoingitwrong.wordpress.com/2010/08/19/why-reinhard-desaturates-my-blacks-3/
void main() {
	ivec2 coord = ivec2(gl_FragCoord.xy);
	vec3 hdr = texelFetch(in_color, coord, 0).rgb;

	vec3 ldr = ACES_fast(hdr, params.params.white_point);


	out_color = vec4(pow(ldr, vec3(inv_gamma)), 1.0);
}


