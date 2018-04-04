//
// Created by Pierre-Yves Boers on 05/02/2018.
//
#include <SDL_quit.h>
#include "SimpleScene.h"
#include "../graphics/Mesh.h"
#include "../engine/BodyObj.h"
#include "../physics/shapes/AABB.h"

Mesh cube;

void SimpleScene::start() {
	camera = new Camera(0, 0, 0, 1280, 720, 72, .1, 100);
	basicShader = Shader::load("../res/shaders/reasonable.vs", "../res/shaders/reasonable.fs");
	cube.loadModel("../res/models/cube.obj");
	mat3 id = mat3();
	//id.initIdentity();
	pw = new PhysicsWorld(32,1);

	{
		Body *b = new Body(*pw, id);
		b->elements.push_back(new Element(*b, new AABB(vec3(0, 0, 0), vec3(0.5, 0.5, 0.5))));
		b->velocity.setX(0);
		b->position.setY(0.6f);
		b->inv_Mass = 0;
		objects.push_back(new BodyObj(Transform(), cube, *b));
		pw->bodies.push_back(b);
	}
	{
		Body *b = new Body(*pw, id);
		b->position.setX(-5);
		b->elements.push_back(new Element(*b, new AABB(vec3(0,0,0), vec3(0.5,0.5,0.5))));
		b->velocity.setX(1);
		b->inv_Mass = 1;
		objects.push_back(new BodyObj(Transform(), cube, *b));
		pw->bodies.push_back(b);
	}


}


void SimpleScene::stop() {
	delete camera;
	delete basicShader;
	delete pw;
}

void SimpleScene::input(float dt) {

}

void SimpleScene::update(float dt) {
	camera->update(dt);
	pw->bodies[1]->velocity.setX(10);
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

