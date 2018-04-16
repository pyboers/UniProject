//
// Created by Pierre-Yves Boers on 11/11/2017.
//

#include <iostream>
#include "Environment.h"
#include "../physics/shapes/Boundless.h"
#include "../engine/Engine.h"


Environment::Environment(PhysicsWorld& pw) : ElementListener(){
	vec3 pos = vec3(0);
	mat3 zeromat;
	Body *body = new Body(pw, zeromat);
	pw.bodies.push_back(body);
	Element *env = new Element(*body, new Boundless());
	env->addListener(this);
	body->elements.push_back(env);
}
int i = 0;
bool Environment::onCollide(const Manifold &m, bool isA) {
	i++;
	float drag = 0.8f;
	vec3 gravity = vec3(0, -50.81f, 0);
	Element &e = isA ? m.b : m.a;
	Body &other = e.body;
	if (other.inv_Mass != 0 && !Engine::getEngine().getInput().isDown(KEY_T)) {
		other.applyForce(gravity / other.inv_Mass);
//		if(i%1000 == 0){
//			other.applyForce(vec3(i%600, 500, -i%500));
//		}else if(i%500 == 0){
//			other.applyForce(vec3(-i%600, 500, i%500));
//		}
	}
	return false;
}