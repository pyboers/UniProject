//
// Created by Pierre-Yves Boers on 07/02/2018.
//

#pragma once
#ifndef UNIPROJECT_TRANSFORM_H
#define UNIPROJECT_TRANSFORM_H

#include <map>
#include "mat4.h"
#include "quat.h"

class Transform {

private:
	std::map<void*, bool> trackers;

	vec3 pos;
	quat rot;
	vec3 scale;


	bool changed;

	void change(void * subscriber);


public:

/**
 * create empty transform.
 */
	Transform();

/**
 * create pos transform.
 *
 * @param pos pos
 */


	Transform(vec3 pos);

/**
 * create no rot transform.
 * @param pos pos
 * @param scale scale
 */


	Transform(vec3 pos, vec3 scale);


	/**
	 * Rotates the transform around the axis.
	 * @param axis the axis to rotate around
	 * @param angle the amount to rotate by
	 * @param subscriber signature of the caller.
	 */
	void rotate(vec3 axis, float angle, void * const subscriber);

	/**
	 * has changed.
	 * @return has changed
	 */
	bool hasChanged(void* const subscriber);

/**
 * get transformation matrix.
 *
 * @return transformation matrix
 */


	mat4 getMatrix();


	const vec3 &getPos();


	Transform *setPos(const vec3 &pos, void * const subscriber);


	void addToPos(const vec3 &addVec, void * const subscriber);


	const quat &getRot();


	void setRot(const quat &rotation, void * const subscriber);


	const vec3 &getScale();


	void setScale(const vec3 &scale, void * const subscriber);



};
#endif //UNIPROJECT_TRANSFORM_H
