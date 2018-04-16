//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#include "ShadowStage.h"

ShadowStage::ShadowStage() {
	shadowmapper = Shader::load("../res/shaders/shadowmap.vs", "../res/shaders/shadowmap.fs");
}

void ShadowStage::render() {
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glEnable(GL_DEPTH_TEST);
	directionalLight->drawShadowMap(*pipeline->objects, shadowmapper);
}

ShadowStage::~ShadowStage() {
	delete shadowmapper;
}

void ShadowStage::bindDirectionalLight(DirectionalLight *directionalLight) {
	this->directionalLight = directionalLight;

}

void ShadowStage::reset() {

}
