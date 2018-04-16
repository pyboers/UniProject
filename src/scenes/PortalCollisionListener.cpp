//
// Created by Pierre-Yves Boers on 16/04/2018.
//

#include "PortalCollisionListener.h"
#include "../physics/constraints/manifold/Manifold.h"
bool PortalCollisionListener::onCollide(Manifold &m, bool isA) {
	return false;
}

bool PortalCollisionListener::onCollideStart(Manifold &m, bool isA) {
	printf("Tada\n");
	return false;
}
