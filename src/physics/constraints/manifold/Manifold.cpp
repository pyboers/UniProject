//
// Created by Pierre-Yves Boers on 09/02/2018.
//

#include "Manifold.h"
#include "../../../maths/MyMath.h"

Manifold::Manifold(Element &a, Element &b, vec3 *collisioninfo, int length) : BinaryConstraint(a, b) {
	points.reserve(length/3);
	int i;
	for(i = 0; i < length; i++){
		points.push_back(Collision(a.body, b.body, collisioninfo[i*3], collisioninfo[(i*3) + 1], collisioninfo[(i*3) + 2]));
	}
}

void Manifold::update(float dt) { //Reset the accumulators
	for (auto &c : points) {
		c.normalImpulseSum = 0;
		c.tangentImpulseSum1 = 0;
		c.tangentImpulseSum2 = 0;
	}
}

void Manifold::solve(float dt) {
	for (auto &c : points) {
		vec3 relativeVelocity = b.body.getPointVelocity(c.pointB) - a.body.getPointVelocity(c.pointA);
		float normalVel = relativeVelocity.dot(c.normal);

		float j = ((((1 + (c.a.restitution*c.b.restitution))*normalVel) + getBiasImpulse(c, dt))*c.divisorN);
		float nIS = c.normalImpulseSum;
		c.normalImpulseSum += j;
		c.normalImpulseSum = c.normalImpulseSum < 0 ? 0 : c.normalImpulseSum;
		j = c.normalImpulseSum - nIS;

		vec3 impulseVector = c.normal * j;

		a.body.applyImpulse(c.pointA, impulseVector);
		b.body.applyImpulse(c.pointB, -impulseVector);

	}

	for (auto &c : points) {
		vec3 impulseVector1;
		vec3 impulseVector2;
		float bound = friction * c.normalImpulseSum;
		//tangent1
		{
			vec3 relativeVelocity = b.body.getPointVelocity(c.pointB) - a.body.getPointVelocity(c.pointA);
			float tangentVel = relativeVelocity.dot(c.tangent1);
			float j = (((tangentVel) + getBiasImpulse(c, dt))*c.divisorT1);
			float tIS = c.tangentImpulseSum1;
			c.tangentImpulseSum1 += j;
			c.tangentImpulseSum1 = math::clamp(c.tangentImpulseSum1, -bound, bound);
			j = c.tangentImpulseSum1 - tIS;

			impulseVector1 = c.tangent1 * j;
		}
		//tangent2
		{
			vec3 relativeVelocity = b.body.getPointVelocity(c.pointB) - a.body.getPointVelocity(c.pointA);
			float tangentVel = relativeVelocity.dot(c.tangent2);

			float j = (((tangentVel) + getBiasImpulse(c, dt))*c.divisorT2);
			float tIS = c.tangentImpulseSum2;
			c.tangentImpulseSum2 += j;
			c.tangentImpulseSum2 = math::clamp(c.tangentImpulseSum2, -bound, bound);
			j = c.tangentImpulseSum2 - tIS;

			impulseVector2 = c.tangent2 * j;
		}

		//Apply friction along the first tangent
		a.body.applyImpulse(c.pointA, impulseVector1);
		b.body.applyImpulse(c.pointB, -impulseVector1);
		//apply friction along the second tangent
		a.body.applyImpulse(c.pointA, impulseVector2);
		b.body.applyImpulse(c.pointB, -impulseVector2);

	}

}
