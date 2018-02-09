//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_COLLISION_H
#define UNIPROJECT_COLLISION_H

#include "../../Body.h"

class Collision{
	friend class Manifold;
protected:
	Body &a;
	Body &b;
	vec3 normal, mtv, tangent1, tangent2;
	vec3 pointA, pointB;
	float normalImpulseSum, tangentImpulseSum1, tangentImpulseSum2;
	float divisorN, divisorT1, divisorT2;

	Collision(Body &a, Body &b, const vec3& mtv, const vec3& normal, const vec3& point);


};
#endif //UNIPROJECT_COLLISION_H
