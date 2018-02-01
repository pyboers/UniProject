//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_PHYSICSWORLD_H
#define UNIPROJECT_PHYSICSWORLD_H

#include <vector>
#include "Body.h"

class PhysicsWorld{
public:
	std::vector<Body*> bodies;
	int frequency;
	PhysicsWorld(int count, int frequency);
	~PhysicsWorld();

	void update(float dt);

};
#endif //UNIPROJECT_PHYSICSWORLD_H