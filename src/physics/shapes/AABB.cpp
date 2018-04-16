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

bool AABB::isPointInside(vec3 point) const {
	float minx, maxx, miny, maxy, minz, maxz;
	minx = position.getX() - dimensions.getX();
	maxx = position.getX() + dimensions.getX();

	miny = position.getY() - dimensions.getY();
	maxy = position.getY() + dimensions.getY();

	minz = position.getZ() - dimensions.getZ();
	maxz = position.getZ() + dimensions.getZ();

	return point.getX() >= minx && point.getX() <= maxx
		   && point.getY() >= miny && point.getY() <= maxy
		   && point.getZ() >= minz && point.getZ() <= maxz;
}
