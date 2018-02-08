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
	std::vector<Collision> points;
public:
	Manifold(Element &a, Element &b, vec3* collisioninfo, int length);
	virtual void update(float dt) override;
	virtual void solve(float dt) override;
};


#endif //UNIPROJECT_MANIFOLD_H
