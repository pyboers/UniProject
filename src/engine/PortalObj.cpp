//
// Created by Pierre-Yves Boers on 15/04/2018.
//

#include "PortalObj.h"
#include "../physics/shapes/AABB.h"
#include "../scenes/PortalCollisionListener.h"


PortalObj::PortalObj(const Transform &transform, Mesh& mesh, Texture* texture, Body &body) : Obj(transform, mesh, texture), body(body){
	Element *element = new Element(body, new AABB(vec3(0, 0, 0), this->transform.getScale()/2));
	element->addListener(new PortalCollisionListener());
	body.elements.push_back(element);
}

void PortalObj::bindPortal(PortalObj *bound) {
	this->bound = bound;
}

void PortalObj::update() {
	transform.setPos(body.position.getCopy(), this);
}
