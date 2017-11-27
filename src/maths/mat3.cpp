#include "mat3.h"
#include <memory.h>

mat3::mat3()
{
	memset(data, 0, 9 * sizeof(float));
}

mat3* mat3::initIdentity() {
	//Top row
	data[0] = 1;
	data[1] = 0;
	data[2] = 0;
	//Middle
	data[3] = 0;
	data[4] = 1;
	data[5] = 0;
	//Bottom
	data[6] = 0;
	data[7] = 0;
	data[8] = 1;
	return this;
}

mat3* mat3::initTranslation(float x, float y) {
	//Top row
	data[0] = 1;
	data[1] = 0;
	data[2] = x;
	//Middle
	data[3] = 0;
	data[4] = 1;
	data[5] = y;
	//Bottom
	data[6] = 0;
	data[7] = 0;
	data[8] = 1;
	return this;
}

mat3* mat3::initTranslation(const vec2 &pos) {
	this->initTranslation(pos.getX(), pos.getY());
	return this;
}

mat3* mat3::initRotation(float z) {
	z = degreesToRadians_F(z);
	float c = cosf(z);
	float s = sinf(z);
	//Top row
	data[0] = c;
	data[1] = -s;
	data[2] = 0;
	//Middle
	data[3] = s;
	data[4] = c;
	data[5] = 0;
	//Bottom
	data[6] = 0;
	data[7] = 0;
	data[8] = 1;
	return this;
}

mat3* mat3::initRotation(float x, float y, float z) {
	float cosA = cosf(x);
	float cosB = cosf(y);
	float cosC = cosf(z);

	float sinA = sinf(x);
	float sinB = sinf(y);
	float sinC = sinf(z);

	//Top row
	data[0] = cosB * cosC;
	data[1] = -cosB * sinC;
	data[2] = sinB;
	//Middle
	data[3] = (sinA * sinB * cosC) + (cosA * sinC);
	data[4] = (-sinA * sinB * sinC) + (cosA * cosC);
	data[5] = -sinA * cosB;
	//Bottom
	data[6] = (-cosA * sinB * cosC) + (sinA * sinC);
	data[7] = (cosA * sinB * sinC) + (sinA * cosC);
	data[8] = cosA * cosB;
	return this;
}

mat3* mat3::initScale(float x, float y) {
	//Top
	data[0] = x;
	data[1] = 0;
	data[2] = 0;
	//Middle
	data[3] = 0;
	data[4] = y;
	data[5] = 0;
	//Bottom
	data[6] = 0;
	data[7] = 0;
	data[8] = 1;
	return this;
}

mat3* mat3::initOrtho(float left, float right, float bottom, float top) {
	float rl = right - left;
	float tb = top - bottom;
	//Top
	data[0] = 2 / (rl);
	data[1] = 0;
	data[2] = -(right + left) / (rl);
	//Middle
	data[3] = 0;
	data[4] = 2 / (tb);
	data[5] = -(top + bottom) / (tb);
	//Bottom
	data[6] = 0;
	data[7] = 0;
	data[8] = 1;
	return this;
}

mat3 mat3::operator*(float scalar) const {
	mat3 m = mat3();
	m.data[0] = data[0] * scalar;
	m.data[1] = data[1] * scalar;
	m.data[2] = data[2] * scalar;
	m.data[3] = data[3] * scalar;
	m.data[4] = data[4] * scalar;
	m.data[5] = data[5] * scalar;
	m.data[6] = data[6] * scalar;
	m.data[7] = data[7] * scalar;
	m.data[8] = data[8] * scalar;
	return m;
}

void mat3::operator*=(float scalar) {
	data[0] *= scalar;
	data[1] *= scalar;
	data[2] *= scalar;
	data[3] *= scalar;
	data[4] *= scalar;
	data[5] *= scalar;
	data[6] *= scalar;
	data[7] *= scalar;
	data[8] *= scalar;
}

mat3 mat3::operator*(const mat3 &m) const {
	mat3 m2 = mat3();
	//Top
	m2.data[0] = (data[0] * m.data[0]) + (data[1] * m.data[3]) + (data[2] * m.data[6]);
	m2.data[1] = (data[0] * m.data[1]) + (data[1] * m.data[4]) + (data[2] * m.data[7]);
	m2.data[2] = (data[0] * m.data[2]) + (data[1] * m.data[5]) + (data[2] * m.data[8]);
	//Middle
	m2.data[3] = (data[3] * m.data[0]) + (data[4] * m.data[3]) + (data[5] * m.data[6]);
	m2.data[4] = (data[3] * m.data[1]) + (data[4] * m.data[4]) + (data[5] * m.data[7]);
	m2.data[5] = (data[3] * m.data[2]) + (data[4] * m.data[5]) + (data[5] * m.data[8]);
	//Bottom
	m2.data[6] = (data[6] * m.data[0]) + (data[7] * m.data[3]) + (data[8] * m.data[6]);
	m2.data[7] = (data[6] * m.data[1]) + (data[7] * m.data[4]) + (data[8] * m.data[7]);
	m2.data[8] = (data[6] * m.data[2]) + (data[7] * m.data[5]) + (data[8] * m.data[8]);
	return m2;
}

