//
// Created by Pierre-Yves Boers on 10/02/2018.
//
#include "Body.h"

void Body::applyForce(const vec3 &f) {
	force += f;
}

void Body::applyForce(const vec3 &f, const vec3 &point) {
	force += f;
	torque += vec3::getCrossProduct(point, f);
}

vec3 Body::getPointVelocity(const vec3 &point) {
	return velocity + (vec3::getCrossProduct(angularVelocity, point));
}

void Body::applyImpulse(const vec3 &point, const vec3 &impulse) {
	velocity += impulse * inv_Mass;
	angularMomentum += vec3::getCrossProduct(point, impulse);
	angularVelocity = angularMomentumToAngularVelocity();
}

void Body::applyImpulse(const vec3 &impulse) {
	velocity += impulse*inv_Mass;
}

void Body::update(float dt) {
	position += velocity * dt;
	orientation *= quat::fromEuler(angularVelocity * dt);
	for (Element *e : elements) {
		e->update();
	}
}

void Body::integrate(float dt) {
	velocity += (force*dt)*inv_Mass;
	angularMomentum += torque * dt;
	angularVelocity = angularMomentumToAngularVelocity();
	force = 0;
	torque = 0;
}

vec3 Body::angularMomentumToAngularVelocity() const {
	return orientation.rotatedVec3(inv_InertiaTensor * (orientation.inverse().rotatedVec3(angularMomentum)));
}

Body::Body(PhysicsWorld& world, mat3 inv_InertiaTensor, const vec3& position, float mass, float restitution, float friction)
: position(position), inv_InertiaTensor(inv_InertiaTensor), restitution(restitution), friction(friction),
world(world) {
	this->inv_Mass = mass == 0? 0 : 1/mass;
}

Body::~Body() {
	for(Element *e : elements){
		delete e;
	}
}
