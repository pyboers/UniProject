#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 vp;
uniform mat4 model;

out vec2 tcoord;
out vec3 norm;
out vec3 vpos;


void main(void) {
	vpos = (model * vec4(vertex, 1)).xyz;
	gl_Position = vp * vec4(vpos, 1);
	tcoord = texCoord;
	norm = normal;
}