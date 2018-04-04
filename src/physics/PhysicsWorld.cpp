//
// Created by Pierre-Yves Boers on 10/02/2018.
//
#include "PhysicsWorld.h"
#include "constraints/IterativeSolver.h"
#include "constraints/manifold/SlowBroadPhase.h"

PhysicsWorld::PhysicsWorld(int count, int frequency) : frequency(frequency) {
	solver = new IterativeSolver(count);
	collisionDetector = new SlowBroadPhase(bodies);
	//create collision detector and solver
}

PhysicsWorld::~PhysicsWorld() {
	delete solver;
	delete collisionDetector;
}

void PhysicsWorld::update(float dt) {
	dt = math::clamp(dt, 0.001, 1);
	dt/= frequency;
	for(int step = 0; step < frequency; step++){
		for (Body *b : bodies) {
			b->integrate(dt);
		}
		for(auto c : constraints){
			c->update(dt);
		}
		collisionDetector->update();
		std::vector<Constraint *> collisions = collisionDetector->detectCollisions();
		std::vector<Constraint *> allconst;
		allconst.reserve(collisions.size() + constraints.size());
		for(auto c : collisions){
			allconst.push_back(c);
		}
		for(auto c : constraints){
			allconst.push_back(c);
		}
		solver->solve(collisions, dt);
		for(auto c : collisions){
			delete c;
		}

		for (Body *b : bodies) {
			b->update(dt);
		}
	}


}
