//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#include "SceneStage.h"
#include "../../engine/Engine.h"

SceneStage::SceneStage() {
	basicShader = Shader::load("../res/shaders/reasonable.vs", "../res/shaders/reasonable.fs");
	pre = new FBO(Engine::getEngine().getWindowWidth(), Engine::getEngine().getWindowHeight());
	pre_texture = pre->colorTextureAttachment(0);
	pre->depthBufferAttachment();
}

void SceneStage::render() {
	pre->bind();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	basicShader->bind();
	for(auto *light : pipeline->lights){
		light->updateShader(basicShader);
	}
	pipeline->dl->updateShader(basicShader);
	pipeline->dl->getShadowMap().bind(1);
	basicShader->uniformi("dLShadowMap", 1);
	basicShader->uniformMat4("depthvp", &pipeline->dl->getvp());

	mat4 viewprojection = camera->getViewProjection();
	basicShader->uniformMat4("vp", &viewprojection);
	vec3 campos = camera->transform.getPos().getCopy();
	basicShader->uniformVec3("viewpos", &campos);

	for(auto* obj: *pipeline->objects){
		obj->render(*basicShader);
	}
}

SceneStage::~SceneStage() {
	delete pre;
	delete basicShader;

}

void SceneStage::setCamera(Camera *camera) {
	this->camera = camera;
}
