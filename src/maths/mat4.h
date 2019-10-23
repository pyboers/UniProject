#pragma once
#ifndef __MAT4_H
#define __MAT4_H

#include "vec4.h"
#include "vec3.h"
#include "quat.h"

class mat4 {
protected:
	float data[16];

public:
	mat4();

	/**
	 * sets this matrix to the identity matrix.
	 *
	 * @return this matrix
	 */
	mat4* initIdentity();

	/**
	 * sets this matrix to a translation matrix.
	 *
	 * @param x x pos
	 * @param y y pos
	 * @param z z pos
	 * @return this matrix
	 */
	mat4* initTranslation(float x, float y, float z);

	mat4* initTranslation(const vec3 &pos);

	/**
	 * initializes a z axis rotation (top down rotation).
	 *
	 * @param z z rotation
	 * @return this matrix
	 */
	mat4* initRotation(float z);

	/**
	 * initialize a full rotation matrix.
	 *
	 * @param x x rotation
	 * @param y y rotation
	 * @param z z rotation
	 * @return this matrix
	 */
	mat4* initRotation(float x, float y, float z);

	/**
	 * initialize a full rotation matrix.
	 *
	 * @param rot the quaternion representing the rotation
	 * @return this matrix
	 */
	mat4* initRotation(const quat &rot);

	/**
	 * Initializes this matrix as a rotation matrix from a basis.
	 *
	 * @param forward forward vector
	 * @param up      up vector
	 * @return this matrix
	 */
	mat4* initRotation(const vec3 &forward, const vec3 &up);

	/**
	 * Initializes this matrix to a rotation matrix from a basis.
	 *
	 * @param forward forward vector
	 * @param up      up vector
	 * @param right   right vector
	 * @return this matrix
	 */
	mat4* initRotation(const vec3 &forward, const vec3 &up, const vec3 &right);

	mat4* initLookAt(const vec3 &forward, const vec3 &up, const vec3 &pos);

	/**
	 * Initializes this matrix as a scale matrix.
	 *
	 * @param x x scale
	 * @param y y scale
	 * @param z z scale
	 * @return this matrix
	 */
	mat4* initScale(float x, float y, float z);

	mat4* initScale(const vec3 &scale);

	/**
	 * Initialises a perspective projection matrix.
	 *
	 * @param fov         fovY
	 * @param aspectRatio aspect ratio
	 * @param zNear       near plane
	 * @param zFar        far plane
	 * @return this matrix
	 */
	mat4* initPerspective(float fov, float aspectRatio, float zNear, float zFar);

	/**
	 * Initialises this matrix as an orthogonal projection matrix.
	 *
	 * @param left   left plane
	 * @param right  right plane
	 * @param bottom bottom plane
	 * @param top    top plane
	 * @param near   near plane
	 * @param far    far plane
	 * @return this matrix
	 */
	mat4* initOrtho(float left, float right, float bottom, float top, float near, float far);


	/**
	 * Multiplies the vector and this homogeneously
	 *
	 * @param v the vector we multiply by
	 * @return the multiplied vector
	 */
	vec3 operator*(const vec3 &v) const;

	/**
	 * Multiplies the vector and this homogeneously
	 *
	 * @param v the vector we multiply by
	 * @return the multiplied vector
	 */
	vec4 operator*(const vec4 &v) const;


	/**
	 * performs matrix multiplication by a scalar.
	 *
	 * @param scalar scale factor
	 * @return the scaled matrix
	 */
	mat4 operator*(float scalar) const;

	/**
	 * performs unwrapped matrix multiplication by a scalar.
	 *
	 * @param scalar scale factor
	 * @return the scaled matrix
	 */
	void operator*=(float scalar);

	/**
	 * Performs matrix multiplication.
	 *
	 * @param m the matrix tp multiply with
	 * @return the result matrix
	 */
	mat4 operator*(const mat4 &m) const;

	/**
	 * Performs matrix multiplication. Keep in mind this still is in the format This*M.
	 * So we are transforming m by this matrix and then putting the result in this matrix. Not m.
	 *
	 * @param m the matrix tp multiply with
	 */
	void operator*=(const mat4 &m);

	float *getData() const;

	float get(int r, int c) const;

	void setData(const float data[]);

	void set(int r, int c, float value);

	/**
	 * gets the transposed version of this matrix.
	 *
	 * @return this matrix transposed
	 */
	mat4 transposed() const;

	/**
	 * transposes this matrix.
	 */
	void transpose();

	float determinant() const;

	mat4 inverse() const;

	void invert();
};

#endif