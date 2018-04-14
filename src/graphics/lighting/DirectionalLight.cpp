//
// Created by Pierre-Yves Boers on 10/04/2018.
//

#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(vec3 pos, vec3 direction, vec3 color, float intensity) : pos(pos), direction(direction.normalized()), color(color), intensity(intensity), shadowbuffer(2048, 2048), shadowmap(0){
	shadowmap = shadowbuffer.depthTextureAttachment();
	vp.initOrtho(-20, 20, -20, 20, 1, 20);
	mat4 view;
//	mat4 rot;
//	view.initRotation(direction.getX(), direction.getY(), direction.getZ());
//	rot.initTranslation(-pos);
//	view *= rot;

	view.initLookAt(direction, vec3::getCrossProduct(direction, vec3(1, 0, 0)), -pos);
	vp *= view;
}

DirectionalLight::~DirectionalLight() {
	delete shadowmap;
}

void DirectionalLight::updateShader(Shader *s) {
	s->bind();
	s->uniformVec3("dLcolor", &color);
	s->uniformVec3("dLdirection", &direction);
	s->uniformf("dLintensity", intensity);

}

const Texture &DirectionalLight::getShadowMap() {
	return *shadowmap;
}

void DirectionalLight::drawShadowMap(std::vector<Obj *> objects, Shader *s) {
	s->bind();
	s->uniformMat4("vp", &vp);
	shadowbuffer.bind();
	glClear(GL_DEPTH_BUFFER_BIT);
	for(Obj* obj: objects){
		obj->render(*s);
	}

}

mat4 &DirectionalLight::getvp() {
	return vp;
}
