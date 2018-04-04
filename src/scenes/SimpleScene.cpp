//
// Created by Pierre-Yves Boers on 05/02/2018.
//
#include <SDL_quit.h>
#include "SimpleScene.h"
#include "../graphics/Mesh.h"
#include "../engine/BodyObj.h"
#include "../physics/shapes/AABB.h"
#include "Environment.h"

Mesh cube;
Environment *environ;
void SimpleScene::start() {
	camera = new Camera(0, 0, 0, 1280, 720, 72, .1, 100);
	basicShader = Shader::load("../res/shaders/reasonable.vs", "../res/shaders/reasonable.fs");
	cube.loadModel("../res/models/cube.obj");
	mat3 id = mat3();
	//id.initIdentity();
	pw = new PhysicsWorld(4,2);

	environ = new Environment(*pw);
	{
		Body *b = new Body(*pw, id);
		b->velocity.setX(0);
		b->position.setY(-2);
		b->inv_Mass = 0;
		b->friction = 0.5f;
		objects.push_back(new BodyObj(Transform(), cube, *b, vec3(100, 0.2, 100)));
		pw->bodies.push_back(b);
	}
	for(int i = 0; i<200; i++) {
		Body *b = new Body(*pw, id);
		b->position.setX(rand()%10);
		b->position.setY(i);
		b->position.setZ(-5);
		b->inv_Mass = 1;
		b->friction = 0.5f;
		objects.push_back(new BodyObj(Transform(), cube, *b, vec3(0.5, 0.5, 0.5)));
		pw->bodies.push_back(b);
	}


}


void SimpleScene::stop() {
	delete camera;
	delete basicShader;
	delete pw;
	delete environ;
}

void SimpleScene::input(float dt) {

}

void SimpleScene::update(float dt) {
	camera->update(dt);
	pw->update(dt);
	for(Obj* obj : objects){
		obj->update(dt);
	}
}
void SimpleScene::render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	basicShader->bind();
	mat4 viewprojection = camera->getViewProjection();
	basicShader->uniformMat4("vp", &viewprojection);
	for(Obj* obj: objects){
		obj->render(*basicShader);
	}
}




void SimpleScene::pause() {

}

void SimpleScene::resume() {

}

