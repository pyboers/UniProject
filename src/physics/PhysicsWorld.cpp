//
// Created by Pierre-Yves Boers on 10/02/2018.
//
#include "PhysicsWorld.h"

PhysicsWorld::PhysicsWorld(int count, int frequency) {
	//create collision detector and solver
}

PhysicsWorld::~PhysicsWorld() {
	delete solver;
	delete collisionDetector;
}
