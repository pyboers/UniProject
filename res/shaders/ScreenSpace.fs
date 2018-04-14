#version 330 core
uniform sampler2D texture0;
in vec2 texel;

layout(location = 0) out vec4 fragcolor;

void main(){
    fragcolor = vec4(vec3(texture(texture0, texel).x), 1);
}