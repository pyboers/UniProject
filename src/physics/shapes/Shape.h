//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_SHAPE_H
#define UNIPROJECT_SHAPE_H

#include "../../maths/vec3.h"
#include "../../maths/quat.h"

enum shapeType {
	Type_AABB, Type_BOUNDLESS
};
class AABB;
class Boundless;
class Shape{
protected:
	vec3 position;
	quat rotation;



public:
	Shape();
	Shape(vec3 position);
	Shape(vec3 position, quat rotation);

	virtual void update(vec3 position, quat rotation){
		this->position = position;
		this->rotation = rotation;
	}

	virtual shapeType getType() const = 0;

	const vec3 &getPosition() const;

	const quat &getRotation() const;

	virtual bool isPointInside(vec3 point) const = 0;

	/*
	 * CollisionDetection
	 */
	/**
	 *
	 * @param s1 Shape 1
	 * @param s2 Shape 2
	 * @param collisions The array to fill with collision information stored as: {mtv_1, normal_1, coordinate_1... mtv_n, normal_n, coordinate_n}
	 * @param count
	 */
	static void getCollisionInfo(const Shape *s1, const Shape *s2, vec3 **collisions, int *count);

	/* AABB*/
	static void calcCollisionInfo(const AABB &a1, const AABB &a2, vec3 **collisions, int *count);
	static void calcCollisionInfo(const AABB &a1, const Boundless &b2, vec3 **collisions, int *count);

	/* Boundless*/

	static void calcCollisionInfo(const Boundless &b1, const AABB &a2, vec3 **collisions, int *count);
	static void calcCollisionInfo(const Boundless &a1, const Boundless &a2, vec3 **collisions, int *count);


};
#endif //UNIPROJECT_SHAPE_H
