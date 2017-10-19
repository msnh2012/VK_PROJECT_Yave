#version 450

#include "yave.glsl"

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec4 out_normal;

layout(set = 1, binding = 0) uniform sampler2D in_texture;

layout(location = 0) in vec3 v_normal;
layout(location = 1) in vec2 v_uv;


void main() {
	vec4 tex_color = texture(in_texture, v_uv);

	out_color = pack_color(tex_color.rgb, 0.0);
	out_normal = pack_normal(v_normal, 0.1);
}
