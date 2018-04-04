//
// Created by Pierre-Yves Boers on 04/04/2018.
//

#include "BodyObj.h"

BodyObj::BodyObj(const Transform &transform, Mesh &mesh, Body &body) : Obj(transform, mesh), body(body) {

}

void BodyObj::update(float dt) {
	transform.setPos(body.position.getCopy(), this);
	printf("POS: %f", body.position.getY());
	transform.setRot(body.orientation.getCopy(), this);
}
