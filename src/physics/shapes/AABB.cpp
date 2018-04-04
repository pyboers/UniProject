//
// Created by Pierre-Yves Boers on 03/04/2018.
//

#include "AABB.h"

AABB::AABB(vec3 position, vec3 dimensions) : Shape(position), dimensions(dimensions){

}

shapeType AABB::getType() const {
	return Type_AABB;
}

const vec3 &AABB::getDimensions() const {
	return dimensions;
}
