//
// Created by Pierre-Yves Boers on 03/04/2018.
//

#include "SlowBroadPhase.h"

SlowBroadPhase::SlowBroadPhase(std::vector<Body *> &bodies) : CollisionDetector(bodies) {}

std::vector<Constraint *> SlowBroadPhase::detectCollisions() {
	std::vector<Constraint*> manifolds;
	int i, j;
	for (i = 0; i < bodies.size() - 1; i++) {
		for (j = i + 1; j < bodies.size(); j++) {
			for (Element* e : bodies[i]->elements) {
				for (Element* e2 : bodies[j]->elements) {
					Constraint *m = detectCollision(*e, *e2);
					if (m != nullptr) {
						manifolds.push_back(m);
					}
				}
			}
		}
	}
	return manifolds;
}

void SlowBroadPhase::update() {

}
