//
// Created by Pierre-Yves Boers on 11/11/2017.
//

#ifndef CHALLENGES_ATMOSPHERE_H
#define CHALLENGES_ATMOSPHERE_H

#include "../physics/ElementListener.h"
#include "../physics/PhysicsWorld.h"

class Environment : public ElementListener{
protected:
public:
	explicit Environment(PhysicsWorld& pw);
	bool onCollide(const Manifold& m, bool isA) override;
};


#endif //CHALLENGES_ATMOSPHERE_H
