//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_SHAPE_H
#define UNIPROJECT_SHAPE_H

#include "../maths/vec3.h"
#include "../maths/quat.h"

enum shapeType {
	Type_AABB
};
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

	virtual void getType() const = 0;

	const vec3 &getPosition() const;

	const quat &getRotation() const;

};
#endif //UNIPROJECT_SHAPE_H
