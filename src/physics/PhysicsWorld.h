//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_PHYSICSWORLD_H
#define UNIPROJECT_PHYSICSWORLD_H

#include <vector>
#include <unordered_set>
#include "Body.h"
#include "constraints/ConstraintSolver.h"
#include "constraints/manifold/CollisionDetector.h"

class PhysicsWorld{
protected:
	ConstraintSolver *solver;
	CollisionDetector *collisionDetector;
	std::vector<Constraint *> past;
	std::vector<Constraint*> constraints;
	int frequency;


public:
	std::vector<Body*> bodies;
	PhysicsWorld(int count, int frequency);
	~PhysicsWorld();

	void update(float dt);

};
#endif //UNIPROJECT_PHYSICSWORLD_H
