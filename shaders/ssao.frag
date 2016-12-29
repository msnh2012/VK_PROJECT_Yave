#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 out_color;

layout(location = 0) in vec2 v_uv;
layout(set = 1, binding = 0) uniform sampler2D in_color;
layout(set = 1, binding = 1) uniform sampler2D in_depth;

const float epsilon = 0.001;

vec3 sample_dir[] = {
	vec3(0.2196607,0.9032637,0.2254677),
	vec3(0.05916681,0.2201506,-0.1430302),
	vec3(-0.4152246,0.1320857,0.7036734),
	vec3(-0.3790807,0.1454145,0.100605),
	vec3(0.3149606,-0.1294581,0.7044517),
	vec3(-0.1108412,0.2162839,0.1336278),
	vec3(0.658012,-0.4395972,-0.2919373),
	vec3(0.5377914,0.3112189,0.426864),
	vec3(-0.2752537,0.07625949,-0.1273409),
	vec3(-0.1915639,-0.4973421,-0.3129629),
	vec3(-0.2634767,0.5277923,-0.1107446),
	vec3(0.8242752,0.02434147,0.06049098),
	vec3(0.06262707,-0.2128643,-0.03671562),
	vec3(-0.1795662,-0.3543862,0.07924347),
	vec3(0.06039629,0.24629,0.4501176),
	vec3(-0.7786345,-0.3814852,-0.2391262),
	vec3(0.2792919,0.2487278,-0.05185341),
	vec3(0.1841383,0.1696993,-0.8936281),
	vec3(-0.3479781,0.4725766,-0.719685),
	vec3(-0.1365018,-0.2513416,0.470937),
	vec3(0.1280388,-0.563242,0.3419276),
	vec3(-0.4800232,-0.1899473,0.2398808),
	vec3(0.6389147,0.1191014,-0.5271206),
	vec3(0.1932822,-0.3692099,-0.6060588),
	vec3(-0.3465451,-0.1654651,-0.6746758),
	vec3(0.2448421,-0.1610962,0.13289366),
	vec3(0.2448421,0.9032637,0.24254677),
	vec3(0.2196607,0.2201506,-0.18430302),
	vec3(0.05916681,0.1320857,0.70036734),
	vec3(-0.4152246,0.1454145,0.1800605),
	vec3(-0.3790807,-0.1294581,0.78044517),
	vec3(0.3149606,0.2162839,0.17336278),
	vec3(-0.1108412,-0.4395972,-0.269619373),
	vec3(0.658012,0.3112189,0.4267864),
	vec3(0.5377914,0.07625949,-0.12773409),
	vec3(-0.2752537,-0.4973421,-0.31629629),
	vec3(-0.1915639,0.5277923,-0.17107446),
	vec3(-0.2634767,0.02434147,0.086049098),
	vec3(0.8242752,-0.2128643,-0.083671562),
	vec3(0.06262707,-0.3543862,0.007924347),
	vec3(-0.1795662,0.24629,0.44501176),
	vec3(0.06039629,-0.3814852,-0.248391262),
	vec3(-0.7786345,0.2487278,-0.065185341),
	vec3(0.2792919,0.1696993,-0.84936281),
	vec3(0.1841383,0.4725766,-0.7419685),
	vec3(-0.3479781,-0.2513416,0.670937),
	vec3(-0.1365018,-0.563242,0.36419276),
	vec3(0.1280388,-0.1899473,0.23948808),
	vec3(-0.4800232,0.1191014,-0.5271206),
	vec3(0.6389147,-0.3692099,-0.5060588),
	vec3(0.1932822,-0.1654651,-0.62746758),
	vec3(-0.3465451,-0.1610962,0.4289366),
	vec3(0.2448421,-0.1610962,0.2254677),
	vec3(0.2196607,0.9032637,-0.1430302),
	vec3(0.05916681,0.2201506,0.7036734),
	vec3(-0.4152246,0.1320857,0.100605),
	vec3(-0.3790807,0.3454145,0.7044517),
	vec3(0.3149606,-0.4294581,0.1336278),
	vec3(-0.1108412,0.3162839,-0.2919373),
	vec3(0.658012,-0.2395972,0.426864),
	vec3(0.5377914,0.33112189,-0.1273409),
	vec3(-0.2752537,0.47625949,-0.3129629),
	vec3(-0.1915639,-0.3973421,-0.1107446),
	vec3(-0.2634767,0.2277923,0.06049098),
	vec3(0.8242752,-0.3434147,-0.03671562),
	vec3(0.06262707,-0.4128643,0.07924347),
	vec3(-0.1795662,-0.3543862,0.4501176),
	vec3(0.06039629,0.24629,-0.2391262),
	vec3(-0.7786345,-0.3814852,-0.05185341),
	vec3(0.2792919,0.4487278,-0.8936281),
	vec3(0.1841383,0.3696993,-0.719685),
	vec3(-0.3479781,0.2725766,0.470937),
	vec3(-0.1365018,-0.5513416,0.3419276),
	vec3(0.1280388,-0.163242,0.2398808),
	vec3(-0.4800232,-0.3899473,-0.5271206),
	vec3(0.6389147,0.3191014,-0.6060588),
	vec3(0.1932822,-0.1692099,-0.6746758),
	vec3(-0.3465451,-0.2654651,0.1289366)
	};

float saturate(float x) {
	return min(1.0, max(0.0, x));
}

float sqr(float x) {
	return x * x;
}

float AO(vec2 uv, float range, uint samples) {
	float depth = texture(in_depth, uv).r;
	float dx = fwidth(depth);
	if(depth > 1.0 - epsilon) {
		return 1.0;
	}

	float ao = 0.0;
	float max_occ_dist = 1.0; //0.02;
	for(int i = 0; i < samples; ++i) {
		range *= 0.975;
		vec3 dir = sample_dir[i & 0x3F];
		float sample_d = depth - dir.z * range;
		vec2 offset = range * dir.xy / depth;
		float d = textureLod(in_depth, uv + offset, 0).r;
		float delta = saturate(sample_d - d);
		delta *= 1.0 - smoothstep(0, max_occ_dist, delta);
		if(delta > epsilon && delta < max_occ_dist) {
			ao += sqr(1.0 - delta);
		}
	}
	return 1.0 - ao / float(samples);
}

void main() {
	float ao = AO(v_uv, 0.01, 64);
	
	//out_color = texture(in_color, v_uv) * ao;
	out_color = vec4(ao);
}
