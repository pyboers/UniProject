//
// Created by Pierre-Yves Boers on 16/04/2018.
//

#include "PortalCollisionListener.h"
#include "../physics/constraints/manifold/Manifold.h"
bool PortalCollisionListener::onCollide(const Manifold &m, bool isA) {
	Element other = isA ? m.b : m.a;


}
