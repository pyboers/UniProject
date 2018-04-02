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
	vec3 force, position, velocity;
	// avoids dividing by mass every time we apply a force. We only do it when we integrate.
	/*
	 * angular
	 */
	vec3 torque, angularMomentum, angularVelocity; //directly calculating momentum from
	// torque avoids multiplying by inv_Tensor every time we apply a torque. We only multiply when integrating.
	quat orientation;
	/*
	 * properties
	 */
	float inv_Mass;
	mat3 inv_InertiaTensor;
	float friction;
	float restitution;

	PhysicsWorld &world;

public:
	Body(vec3& position, float mass, mat3 inv_InertiaTensor, float restitution, float friction, PhysicsWorld& world);
	~Body();


	void integrate(float dt);
	void update(float dt);

	void applyForce(const vec3& f);
	void applyForce(const vec3& f, const vec3& point);

	void applyImpulse(const vec3& point, const vec3& impulse);
	void applyImpulse(const vec3& impulse);

	vec3 getPointVelocity(const vec3& point);


private:
	vec3 angularMomentumToAngularVelocity()const;

};
#endif //UNIPROJECT_BODY_H
