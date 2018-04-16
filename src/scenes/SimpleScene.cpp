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
Mesh portal;
std::vector<PortalObj* >portals;
void SimpleScene::start() {
	camera = new Camera(0, 0, 0, 1280, 720, 72, .1, 100);
	rp.setCamera(camera);

	cube.loadModel("../res/models/box2.obj");
	portal.loadModel("../res/models/portal.obj");
	mat3 id = mat3();
//	rp.addLight(new Light(0, 1, vec3(0, 4, 0), vec3(1, 0.6, 0), vec3(1, 0.1, 0.01)));
//	rp.addLight(new Light(1, 1, vec3(3, 4, 20), vec3(0, .6, 1), vec3(1, 0.1, 0.01)));
	rp.setDirectionalLight(new DirectionalLight(vec3(-2, -10, 5), vec3(0.3f, 0.7, 0.5), vec3(1, 1, 1), 5));
//	rp.setDirectionalLight(new DirectionalLight(vec3(-2, -10, 5), vec3(0, 0.3, 0.4), vec3(1, 1, 1), 5));

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
		objects.push_back(new BodyObj(Transform(0, vec3(100*2, 4*2, 100*2)), cube, grass, *b));
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
			objects.push_back(new BodyObj(Transform(), cube, wood, *b));
		}else{
			objects.push_back(new BodyObj(Transform(), cube, wood2, *b));
		}

		pw->bodies.push_back(b);
	}

	body = new Body(*pw, id);
	body->position.setY(4);
	body->friction = 1;
	body->inv_Mass = 0.5f;
	Element *e = new Element(*body, new AABB(vec3(0, 0, 0), vec3(0.25f, 1, 0.25f)));
	body->elements.push_back(e);
	pw->bodies.push_back(body);

	Body *p1body = new Body(*pw, id);
	p1body->position = vec3(0, 1, -4);
	pw->bodies.push_back(p1body);
	Body *p2body = new Body(*pw, id);
	p2body->position = vec3(0, 1, 0);
	pw->bodies.push_back(p2body);
	PortalObj* p1 = new PortalObj(Transform(vec3(0, 1, -4), vec3(1, 2, 0.3)), portal, wood, *p1body);
	PortalObj* p2 = new PortalObj(Transform(vec3(0, 1, 0), vec3(1, 2, 0.3)), portal, wood2, *p2body);

	p2->getTransform().setRot(quat::fromEulerDeg(vec3(0, 0, 0)), this);
	p1->getTransform().setRot(quat::fromEulerDeg(vec3(0, 45, 0)), this);
	p1->bindPortal(p2);
	p2->bindPortal(p1);
	portals.push_back(p1);
	portals.push_back(p2);
	rp.setObjs(&objects);
	rp.setPortals(&portals);


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

