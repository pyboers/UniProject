//
// Created by Pierre-Yves Boers on 03/04/2018.
//

#ifndef UNIPROJECT_SLOWBROADPHASE_H
#define UNIPROJECT_SLOWBROADPHASE_H


#include "CollisionDetector.h"

class SlowBroadPhase : public CollisionDetector{
public:
	explicit SlowBroadPhase(std::vector<Body *> &bodies);

	std::vector<Constraint*> collisionDetection() override;

	void update() override;

};


#endif //UNIPROJECT_SLOWBROADPHASE_H