void mat3::operator*=(const mat3 &m) {
	float mdata[9];
	//Top
	mdata[0] = (data[0] * m.data[0]) + (data[1] * m.data[3]) + (data[2] * m.data[6]);
	mdata[1] = (data[0] * m.data[1]) + (data[1] * m.data[4]) + (data[2] * m.data[7]);
	mdata[2] = (data[0] * m.data[2]) + (data[1] * m.data[5]) + (data[2] * m.data[8]);
	//Middle
	mdata[3] = (data[3] * m.data[0]) + (data[4] * m.data[3]) + (data[5] * m.data[6]);
	mdata[4] = (data[3] * m.data[1]) + (data[4] * m.data[4]) + (data[5] * m.data[7]);
	mdata[5] = (data[3] * m.data[2]) + (data[4] * m.data[5]) + (data[5] * m.data[8]);
	//Bottom
	mdata[6] = (data[6] * m.data[0]) + (data[7] * m.data[3]) + (data[8] * m.data[6]);
	mdata[7] = (data[6] * m.data[1]) + (data[7] * m.data[4]) + (data[8] * m.data[7]);
	mdata[8] = (data[6] * m.data[2]) + (data[7] * m.data[5]) + (data[8] * m.data[8]);
	this->setData(mdata);
}

vec2 mat3::operator*(const vec2 v) const {
	return vec2(
			(v.getX() * data[0]) + (v.getY() * data[1]) + data[2],
			(v.getX() * data[3]) + (v.getY() * data[4]) + data[5]);
}

vec3 mat3::operator*(const vec3 &v) const {
	return vec3(
			(v.getX() * data[0]) + (v.getY() * data[1]) + (v.getZ() * data[2]),
			(v.getX() * data[3]) + (v.getY() * data[4]) + (v.getZ() * data[5]),
			(v.getX() * data[6]) + (v.getY() * data[7]) + (v.getZ() * data[8])
	);
}

float* mat3::getData() const {
	float *res = new float[9];

	memcpy(res, data, 9 * sizeof(float));
	return res;
}

float mat3::get(int r, int c) const {
	return data[r * 3 + c];
}

void mat3::setData(const float data[]) {
	memcpy(this->data, data, 9 * sizeof(float));
}

void mat3::set(int x, int y, float value) {
	data[x * 3 + y] = value;
}

mat3 mat3::transposed() const {
	mat3 ret = mat3();
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			ret.data[i * 3 + j] = data[j * 3 + i];
		}
	}
	return ret;
}

void mat3::transpose() {
	float tr[9];
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			tr[i * 3 + j] = data[j * 3 + i];
		}
	}
	this->setData(tr);
}

float mat3::determinant() const {
	float a11 = data[0];
	float a12 = data[1];
	float a13 = data[2];
	float a21 = data[3];
	float a22 = data[4];
	float a23 = data[5];
	float a31 = data[6];
	float a32 = data[7];
	float a33 = data[8];

	return (a11 * a22 * a33 + a21 * a32 * a13
			+ a31 * a12 * a23 - a11 * a32 * a23
			- a31 * a22 * a13 - a21 * a12 * a33);
}

mat3 mat3::inverse() const {
	float a11 = data[0];
	float a12 = data[1];
	float a13 = data[2];
	float a21 = data[3];
	float a22 = data[4];
	float a23 = data[5];
	float a31 = data[6];
	float a32 = data[7];
	float a33 = data[8];
	float invdet = (a11 * a22 * a33 + a21 * a32 * a13
					+ a31 * a12 * a23 - a11 * a32 * a23
					- a31 * a22 * a13 - a21 * a12 * a33);
	if (invdet == 0) {
		return mat3();
	}
	invdet = 1 / invdet;
	mat3 invmat = mat3();
	float ndata[]{a22 * a33 - a23 * a32, a13 * a32 - a12 * a33, a12 * a23 - a13 * a22,
				  a23 * a31 - a21 * a33, a11 * a33 - a13 * a31, a13 * a21 - a11 * a23,
				  a21 * a32 - a22 * a31, a12 * a31 - a11 * a32, a11 * a22 - a12 * a21};
	invmat.setData(ndata);
	invmat *= invdet;
	return invmat;
}

void mat3::invert() {
	float a11 = data[0];
	float a12 = data[1];
	float a13 = data[2];
	float a21 = data[3];
	float a22 = data[4];
	float a23 = data[5];
	float a31 = data[6];
	float a32 = data[7];
	float a33 = data[8];
	float invdet = (a11 * a22 * a33 + a21 * a32 * a13
					+ a31 * a12 * a23 - a11 * a32 * a23
					- a31 * a22 * a13 - a21 * a12 * a33);
	if (invdet == 0) {
		return;
	}
	invdet = 1 / invdet;
	float ndata[]{a22 * a33 - a23 * a32, a13 * a32 - a12 * a33, a12 * a23 - a13 * a22,
				  a23 * a31 - a21 * a33, a11 * a33 - a13 * a31, a13 * a21 - a11 * a23,
				  a21 * a32 - a22 * a31, a12 * a31 - a11 * a32, a11 * a22 - a12 * a21};
	setData(ndata);
	*this *= (invdet);
}
