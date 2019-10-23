#version 330 core

in vec2 tcoord; 
in vec3 norm;
in vec3 vpos;



layout(location = 0) out vec4 fragcolor;

void main(void) {
	fragcolor = vec4(1,1,1,0);
}