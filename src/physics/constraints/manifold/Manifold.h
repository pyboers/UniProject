//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_MANIFOLD_H
#define UNIPROJECT_MANIFOLD_H

#include <vector>
#include "../BinaryConstraint.h"
#include "Collision.h"

class Manifold : public BinaryConstraint{
protected:
	float friction;
public:
	int persistance = 0;
	std::vector<Collision> points;
	Manifold(Element &a, Element &b, vec3* collisioninfo, int length);

	static float getBiasImpulse(const Collision& c, float dt) {
		float slop = 0.001f;
		float strength = 0.1f;
		float s = c.mtv.calculateMagnitude() - slop;
		if (s > 0) {
			return (strength / dt) * s;
		}
		return 0;
	}

	void update(float dt) override;
	void solve(float dt) override;
};


#endif //UNIPROJECT_MANIFOLD_H
