//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_SHAPE_H
#define UNIPROJECT_SHAPE_H

#include "../../maths/vec3.h"
#include "../../maths/quat.h"

enum shapeType {
	Type_AABB
};
class AABB;
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


};
#endif //UNIPROJECT_SHAPE_H
