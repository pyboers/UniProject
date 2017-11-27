#pragma once
#ifndef __MAT3_H
#define __MAT3_H

#include "vec2.h"

/**
 * Row Major Matrix
 */
class mat3
{
protected:
	float data[9];

public:
	mat3();

	/**
	 * sets this matrix to the identity matrix.
	 *
	 * @return this matrix
	 */
	mat3* initIdentity();

	/**
	 * sets this matrix to a translation matrix.
	 *
	 * @param x x pos
	 * @param y y pos
	 * @return this matrix
	 */
	mat3* initTranslation(float x, float y);

	mat3* initTranslation(const vec2& pos);

	/**
	 * initializes a z axis rotation (top down rotation).
	 *
	 * @param z z rotation
	 * @return this matrix
	 */
	mat3* initRotation(float z);

	mat3* initRotation(float x, float y, float z);


	/**
	 * Initializes this matrix as a scale matrix.
	 *
	 * @param x x scale
	 * @param y y scale
	 * @return this matrix
	 */
	mat3* initScale(float x, float y);

	/**
	 * Initialises this matrix as an orthogonal projection matrix.
	 *
	 * @param left   left plane
	 * @param right  right plane
	 * @param bottom bottom plane
	 * @param top    top plane
	 * @return this matrix
	 */
	mat3* initOrtho(float left, float right, float bottom, float top);


	/**
	 * performs unwrapped matrix multiplication by a scalar.
	 *
	 * @param scalar scale factor
	 * @return the scaled matrix
	 */
	mat3 operator*(float scalar) const;

	/**
	 * performs unwrapped matrix multiplication by a scalar.
	 *
	 * @param scalar scale factor
	 */
	void operator*=(float scalar);

	/**
	 * Performs matrix multiplication.
	 *
	 * @param m the matrix tp multiply with
	 * @return the result matrix
	 */
	mat3 operator*(const mat3& m) const;

	/**
	 * Performs matrix multiplication. Keep in mind this still is in the format This*M.
	 * So we are transforming m by this matrix and then putting the result in this matrix. Not m.
	 *
	 * @param m the matrix tp multiply with
	 */
	void operator*=(const mat3& m);

	/**
	 * Multiplies the vector and this homogeneously
	 *
	 * @param v the vector we multiply by
	 * @return the multiplied vector
	 */
	vec2 operator*(const vec2 v) const;

	/**
	 * Multiplies the vector and this.
	 *
	 * @param v the vector we multiply by
	 * @return the multiplied vector
	 */
	vec3 operator*(const vec3& v) const;

	/**
	 * returns the data of the matrix.
	 *
	 * @return the data
	 */
	float* getData() const;

	float get(int r, int c) const;

	/**
	 * Takes in a 9 float array
	 */
	void setData(const float data[]);

	void set(int x, int y, float value);

	/**
	 * gets the transposed version of this matrix.
	 *
	 * @return this matrix transposed
	 */
	mat3 transposed() const;

	/**
	 * transposes this matrix.
	 */
	void transpose();

	float determinant() const;

	mat3 inverse() const;

	void invert();
};

#endif
