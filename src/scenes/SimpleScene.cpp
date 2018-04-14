//
// Created by Pierre-Yves Boers on 05/02/2018.
//
#include <SDL_quit.h>
#include "SimpleScene.h"
#include "../graphics/Mesh.h"
#include "../engine/BodyObj.h"
#include "../physics/shapes/AABB.h"
#include "Environment.h"
#include "../engine/Engine.h"
#include "../engine/picopng.h"

Mesh cube;
Environment *environ;
Body *body;
Texture *wood;
Texture *wood2;
Texture *grass;
void SimpleScene::start() {
	camera = new Camera(0, 0, 0, 1280, 720, 72, .1, 100);
	rp.setCamera(camera);

	cube.loadModel("../res/models/box2.obj");
	mat3 id = mat3();
	rp.addLight(new Light(0, 1, vec3(0, 4, 0), vec3(1, 0.6, 0), vec3(1, 0.1, 0.01)));
	rp.addLight(new Light(1, 1, vec3(3, 4, 20), vec3(0, .6, 1), vec3(1, 0.1, 0.01)));
	rp.setDirectionalLight(new DirectionalLight(vec3(-2, -10, 5), vec3(0.3f, 0.7, 0.5), vec3(1, 1, 1), 5));

	pw = new PhysicsWorld(4,2);
	wood = loadpng("../res/textures/wood.png");
	wood2 = loadpng("../res/textures/wood2.png");
	grass = loadpng("../res/textures/grass.png");


	environ = new Environment(*pw);
	{
		Body *b = new Body(*pw, id);
		b->velocity.setX(0);
		b->position.setY(-4);
		b->inv_Mass = 0;
		b->friction = 0.5f;
		objects.push_back(new BodyObj(Transform(), cube, grass, *b, vec3(100, 4, 100)));
		pw->bodies.push_back(b);
	}
	for(int i = 0; i<100; i++) {
		Body *b = new Body(*pw, id);
		b->position.setX(3 + rand()%5);
		b->position.setY(i/5.f);
		b->position.setZ(-3 -rand()%5);
		b->inv_Mass = 1;
		b->friction = 0.5f;
		if(rand()%10 > 5){
			objects.push_back(new BodyObj(Transform(), cube, wood, *b, vec3(0.5, 0.5, 0.5)));
		}else{
			objects.push_back(new BodyObj(Transform(), cube, wood2, *b, vec3(0.5, 0.5, 0.5)));
		}

		pw->bodies.push_back(b);
	}

	body = new Body(*pw, id);
	body->position.setY(4);
	body->friction = 1;
	body->inv_Mass = 0.5f;
	body->elements.push_back(new Element(*body, new AABB(vec3(0, 0, 0), vec3(0.25f, 1, 0.25f))));
	pw->bodies.push_back(body);

	rp.setObjs(&objects);


}


void SimpleScene::stop() {
	delete camera;
	delete pw;
	delete environ;
}
float speed = 0;
void SimpleScene::input(float dt) {
	vec3 movement = 0;
	vec3 look = vec3(sin(camera->horizontalangle), 0, -cos(camera->horizontalangle));
	vec3 perplook = vec3::getCrossProduct(look, vec3(0, 1, 0));
	float y = body->velocity.getY();
	if(Engine::getEngine().getInput().isDown(KEY_W)){
		movement += ((look));
	}
	if(Engine::getEngine().getInput().isDown(KEY_S)){
		movement += ((-look));
	}
	if(Engine::getEngine().getInput().isDown(KEY_A)){
		movement += ((-perplook));
	}
	if(Engine::getEngine().getInput().isDown(KEY_D)){
		movement += ((perplook));
	}
	if(movement.calculateMagnitudeS() > 0){
		speed += 100 * dt;
		body->friction = 0;
	}else{
		speed = 0;
		body->friction = 1;
	}
	speed = std::fminf(speed, 6);
	movement.normalize();
	float cspeed = body->velocity.dot(movement);
	float speed_diff = speed - cspeed;
	if(speed_diff > 0){
		body->velocity+=movement * speed_diff;
	}
	body->velocity.setY(y);
	if(Engine::getEngine().getInput().isPressed(KEY_SPACE)){
		body->applyImpulse(vec3(0, 30, 0));
	}
}

SDL_bool grabbed = SDL_FALSE;
void SimpleScene::update(float dt) {
	if(Engine::getEngine().getInput().isPressed(MOUSE_1)){
		grabbed = grabbed == SDL_TRUE? SDL_FALSE : SDL_TRUE;
		SDL_SetRelativeMouseMode(grabbed);
	}
	camera->update(dt);
	pw->update(dt);
	camera->transform.setPos(body->position + vec3(0, 0.5f, 0), this);
	for(Obj* obj : objects){
		obj->update(dt);
	}
}

void SimpleScene::render() {
	rp.render();
}




void SimpleScene::pause() {

}

void SimpleScene::resume() {

}

