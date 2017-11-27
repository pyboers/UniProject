#pragma once
#ifndef __VEC2_H
#define __VEC2_H
#include <math.h>
#include <ostream>
#include "MyMath.h"
#include "vec3.h"
#define nullvec vec2(NAN)

class vec2 {

protected:
	float x;
	float y;

public:
	/**
	 * Constructs an origin vector.
	 */
	vec2();
	/**
	 * Construct a vector with x and y value f.
	 *
	 * @param f both values of the vector
	 */
	vec2(float f);

	/**
	 * Constructs a vector with values of another vector.
	 *
	 * @param v vector to copy
	 */
	vec2(const vec2& v);

	/**
	 * Constructs a vector with values x and y.
	 *
	 * @param x the x value
	 * @param y the y value
	 */
	vec2(float x, float y);

	/**
	 * Sets x member to x.
	 *
	 * @param x the x value
	 */
	void  setX(float x);

	/**
	 * Sets y member to y.
	 *
	 * @param y the y value
	 */
	void setY(float y);

	/**
	 * Sets x and y.
	 *
	 * @param x the x value
	 * @param y the y value
	 */
	void set(float x, float y);

	/**
	 * Sets this vec2's members to another vec2's members.
	 *
	 * @param v
	 */
	void set(const vec2& v);

	float getX() const;

	float getY() const;


	float calculateMagnitudeS() const;

	float calculateMagnitude() const;

	vec2 normalized() const;

    void normalize();

	void negate();

	float dot(const vec2& v2) const;

	/**
	 * Rotates this vector.
	 *
	 * @param degrees The degrees to rotated by
	 */
	void rotate(float degrees);

	/**
	 * Calculates the rotation of this vector.
	 *
	 * @param degrees The degrees to rotated by
	 * @return this rotated by degrees
	 */
	vec2 rotated(float degrees) const;

	/**
	 * Rotates this vector.
	 *
	 * @param radians The degrees in radians to rotated by
	 */
	void rotateR(float radians);

	/**
	 * Calculates the rotation of this vector.
	 *
	 * @param radians The degrees in radians to rotated by
	 * @return this rotated by degrees
	 */
	vec2 rotatedR(float radians) const;

	float getRadians() const;
	/**
	 * Makes a copy of this vector.
	 *
	 * @return The copy of this vector
	 */
	vec2 getCopy() const;

	vec3 toHomogeneous() const;

	vec3 toVec3() const;
	
	bool operator==(const vec2& v2) const;

	vec2 operator+(const vec2& v2) const;

	vec2 operator-(const vec2& v2) const;

	vec2 operator-() const;

	void operator+=(const vec2& v2);

	void operator-=(const vec2& v2);

	vec2 operator*(const vec2& v2) const;

	vec2 operator*(float f) const;

	void operator*=(float f);

	void operator*=(const vec2& v2);

	vec2 operator/(const vec2& v2) const;

	vec2 operator/(float f) const;

	void operator/=(float f);

	void operator/=(const vec2& v2);

	bool operator>(const vec2 &v2);

	bool operator<(const vec2 &v2);

	vec2* operator()(const vec2& v2);

	bool isNull() const;

	static float perpDot(const vec2 &v1, const vec2 &v2);

	/**
	 *
	 * @param v1
	 * @param s scale. Positive is right. Negative is left. 0 is foobar.
	 * @return perp vector
	 */
	static vec2 perp(const vec2 &v1, float s);

};
std::ostream &operator<<(std::ostream &stream, const vec2 &vec);

#endif