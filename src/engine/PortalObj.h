//
// Created by Pierre-Yves Boers on 15/04/2018.
//

#ifndef UNIPROJECT_WORMHOLEOBJ_H
#define UNIPROJECT_WORMHOLEOBJ_H


#include "../maths/Transform.h"
#include "../graphics/Mesh.h"
#include "Obj.h"
#include "BodyObj.h"

class PortalObj : public Obj{
public:
	PortalObj* bound;
	Body &body;
	explicit PortalObj(const Transform &transform, Mesh& mesh, Texture *texture, Body& body);

	void bindPortal(PortalObj *bound);

	void update();
};


#endif //UNIPROJECT_WORMHOLEOBJ_H
