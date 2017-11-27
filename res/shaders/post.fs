#version 330 core

in vec2 texel;
  
uniform sampler2D screentexture;
 
layout(location = 0) out vec4 fragcolor;


void main(){
	vec4 screencolor = texture(screentexture, texel);
	
	fragcolor = screencolor;

}