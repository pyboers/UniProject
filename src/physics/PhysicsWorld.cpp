//
// Created by Pierre-Yves Boers on 10/02/2018.
//
#include "PhysicsWorld.h"
#include "constraints/IterativeSolver.h"
#include "constraints/manifold/SlowBroadPhase.h"
#define warmstarting true
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
	dt /= frequency;
	for (int step = 0; step < frequency; step++) {
		for (Body *b : bodies) {
			b->integrate(dt);
		}
		for (auto c : constraints) {
			c->update(dt);
		}
		collisionDetector->update();
		std::vector<Constraint *> collisions = collisionDetector->detectCollisions();
		std::vector<Constraint *> allconst;
		allconst.reserve(collisions.size() + constraints.size());
		for (auto c : collisions) {
			if (warmstarting && !past.empty()) {
				Manifold *presentMan = static_cast<Manifold *>(c);
				for (Constraint *pc : past) {
					Manifold *pastMan = static_cast<Manifold *>(pc);
					if (presentMan->a.shape->getType() == Type_AABB && pastMan->a.shape->getType() == Type_AABB) {
						if (pastMan->a.shape == presentMan->a.shape && pastMan->b.shape ==
																	   presentMan->b.shape) {

							presentMan->persistance = pastMan->persistance + 1;
							//Normal
							{
								presentMan->points[0].normalImpulseSum = pastMan->points[0].normalImpulseSum * 0.6f;
								presentMan->a.body.applyImpulse(
										presentMan->points[0].normal * presentMan->points[0].normalImpulseSum);
								presentMan->b.body.applyImpulse(
										-presentMan->points[0].normal * presentMan->points[0].normalImpulseSum);
							}
							//Tangent1
							{
								presentMan->points[0].tangentImpulseSum1 = pastMan->points[0].tangentImpulseSum1 * 0.6f;
								presentMan->a.body.applyImpulse(
										presentMan->points[0].tangent1 * presentMan->points[0].tangentImpulseSum1);
								presentMan->b.body.applyImpulse(
										-presentMan->points[0].tangent1 * presentMan->points[0].tangentImpulseSum1);
							}
							//Tangent2
							{
								presentMan->points[0].tangentImpulseSum2 = pastMan->points[0].tangentImpulseSum2 * 0.6f;
								presentMan->a.body.applyImpulse(
										presentMan->points[0].tangent2 * presentMan->points[0].tangentImpulseSum2);
								presentMan->b.body.applyImpulse(
										-presentMan->points[0].tangent2 * presentMan->points[0].tangentImpulseSum2);
							}
						}
					}
				}
			}
			allconst.push_back(c);
		}
		for (auto *c : constraints) {
			allconst.push_back(c);
		}
		solver->solve(allconst, dt);

		if(warmstarting){
			for (auto *c : past) {
				delete c;
			}
			past.clear();
		}
		for (auto *c : collisions) {
			past.push_back(c);
		}

		for (Body *b : bodies) {
			b->update(dt);
		}
	}


}
