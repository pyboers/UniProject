#pragma once
#ifndef __VEC3_H
#define __VEC3_H
#include <math.h>
#include "MyMath.h"
#include "vec4.h"

class vec3 {

protected:
	float x;
	float y;
	float z;

public:

	/**
	 * Constructs an origin vector.
	 */
	vec3();

	/**
	 * Construct a vector with x, y and z value f.
	 *
	 * @param f the x, y and z values
	 */
	vec3(float f);

	/** Constructs a vector with values of another vector.
	 *
	 * @param v the vector to copy
	 */
	vec3(const vec3& v);

	/**
	 * Constructs a vector with values x, y and z
	 *
	 * @param x
	 * @param y
	 * @param z
	 */
	vec3(float x, float y, float z);

	/**
	 * Sets x member to x.
	 *
	 * @param x x value
	 */
	void setX(float x);

	/**
	 * Sets y member to y.
	 *
	 * @param y y value
	 */
	void setY(float y);

	/**
	 * Sets z member to z.
	 *
	 * @param z z value
	 */
	void setZ(float z);

	/**
	 * Sets x, y and z.
	 *
	 * @param x x value
	 * @param y y value
	 * @param z z value
	 */
	void set(float x, float y, float z);

	/**
	 * Sets this vec3's members to another vec3's members.
	 *
	 * @param v2 other vector
	 */
	void set(const vec3& v2);

	float getX() const;

	float getY() const;

	float getZ() const;

	/**
	 * Gets the length of the vector.
	 *
	 * @return the magnitude
	 */

	float calculateMagnitude() const;
	float calculateMagnitudeS() const;

	vec3 normalized() const;

	void normalize();

	void negate();

	float dot(const vec3& v2) const;

	/**
	* Makes a copy of this vector.
	*
	* @return The copy of this vector
	*/
	vec3 getCopy() const;

	vec4 toHomogeneous() const;

	vec4 toVec4() const;

	bool operator==(const vec3& v2) const;

	vec3 operator+(const vec3& v2) const;

	vec3 operator-(const vec3& v2) const;

	vec3 operator-() const;

	void operator+=(const vec3& v2);

	void operator-=(const vec3& v2);

	vec3 operator*(const vec3& v2) const;

	vec3 operator*(float f) const;

	void operator*=(float f);

	void operator*=(const vec3& v2);

	vec3 operator/(const vec3& v2) const;

	vec3 operator/(float f) const;

	void operator/=(float f);

	void operator/=(const vec3& v2);

	vec3* operator()(const vec3& v2);

	static vec3 getCrossProduct(vec3 v1, vec3 v2);
};

#endif