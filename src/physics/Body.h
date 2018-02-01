//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_BODY_H
#define UNIPROJECT_BODY_H

#include "../maths/vec3.h"
#include "../maths/mat3.h"
#include "../maths/quat.h"

class PhysicsWorld;

class Body{
public:
	/*
	 * linear
	 */
	vec3 position, velocity, acceleration;
	/*
	 * angular
	 */
	vec3 aAcceleration, aVelocity;
	quat a;
	/*
	 * properties
	 */
	float inv_Mass;
	mat3 inv_InertiaTensor;

public:
	Body(vec3& position, PhysicsWorld& world);
	Body(vec3& position, float mass, PhysicsWorld& world);
	Body(vec3& position, float mass, float restitution, PhysicsWorld& world);
	Body(vec3& position, float mass, float restitution, float friction, PhysicsWorld& world);
	Body(vec3& position, float mass, mat3 inv_InertiaTensor, float restitution, float friction, PhysicsWorld& world);
	~Body();


	void integrate(float dt);
	void update(float dt);

	void applyForce(const vec3& f);
	void applyForce(const vec3& f, const vec3& point);

	void applyImpulse(const vec3& point, const vec3& impulse);
	void applyImpulse(const vec3& impulse);

	vec3 getPointVelocity(const vec3& point);

};
#endif //UNIPROJECT_BODY_H
