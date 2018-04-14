//
// Created by Pierre-Yves Boers on 10/04/2018.
//

#ifndef UNIPROJECT_DIRECTIONALLIGHT_H
#define UNIPROJECT_DIRECTIONALLIGHT_H


#include "../../maths/vec3.h"
#include "../Shader.h"
#include "../Texture.h"
#include "../FBO.h"
#include "../../engine/Obj.h"

class DirectionalLight {
	vec3 direction;
	vec3 color;
	float intensity;
	vec3 pos;
	mat4 vp;
	FBO shadowbuffer;
	Texture *shadowmap;
public:
	DirectionalLight(vec3 pos, vec3 direction, vec3 color, float intensity);

	void drawShadowMap(std::vector<Obj*> objects, Shader *s);

	void updateShader(Shader *s);

	const Texture& getShadowMap();

	mat4& getvp();

	~DirectionalLight();
};


#endif //UNIPROJECT_DIRECTIONALLIGHT_H
