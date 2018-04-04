//
// Created by Pierre-Yves Boers on 04/04/2018.
//

#ifndef UNIPROJECT_BODYOBJ_H
#define UNIPROJECT_BODYOBJ_H


#include "Obj.h"
#include "../physics/Body.h"

class BodyObj : public Obj{
	Body &body;
public:
	BodyObj(const Transform &transform, Mesh &mesh, Body& body, vec3 scale);

	void update(float dt) override;

};


#endif //UNIPROJECT_BODYOBJ_H
