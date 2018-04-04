//
// Created by Pierre-Yves Boers on 04/04/2018.
//

#include "BodyObj.h"
#include "../physics/shapes/AABB.h"

BodyObj::BodyObj(const Transform &transform, Mesh &mesh, Body &body, vec3 scale) : Obj(transform, mesh), body(body) {
	body.elements.push_back(new Element(body, new AABB(vec3(0, 0, 0), scale)));
	this->transform.setScale(scale *2 , this);
}

void BodyObj::update(float dt) {
	transform.setPos(body.position.getCopy(), this);
	transform.setRot(body.orientation.getCopy(), this);
}
