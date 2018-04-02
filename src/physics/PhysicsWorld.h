//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_PHYSICSWORLD_H
#define UNIPROJECT_PHYSICSWORLD_H

#include <vector>
#include "Body.h"
#include "constraints/ConstraintSolver.h"
#include "constraints/manifold/CollisionDetector.h"

class PhysicsWorld{
protected:
	std::vector<Body*> bodies;
	ConstraintSolver *solver;
	CollisionDetector *collisionDetector;

public:
	PhysicsWorld(int count, int frequency);
	~PhysicsWorld();

	void update(float dt);

};
#endif //UNIPROJECT_PHYSICSWORLD_H
