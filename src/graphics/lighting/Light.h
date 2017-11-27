#pragma once
#ifndef __LIGHT_H
#define __LIGHT_H
#define _CRT_SECURE_NO_WARNINGS
#include "../../maths/vec3.h"
#include "../Shader.h"
#define MAX_LIGHTS 0
class Light{
private:
	vec3 diffuseCoefficient;
	vec3 specularCoefficient;
	vec3 attenuation;
	vec3 pos;
	int Id;
public:
	float intensity;
	Light(int Id, float intensity, vec3 pos, vec3 diffuseCoefficient, vec3 specularCoefficient, vec3 attenuation);
	void updateShader(Shader *s);

	static void updateAmbient(Shader *s, vec3 *ambient);

};
#endif