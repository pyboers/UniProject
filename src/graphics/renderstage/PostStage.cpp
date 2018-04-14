//
// Created by Pierre-Yves Boers on 12/04/2018.
//

#include "PostStage.h"
#include "../../engine/Engine.h"

PostStage::PostStage() {
	postShader = Shader::load("../res/shaders/post.vs", "../res/shaders/post.fs");
}

void PostStage::render() {
	FBO::bindWindow(Engine::getEngine().getWindowWidth(), Engine::getEngine().getWindowHeight());
	glClear(GL_COLOR_BUFFER_BIT);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	postShader->bind();
	pre_texture->bind(0);
	postShader->uniformi("screentexture", 0);
	Mesh::indexCall(4);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

void PostStage::setPreTexture(const Texture *texture) {
	pre_texture = texture;

}

PostStage::~PostStage() {
	delete postShader;
}
