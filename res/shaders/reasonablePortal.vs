#version 330 core

layout(location = 0) in vec3 vertex;
layout(location = 1) in vec2 texCoord;
layout(location = 2) in vec3 normal;

uniform mat4 vp;
uniform mat4 portalV;
uniform mat4 model;
uniform mat4 depthvp;
uniform vec4 clipPlane;

out vec2 tcoord;
out vec3 norm;
out vec3 vpos;
out vec3 scoord;

void main(void) {
	vpos = (portalV * model * vec4(vertex, 1)).xyz;
	gl_Position =  vp * vec4(vpos, 1);
	tcoord = texCoord;
	norm = normal;
	scoord = (depthvp * vec4(vpos, 1) * 0.5 + 0.5).xyz;
	gl_ClipDistance[0] = dot(vec4(vpos, -1), clipPlane);
}