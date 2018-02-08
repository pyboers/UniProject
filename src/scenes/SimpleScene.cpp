//
// Created by Pierre-Yves Boers on 05/02/2018.
//
#include "SimpleScene.h"
#include "../graphics/Mesh.h"

Mesh cube;

void SimpleScene::start() {
	camera = new Camera(0, 0, 0, 1280, 720, 72, .1, 100);
	basicShader = Shader::load("../res/shaders/reasonable.vs", "../res/shaders/reasonable.fs");
	cube.loadModel("../res/models/cube.obj");
}

void SimpleScene::stop() {
	delete camera;
	delete basicShader;
}

void SimpleScene::input(float dt) {

}

void SimpleScene::update(float dt) {

}
void SimpleScene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	basicShader->bind();
	mat4 viewprojection = camera->getViewProjection();
	basicShader->uniformMat4("vp", &viewprojection);
	basicShader->uniformMat4("model", mat4().initTranslation(0, 0, -2));
	cube.draw();

}




void SimpleScene::pause() {

}

void SimpleScene::resume() {

}

