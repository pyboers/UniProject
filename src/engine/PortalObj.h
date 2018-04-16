//
// Created by Pierre-Yves Boers on 15/04/2018.
//

#ifndef UNIPROJECT_WORMHOLEOBJ_H
#define UNIPROJECT_WORMHOLEOBJ_H


#include "../maths/Transform.h"
#include "../graphics/Mesh.h"
#include "Obj.h"

class PortalObj : public Obj{
public:
	PortalObj* bound;
	explicit PortalObj(const Transform &transform, Mesh& mesh, Texture *texture);

	void bindPortal(PortalObj *bound);
};


#endif //UNIPROJECT_WORMHOLEOBJ_H
