//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_COLLISION_H
#define UNIPROJECT_COLLISION_H

#include "../../Body.h"

class Collision{ //Todo: add friction
	friend class Manifold;
protected:
	Body &a;
	Body &b;
	vec3 normal, mtv, friction;
	vec3 pointA, pointB;
	float normalImpulseSum, frictionImpulseSum;

	Collision(Body &a, Body &b, const vec2& mtv, const vec2& normal, const vec2& point);


};
#endif //UNIPROJECT_COLLISION_H
