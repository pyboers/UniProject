//
// Created by Pierre-Yves Boers on 04/04/2018.
//

#include "BodyObj.h"
#include "../physics/shapes/AABB.h"

BodyObj::BodyObj(const Transform &transform, Mesh &mesh, Texture* t, Body &body) : Obj(transform, mesh, t), body(body) {
	body.elements.push_back(new Element(body, new AABB(vec3(0, 0, 0), this->transform.getScale()/2)));
}

void BodyObj::update(float dt) {
	transform.setPos(body.position.getCopy(), this);
	transform.setRot(body.orientation.getCopy(), this);
}
