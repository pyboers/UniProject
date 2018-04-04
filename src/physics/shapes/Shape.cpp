//
// Created by Pierre-Yves Boers on 03/02/2018.
//
#include <cstdio>
#include "Shape.h"
#include "AABB.h"

/* AABB*/

const vec3 &Shape::getPosition() const {
	return position;
}

const quat &Shape::getRotation() const {
	return rotation;
}

Shape::Shape(vec3 position) : position(position) {

}

Shape::Shape() {

}

Shape::Shape(vec3 position, quat rotation) : position(position), rotation(rotation){

}

void Shape::getCollisionInfo(const Shape *s1, const Shape *s2, vec3 **collisions, int *count) {
	if(s1->getType() == Type_AABB && s2->getType() == Type_AABB){
		return calcCollisionInfo(*static_cast<const AABB*>(s1), *static_cast<const AABB*>(s2), collisions, count);
	}
}

void Shape::calcCollisionInfo(const AABB &a1, const AABB &a2, vec3 **collisions, int *count) {
	float sWidth = a1.getDimensions().getX() + a2.getDimensions().getX();
	float sHeight = a1.getDimensions().getY() + a2.getDimensions().getY();
	float sDepth = a1.getDimensions().getZ() + a2.getDimensions().getZ();
	float distancex = fabsf(a1.getPosition().getX() - a2.getPosition().getX()) - sWidth;
	float distancey = fabsf(a1.getPosition().getY() - a2.getPosition().getY()) - sHeight;
	float distancez = fabsf(a1.getPosition().getZ() - a2.getPosition().getZ()) - sDepth;
	if(distancex < 0 && distancey < 0 && distancez < 0){ //collision
		if(distancex >= distancey && distancex >= distancez){ //X MTV
			if(a1.getPosition().getX() < a2.getPosition().getX()){
				(*collisions) = new vec3[3];
				(*collisions)[0] = vec3(-distancex, 0, 0);
				(*collisions)[1] = vec3(-1, 0, 0);
				(*collisions)[2] = a1.getPosition();
				*count = 1;
				return;
			}else{
				(*collisions) = new vec3[3];
				(*collisions)[0] = vec3(-distancex, 0, 0);
				(*collisions)[1] = vec3(1, 0, 0);
				(*collisions)[2] = a1.getPosition();
				*count = 1;
				return;
			}
		}else if(distancey >= distancex && distancey >= distancez){ //Y MTV
			if(a1.getPosition().getY() < a2.getPosition().getY()){
				(*collisions) = new vec3[3];
				(*collisions)[0] = vec3(0, distancey, 0);
				(*collisions)[1] = vec3(0, -1, 0);
				(*collisions)[2] = a1.getPosition();
				*count = 1;
				return;
			}else{
				(*collisions) = new vec3[3];
				(*collisions)[0] = vec3(0, -distancey, 0);
				(*collisions)[1] = vec3(0, 1, 0);
				(*collisions)[2] = a1.getPosition();
				*count = 1;
				return;

			}
		}else{ //Z MTV
			if(a1.getPosition().getZ() < a2.getPosition().getZ()){
				(*collisions) = new vec3[3];
				(*collisions)[0] = vec3(0, 0, distancez);
				(*collisions)[1] = vec3(0, 0, -1);
				(*collisions)[2] = a1.getPosition();
				*count = 1;
				return;
			}else{
				(*collisions) = new vec3[3];
				(*collisions)[0] = vec3(0, 0, distancez);
				(*collisions)[1] = vec3(0, 0, 1);
				(*collisions)[2] = a1.getPosition();
				*count = 1;
				return;
			}
		}
	}
	*count = 0;
}
