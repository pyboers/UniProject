#version 330 core

layout(location = 0) in vec3 vertPos;

uniform mat4 model;
uniform mat4 vp;

void main(){
    gl_Position =  vp * model * vec4(vertPos, 1);
}