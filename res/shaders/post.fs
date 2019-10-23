#version 330 core

in vec2 texel;
  
uniform sampler2D screentexture;
 
layout(location = 0) out vec4 fragcolor;

#define gamma 1/(2.2)

vec3 vec_gamma(vec3 vec){
	return pow(vec, vec3(gamma));
}


void main(){
	vec4 screencolor = texture(screentexture, texel);

	fragcolor = vec4(vec_gamma(screencolor.xyz), screencolor.a);

}