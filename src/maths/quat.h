//
// Created by Pierre-Yves Boers on 01/02/2018.
//

#pragma once
#ifndef UNIPROJECT_QUAT_H
#define UNIPROJECT_QUAT_H

#include "vec3.h"
class mat4;
class quat{
	friend class mat4;
private:
	float x;
	float y;
	float z;
	float w;

public:
	quat();

	/**
	 * Creates a Quaternion from 4 values. (used primarily for copy instructions)
	 *
	 * @param w w component
	 * @param x x component
	 * @param y y component
	 * @param z z component
	 */
	quat(float w, float x, float y, float z);

	/**
	 * creates a Quaternion from an axis and an angle.
	 *
	 * @param axis the axis
	 * @param angle the angle about the axis
	 */
	quat(vec3 axis, float angle);

	float length() const;

	quat inverse() const;

	/**
	 * gets the version of this quaternion normalized.
	 *
	 * @return the version of this quaternion
	 */
	quat normalized() const;

	quat conjugate() const;

	quat operator*(float r) const;

	/**
	 * performs Quaternion to Quaternion multiplication with another Quaternion.
	 * @param r another Quaternion
	 * @return the product
	 */
	quat operator*(quat r) const;

	quat operator*=(quat r);

	/**
	 * performs Quaternion to 3D vector multiplication with another Quaternion.
	 * @param r a vector
	 * @return the product
	 */
	quat operator*(vec3 r) const ;

	quat operator-(quat r) const;

	quat operator+(quat r) const;

	/**
	 * Gets the version of this vector rotated.
	 *
	 * @param rotation rotation amount
	 * @return the version of this vector rotated
	 */
	vec3 rotatedVec3(const vec3& v2) const;

	void rotateVec3(vec3& v2) const;

	/**
	 * creates a rotation matrix from this Quaternion.
	 * @return the rotation matrix.
	 */
	mat4 toRotationMatrix() const;

	float dot(quat r) const;

	/**
	 * performs NLerp between this Quaternion and a desired Quaternion.
	 *
	 * @param dest desired Quaternion
	 * @param lerpFactor lerp factor
	 * @param shortest shortest
	 * @return NLerp of this Quaternion towards dest by lerp factor
	 */
	quat nLerp(quat dest, float lerpFactor, bool shortest) const;

	/**
	 * performs SLerp between this Quaternion and a desired Quaternion.
	 *
	 * @param dest desired Quaternion
	 * @param lerpFactor lerp factor
	 * @param shortest shortest
	 * @return SLerp of this Quaternion towards dest by lerp factor
	 */
	quat sLerp(quat dest, float lerpFactor, bool shortest) const;

	vec3 getForward() const;

	vec3 getBack() const;

	vec3 getUp() const;

	vec3 getDown() const;

	vec3 getRight() const;

	vec3 getLeft() const;

	/**
	 * direct set method (used for copy instructions).
	 *
	 * @param w w component
	 * @param x x component
	 * @param y y component
	 * @param z z component
	 * @return this Quaternion
	 */
	void set(float w, float x, float y, float z);

	void set(quat r);

	static quat fromEulerDeg(vec3 eulerAngles);

	/**
	 * converts euler angles to a quaternion for easy setting.
	 *
	 * @param eulerAngles the input euler angles
	 *
	 * @see <a href="https://en.wikipedia.org/wiki/Euler_angles#Proper_Euler_angles">Wikipedia's
	 * Article on Euler Angles</a> for a description of their usage/definition.
	 *
	 * @return The {@link quat} associated with the Euler angles.
	 */
	static quat fromEuler(vec3 eulerAngles);

	vec3 toEulerAngles() const;

	float toEulerX() const;
	float toEulerY() const;
	float toEulerZ() const;

	float getX() const;

	void setX(float x);

	float getY() const;

	void setY(float y);

	float getZ() const;

	void setZ(float z);

	float getW() const;

	void setW(float w);

	bool operator==(const quat& other) const;

	quat getCopy() const;


};
#endif //UNIPROJECT_QUAT_H
