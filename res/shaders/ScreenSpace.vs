#version 330 core

out vec2 texel;

void main() {
	texel = vec2((gl_VertexID & 2) >> 1, 1 - (gl_VertexID & 1));
	vec2 pos = texel * 2.0 - 1.0;
	gl_Position = vec4(pos, 0, 1);
}