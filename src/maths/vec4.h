#pragma once
#pragma once
#ifndef __VEC4_H
#define __VEC4_H
#include <math.h>
#include "MyMath.h"

class vec4{

protected:
	float x;
	float y;
	float z;
	float w;

public:

	/**
	 * Constructs an origin vector.
	 */
	vec4();

	/**
	 * Construct a vector with x, y, z and w value f.
	 *
	 * @param f the x, y, z and w
	 */
	vec4(float f);

	/**
	 * Constructs a vector with values of another vector.
	 *
	 * @param v vector to copy
	 */
	vec4(const vec4& v);

	/**
	 * Constructs a vector with values x, y, z and w.
	 *
	 * @param x the x value
	 * @param y the y value
	 * @param z the z value
	 * @param w the w value
	 */
	vec4(float x, float y, float z, float w);

	/**
	 * Sets x member to x
	 *
	 * @param x the x value
	 */
	void setX(float x);

	/**
	 * Sets y member to y
	 *
	 * @param y the y value
	 */
	void setY(float y);

	/**
	 * Sets z member to z
	 *
	 * @param z the z value
	 */
	void setZ(float z);

	/**
	 * Sets w member to y
	 *
	 * @param w the w value
	 */
	void setW(float w);

	/**
	 * Sets x, y, z and w
	 *
	 * @param x the x value
	 * @param y the y value
	 * @param z the z value
	 * @param w the w value
	 */
	void set(float x, float y, float z, float w);

	/**
	 * Sets this vec4's members to another vec4's members
	 *
	 * @param v2 other vector
	 */
	void set(const vec4& v2);

	float getX() const;

	float getY() const;

	float getZ() const;

	float getW() const;

	float calculateMagnitudeS() const;
	float calculateMagnitude() const;

	vec4 normalized() const;

	void normalize();

	void negate();

	float dot(const vec4& v2) const;

	/**
	 * Makes a copy of this vector.
	 *
	 * @return The copy of this vector
	 */
	vec4 getCopy() const;

	bool operator==(const vec4& v2) const;

	vec4 operator+(const vec4& v2) const;

	vec4 operator-(const vec4& v2) const;

	vec4 operator-() const;

	void operator+=(const vec4& v2);

	void operator-=(const vec4& v2);

	vec4 operator*(const vec4& v2) const;

	vec4 operator*(float f) const;

	void operator*=(float f);

	void operator*=(const vec4& v2);

	vec4 operator/(const vec4& v2) const;

	vec4 operator/(float f) const;

	void operator/=(float f);

	void operator/=(const vec4& v2);

	vec4 *operator()(const vec4& v2);
};

#endif