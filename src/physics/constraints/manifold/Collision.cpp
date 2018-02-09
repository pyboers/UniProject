//
// Created by Pierre-Yves Boers on 03/02/2018.
//
#include "Collision.h"

Collision::Collision(Body &a, Body &b, const vec3 &mtv, const vec3 &normal, const vec3 &point) : a(a), b(b), mtv(mtv), normal(normal),pointA(point - a.position), pointB(point + mtv - b.position), normalImpulseSum(0), tangentImpulseSum1(0), tangentImpulseSum2(0) {
	divisorN = b.inv_Mass + a.inv_Mass +
			((b.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointB, normal), pointB))
			 + (a.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointA, normal), pointA))).dot(normal);




	//assign tangent!!!!!!!	//Todo: Experiment to remove artifacting




	divisorT1 = b.inv_Mass + a.inv_Mass +
			   ((b.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointB, tangent1), pointB))
				+ (a.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointA, tangent1), pointA))).dot(tangent1); //Using two tangents since the tangential direction might change over iterations of the solver. Note this can create artifacting. If one direction acts as "static"friction and the other doesn't it might misbehave.
	divisorT2 = b.inv_Mass + a.inv_Mass +
				((b.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointB, tangent2), pointB))
				 + (a.inv_InertiaTensor * vec3::getCrossProduct(vec3::getCrossProduct(pointA, tangent2), pointA))).dot(tangent2);
}
