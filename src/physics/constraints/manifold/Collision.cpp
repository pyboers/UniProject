//
// Created by Pierre-Yves Boers on 03/02/2018.
//
#include "Collision.h"

Collision::Collision(Body &a, Body &b, const vec3 &mtv, const vec3 &normal, const vec3 &point) : a(a), b(b), mtv(mtv), normal(normal),pointA(point - a.position), pointB(point + mtv - b.position), normalImpulseSum(0), tangentImpulseSum1(0), tangentImpulseSum2(0) {
	//Assign normal impulse calculation's denominator
	divisorN = b.inv_Mass + a.inv_Mass +
			((b.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointB, normal), pointB))
			 + (a.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointA, normal), pointA))).dot(normal);

	//assign tangents
	vec3 relativeVelocity = b.getPointVelocity(this->pointB) - a.getPointVelocity(this->pointA);
	float nVel = relativeVelocity.dot(normal);
	tangent1 = relativeVelocity - (normal * nVel);
	if(tangent1.calculateMagnitudeS() > 0){ //If not pointing in same direction
		tangent1.normalize();
	}else{//Velocity is not tangential to normal, pick arbitrary tangents.
		tangent1 = normal.dot(vec3::up()) != 0 ? vec3::getCrossProduct(normal, vec3::up())
											 : vec3::getCrossProduct(normal, vec3::right());
		tangent1.normalize();
	}
	tangent2 = vec3::getCrossProduct(normal, tangent1);

	//Assign first tangential direction's impulse denominator
	divisorT1 = b.inv_Mass + a.inv_Mass +
			   ((b.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointB, tangent1), pointB))
				+ (a.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointA, tangent1), pointA))).dot(tangent1); //Using two tangents since the tangential direction might change over iterations of the solver. Note this can create artifacting. If one direction acts as "static"friction and the other doesn't it might misbehave.
	//Assign second tangential direction's impulse denominator
	divisorT2 = b.inv_Mass + a.inv_Mass +
				((b.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointB, tangent2), pointB))
				 + (a.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointA, tangent2), pointA))).dot(tangent2);
}
