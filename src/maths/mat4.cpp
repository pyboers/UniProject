#include "mat4.h"
#include "memory.h" 

mat4::mat4()
{
	memset(data, 0, 16*sizeof(float));
}

mat4* mat4::initIdentity()
{
	data[0] = 1;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	data[5] = 1;
	data[6] = 0;
	data[7] = 0;
	data[8] = 0;
	data[9] = 0;
	data[10] = 1;
	data[11] = 0;
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
	return this;
}

mat4* mat4::initTranslation(float x, float y, float z)
{
	data[0] = 1;
	data[1] = 0;
	data[2] = 0;
	data[3] = x;
	data[4] = 0;
	data[5] = 1;
	data[6] = 0;
	data[7] = y;
	data[8] = 0;
	data[9] = 0;
	data[10] = 1;
	data[11] = z;
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
	return this;
}

mat4* mat4::initTranslation(const vec3& pos)
{
	data[0] = 1;
	data[1] = 0;
	data[2] = 0;
	data[3] = pos.getX();
	data[4] = 0;
	data[5] = 1;
	data[6] = 0;
	data[7] = pos.getY();
	data[8] = 0;
	data[9] = 0;
	data[10] = 1;
	data[11] = pos.getZ();
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
	return this;
}

mat4* mat4::initRotation(float z)
{
	z = degreesToRadians_F(z);
	float c = cosf(z);
	float s = sinf(z);

	data[0] = c;
	data[1] = -s;
	data[2] = 0;
	data[3] = 0;
	data[4] = s;
	data[5] = c;
	data[6] = 0;
	data[7] = 0;
	data[8] = 0;
	data[9] = 0;
	data[10] = 1;
	data[11] = 0;
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
	return this;
}

mat4* mat4::initRotation(float x, float y, float z)
{
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
	data[3] = 0;
	//Middle
	data[4] = (sinA * sinB * cosC) + (cosA * sinC);
	data[5] = (-sinA * sinB * sinC) + (cosA * cosC);
	data[6] = -sinA * cosB;
	data[7] = 0;
	//Middle2
	data[8] = (-cosA * sinB * cosC) + (sinA * sinC);
	data[9] = (cosA * sinB * sinC) + (sinA * cosC);
	data[10] = cosA * cosB;
	data[11] = 0;
	//Bottom
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
	return this;
}

mat4 *mat4::initRotation(const quat &rot) {
	vec3 euler = rot.toEulerAngles();
	return initRotation(euler.getX(), euler.getY(), euler.getZ());
}

mat4* mat4::initRotation(const vec3& forward, const vec3& up)
{
	vec3 f = forward.normalized();

	vec3 r = up.normalized();
	r = vec3::getCrossProduct(r, f);

	return initRotation(f, up, r);
}

mat4* mat4::initRotation(const vec3& forward, const vec3& up, const vec3& right)
{
	data[0] = right.getX();
	data[1] = right.getY();
	data[2] = right.getZ();
	data[3] = 0;
	data[4] = up.getX();
	data[5] = up.getY();
	data[6] = up.getZ();
	data[7] = 0;
	data[8] = forward.getX();
	data[9] = forward.getY();
	data[10] = forward.getZ();
	data[11] = 0;
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
	return this;
}

mat4* mat4::initLookAt(const vec3& forward, const vec3& up, const vec3& pos)
{
	initRotation(forward, up);
	data[3] = pos.getX();
	data[7] = pos.getY();
	data[11] = pos.getZ();
	return this;
}

mat4* mat4::initScale(float x, float y, float z)
{
	data[0] = x;
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	data[5] = y;
	data[6] = 0;
	data[7] = 0;
	data[8] = 0;
	data[9] = 0;
	data[10] = z;
	data[11] = 0;
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
	return this;
}

mat4* mat4::initScale(const vec3& scale)
{
	data[0] = scale.getX();
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	data[5] = scale.getY();
	data[6] = 0;
	data[7] = 0;
	data[8] = 0;
	data[9] = 0;
	data[10] = scale.getZ();
	data[11] = 0;
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
	return this;
}

mat4* mat4::initPerspective(float fov, float aspectRatio, float zNear, float zFar)
{
	float tanHalfFOV = tanf(degreesToRadians_F(fov) / 2);
	float zRange = zNear - zFar;

	data[0] = 1.0f / (tanHalfFOV * aspectRatio);
	data[1] = 0;
	data[2] = 0;
	data[3] = 0;
	data[4] = 0;
	data[5] = 1.0f / tanHalfFOV;
	data[6] = 0;
	data[7] = 0;
	data[8] = 0;
	data[9] = 0;
	data[10] = ((zFar + zNear) / zRange);
	data[11] = 2 * zFar * zNear / zRange;
	data[12] = 0;
	data[13] = 0;
	data[14] = -1;
	data[15] = 0;
	return this;
}

mat4* mat4::initOrtho(float left, float right, float bottom, float top, float near, float far)
{
	float width = right - left;
	float height = top - bottom;
	float depth = far - near;

	data[0] = 2 / width;
	data[1] = 0;
	data[2] = 0;
	data[3] = -(right + left) / width;
	data[4] = 0;
	data[5] = 2 / height;
	data[6] = 0;
	data[7] = -(top + bottom) / height;
	data[8] = 0;
	data[9] = 0;
	data[10] = -2 / depth;
	data[11] = -(far + near) / depth;
	data[12] = 0;
	data[13] = 0;
	data[14] = 0;
	data[15] = 1;
	return this;
}

vec3 mat4::operator*(const vec3& v) const
{
	return vec3((v.getX() * data[0]) + (v.getY() * data[1]) + (v.getZ() * data[2]) + data[3],
	            (v.getX() * data[4]) + (v.getY() * data[5]) + (v.getZ() * data[6]) + data[7],
	            (v.getX() * data[8]) + (v.getY() * data[9]) + (v.getZ() * data[10]) + data[11]);
}

vec4 mat4::operator*(const vec4& v) const
{
	return vec4((v.getX() * data[0]) + (v.getY() * data[1]) + (v.getZ() * data[2]) + (v.getW() * data[3]),
	            (v.getX() * data[4]) + (v.getY() * data[5]) + (v.getZ() * data[6]) + (v.getW() * data[7]),
	            (v.getX() * data[8]) + (v.getY() * data[9]) + (v.getZ() * data[10]) + (v.getW() * data[11]),
	            (v.getX() * data[12]) + (v.getY() * data[13]) + (v.getZ() * data[14]) + (v.getW() * data[15]));
}

mat4 mat4::operator*(float scalar) const
{
	mat4 m = mat4();
	m.data[0] = data[0] * scalar;
	m.data[1] = data[1] * scalar;
	m.data[2] = data[2] * scalar;
	m.data[3] = data[3] * scalar;
	m.data[4] = data[4] * scalar;
	m.data[5] = data[5] * scalar;
	m.data[6] = data[6] * scalar;
	m.data[7] = data[7] * scalar;
	m.data[8] = data[8] * scalar;
	m.data[9] = data[9] * scalar;
	m.data[10] = data[10] * scalar;
	m.data[11] = data[11] * scalar;
	m.data[12] = data[12] * scalar;
	m.data[13] = data[13] * scalar;
	m.data[14] = data[14] * scalar;
	m.data[15] = data[15] * scalar;
	return m;
}

void mat4::operator*=(float scalar)
{
	data[0] *= scalar;
	data[1] *= scalar;
	data[2] *= scalar;
	data[3] *= scalar;
	data[4] *= scalar;
	data[5] *= scalar;
	data[6] *= scalar;
	data[7] *= scalar;
	data[8] *= scalar;
	data[9] *= scalar;
	data[10] *= scalar;
	data[11] *= scalar;
	data[12] *= scalar;
	data[13] *= scalar;
	data[14] *= scalar;
	data[15] *= scalar;
}

mat4 mat4::operator*(const mat4& m) const
{
	mat4 m2 = mat4();
	//
	m2.data[0] = (data[0] * m.data[0]) + (data[1] * m.data[4]) + (data[2] * m.data[8]) + (data[3] * m.data[12]);
	m2.data[1] = (data[0] * m.data[1]) + (data[1] * m.data[5]) + (data[2] * m.data[9]) + (data[3] * m.data[13]);
	m2.data[2] = (data[0] * m.data[2]) + (data[1] * m.data[6]) + (data[2] * m.data[10]) + (data[3] * m.data[14]);
	m2.data[3] = (data[0] * m.data[3]) + (data[1] * m.data[7]) + (data[2] * m.data[11]) + (data[3] * m.data[15]);
	//
	m2.data[4] = (data[4] * m.data[0]) + (data[5] * m.data[4]) + (data[6] * m.data[8]) + (data[7] * m.data[12]);
	m2.data[5] = (data[4] * m.data[1]) + (data[5] * m.data[5]) + (data[6] * m.data[9]) + (data[7] * m.data[13]);
	m2.data[6] = (data[4] * m.data[2]) + (data[5] * m.data[6]) + (data[6] * m.data[10]) + (data[7] * m.data[14]);
	m2.data[7] = (data[4] * m.data[3]) + (data[5] * m.data[7]) + (data[6] * m.data[11]) + (data[7] * m.data[15]);
	//
	m2.data[8] = (data[8] * m.data[0]) + (data[9] * m.data[4]) + (data[10] * m.data[8]) + (data[11] * m.data[12]);
	m2.data[9] = (data[8] * m.data[1]) + (data[9] * m.data[5]) + (data[10] * m.data[9]) + (data[11] * m.data[13]);
	m2.data[10] = (data[8] * m.data[2]) + (data[9] * m.data[6]) + (data[10] * m.data[10]) + (data[11] * m.data[14]);
	m2.data[11] = (data[8] * m.data[3]) + (data[9] * m.data[7]) + (data[10] * m.data[11]) + (data[11] * m.data[15]);
	//
	m2.data[12] = (data[12] * m.data[0]) + (data[13] * m.data[4]) + (data[14] * m.data[8]) + (data[15] * m.data[12]);
	m2.data[13] = (data[12] * m.data[1]) + (data[13] * m.data[5]) + (data[14] * m.data[9]) + (data[15] * m.data[13]);
	m2.data[14] = (data[12] * m.data[2]) + (data[13] * m.data[6]) + (data[14] * m.data[10]) + (data[15] * m.data[14]);
	m2.data[15] = (data[12] * m.data[3]) + (data[13] * m.data[7]) + (data[14] * m.data[11]) + (data[15] * m.data[15]);
	return m2;
}

void mat4::operator*=(const mat4& m)
{
	float mdata[16];
	//
	mdata[0] = (data[0] * m.data[0]) + (data[1] * m.data[4]) + (data[2] * m.data[8]) + (data[3] * m.data[12]);
	mdata[1] = (data[0] * m.data[1]) + (data[1] * m.data[5]) + (data[2] * m.data[9]) + (data[3] * m.data[13]);
	mdata[2] = (data[0] * m.data[2]) + (data[1] * m.data[6]) + (data[2] * m.data[10]) + (data[3] * m.data[14]);
	mdata[3] = (data[0] * m.data[3]) + (data[1] * m.data[7]) + (data[2] * m.data[11]) + (data[3] * m.data[15]);
	//
	mdata[4] = (data[4] * m.data[0]) + (data[5] * m.data[4]) + (data[6] * m.data[8]) + (data[7] * m.data[12]);
	mdata[5] = (data[4] * m.data[1]) + (data[5] * m.data[5]) + (data[6] * m.data[9]) + (data[7] * m.data[13]);
	mdata[6] = (data[4] * m.data[2]) + (data[5] * m.data[6]) + (data[6] * m.data[10]) + (data[7] * m.data[14]);
	mdata[7] = (data[4] * m.data[3]) + (data[5] * m.data[7]) + (data[6] * m.data[11]) + (data[7] * m.data[15]);
	//
	mdata[8] = (data[8] * m.data[0]) + (data[9] * m.data[4]) + (data[10] * m.data[8]) + (data[11] * m.data[12]);
	mdata[9] = (data[8] * m.data[1]) + (data[9] * m.data[5]) + (data[10] * m.data[9]) + (data[11] * m.data[13]);
	mdata[10] = (data[8] * m.data[2]) + (data[9] * m.data[6]) + (data[10] * m.data[10]) + (data[11] * m.data[14]);
	mdata[11] = (data[8] * m.data[3]) + (data[9] * m.data[7]) + (data[10] * m.data[11]) + (data[11] * m.data[15]);
	//
	mdata[12] = (data[12] * m.data[0]) + (data[13] * m.data[4]) + (data[14] * m.data[8]) + (data[15] * m.data[12]);
	mdata[13] = (data[12] * m.data[1]) + (data[13] * m.data[5]) + (data[14] * m.data[9]) + (data[15] * m.data[13]);
	mdata[14] = (data[12] * m.data[2]) + (data[13] * m.data[6]) + (data[14] * m.data[10]) + (data[15] * m.data[14]);
	mdata[15] = (data[12] * m.data[3]) + (data[13] * m.data[7]) + (data[14] * m.data[11]) + (data[15] * m.data[15]);
	this->setData(mdata);
}

float* mat4::getData() const
{
	float* res = new float[16];

	memcpy(res, data, 16 * sizeof(float));
	return res;
}

float mat4::get(int r, int c) const
{
	return data[r + c * 4];
}

void mat4::setData(const float data[])
{
	memcpy(this->data, data, 16 * sizeof(float));
}

void mat4::set(int r, int c, float value)
{
	data[r + 4 * c] = value;
}

mat4 mat4::transposed() const
{
	mat4 ret = mat4();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			ret.data[i * 4 + j] = data[j * 4 + i];
		}
	}
	return ret;
}

void mat4::transpose()
{
	float tr[16];
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			tr[i * 4 + j] = data[j * 4 + i];
		}
	}
	this->setData(tr);
}

float mat4::determinant() const
{
	float a11 = data[0];
	float a12 = data[1];
	float a13 = data[2];
	float a14 = data[3];
	float a21 = data[4];
	float a22 = data[5];
	float a23 = data[6];
	float a24 = data[7];
	float a31 = data[8];
	float a32 = data[9];
	float a33 = data[10];
	float a34 = data[11];
	float a41 = data[12];
	float a42 = data[13];
	float a43 = data[14];
	float a44 = data[15];
	return a11 * a22 * a33 * a44 + a11 * a23 * a34 * a42 + a11 * a24 * a32 * a43
		+ a12 * a21 * a34 * a43 + a12 * a23 * a31 * a44 + a12 * a24 * a33 * a41
		+ a13 * a21 * a32 * a44 + a13 * a22 * a34 * a41 + a13 * a24 * a31 * a42
		+ a14 * a21 * a33 * a42 + a14 * a22 * a31 * a43 + a14 * a23 * a32 * a41
		- a11 * a22 * a34 * a43 - a11 * a23 * a32 * a44 - a11 * a24 * a33 * a42
		- a12 * a21 * a33 * a44 - a12 * a23 * a34 * a41 - a12 * a24 * a31 * a43
		- a13 * a21 * a34 * a42 - a13 * a22 * a31 * a44 - a13 * a24 * a32 * a41
		- a14 * a21 * a32 * a43 - a14 * a22 * a33 * a41 - a14 * a23 * a31 * a42;
}

mat4 mat4::inverse() const
{
	float a11 = data[0];
	float a12 = data[1];
	float a13 = data[2];
	float a14 = data[3];
	float a21 = data[4];
	float a22 = data[5];
	float a23 = data[6];
	float a24 = data[7];
	float a31 = data[8];
	float a32 = data[9];
	float a33 = data[10];
	float a34 = data[11];
	float a41 = data[12];
	float a42 = data[13];
	float a43 = data[14];
	float a44 = data[15];
	float invdet = a11 * a22 * a33 * a44 + a11 * a23 * a34 * a42 + a11 * a24 * a32 * a43
		+ a12 * a21 * a34 * a43 + a12 * a23 * a31 * a44 + a12 * a24 * a33 * a41
		+ a13 * a21 * a32 * a44 + a13 * a22 * a34 * a41 + a13 * a24 * a31 * a42
		+ a14 * a21 * a33 * a42 + a14 * a22 * a31 * a43 + a14 * a23 * a32 * a41
		- a11 * a22 * a34 * a43 - a11 * a23 * a32 * a44 - a11 * a24 * a33 * a42
		- a12 * a21 * a33 * a44 - a12 * a23 * a34 * a41 - a12 * a24 * a31 * a43
		- a13 * a21 * a34 * a42 - a13 * a22 * a31 * a44 - a13 * a24 * a32 * a41
		- a14 * a21 * a32 * a43 - a14 * a22 * a33 * a41 - a14 * a23 * a31 * a42;
	if (invdet == 0)
	{
		return mat4();
	}
	invdet = 1 / invdet;
	float mdata[]{
		a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 - a22 * a34 * a43 - a23 * a32 * a44 - a24 * a33 * a42,
		a12 * a34 * a43 + a13 * a32 * a44 + a14 * a33 * a42 - a12 * a33 * a44 - a13 * a34 * a42 - a14 * a32 * a43,
		a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 - a12 * a24 * a43 - a13 * a22 * a44 - a14 * a23 * a42,
		a12 * a24 * a33 + a13 * a22 * a34 + a14 * a23 * a32 - a12 * a23 * a34 - a13 * a24 * a32 - a14 * a22 * a33,

		a21 * a34 * a43 + a23 * a31 * a44 + a24 * a33 * a41 - a21 * a33 * a44 - a23 * a34 * a41 - a24 * a31 * a43,
		a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 - a11 * a34 * a43 - a13 * a31 * a44 - a14 * a33 * a41,
		a11 * a24 * a43 + a13 * a21 * a44 + a14 * a23 * a41 - a11 * a23 * a44 - a13 * a24 * a41 - a14 * a21 * a43,
		a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 - a11 * a24 * a33 - a13 * a21 * a34 - a14 * a23 * a31,

		a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 - a21 * a34 * a42 - a22 * a31 * a44 - a24 * a32 * a41,
		a11 * a34 * a42 + a12 * a31 * a44 + a14 * a32 * a41 - a11 * a32 * a44 - a12 * a34 * a41 - a14 * a31 * a42,
		a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 - a11 * a24 * a42 - a12 * a21 * a44 - a14 * a22 * a41,
		a11 * a24 * a32 + a12 * a21 * a34 + a14 * a22 * a31 - a11 * a22 * a34 - a12 * a24 * a31 - a14 * a21 * a32,

		a21 * a33 * a42 + a22 * a31 * a43 + a23 * a32 * a41 - a21 * a32 * a43 - a22 * a33 * a41 - a23 * a31 * a42,
		a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 - a11 * a33 * a42 - a12 * a31 * a43 - a13 * a32 * a41,
		a11 * a23 * a42 + a12 * a21 * a43 + a13 * a22 * a41 - a11 * a22 * a43 - a12 * a23 * a41 - a13 * a21 * a42,
		a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a11 * a23 * a32 - a12 * a21 * a33 - a13 * a22 * a31
	};
	mat4 invmat = mat4();
	invmat.setData(mdata);
	invmat *= (invdet);
	return invmat;
}

void mat4::invert()
{
	float a11 = data[0];
	float a12 = data[1];
	float a13 = data[2];
	float a14 = data[3];
	float a21 = data[4];
	float a22 = data[5];
	float a23 = data[6];
	float a24 = data[7];
	float a31 = data[8];
	float a32 = data[9];
	float a33 = data[10];
	float a34 = data[11];
	float a41 = data[12];
	float a42 = data[13];
	float a43 = data[14];
	float a44 = data[15];
	float invdet = a11 * a22 * a33 * a44 + a11 * a23 * a34 * a42 + a11 * a24 * a32 * a43
		+ a12 * a21 * a34 * a43 + a12 * a23 * a31 * a44 + a12 * a24 * a33 * a41
		+ a13 * a21 * a32 * a44 + a13 * a22 * a34 * a41 + a13 * a24 * a31 * a42
		+ a14 * a21 * a33 * a42 + a14 * a22 * a31 * a43 + a14 * a23 * a32 * a41
		- a11 * a22 * a34 * a43 - a11 * a23 * a32 * a44 - a11 * a24 * a33 * a42
		- a12 * a21 * a33 * a44 - a12 * a23 * a34 * a41 - a12 * a24 * a31 * a43
		- a13 * a21 * a34 * a42 - a13 * a22 * a31 * a44 - a13 * a24 * a32 * a41
		- a14 * a21 * a32 * a43 - a14 * a22 * a33 * a41 - a14 * a23 * a31 * a42;
	if (invdet == 0)
	{
		return;
	}
	invdet = 1 / invdet;
	float mdata[]{
		a22 * a33 * a44 + a23 * a34 * a42 + a24 * a32 * a43 - a22 * a34 * a43 - a23 * a32 * a44 - a24 * a33 * a42,
		a12 * a34 * a43 + a13 * a32 * a44 + a14 * a33 * a42 - a12 * a33 * a44 - a13 * a34 * a42 - a14 * a32 * a43,
		a12 * a23 * a44 + a13 * a24 * a42 + a14 * a22 * a43 - a12 * a24 * a43 - a13 * a22 * a44 - a14 * a23 * a42,
		a12 * a24 * a33 + a13 * a22 * a34 + a14 * a23 * a32 - a12 * a23 * a34 - a13 * a24 * a32 - a14 * a22 * a33,

		a21 * a34 * a43 + a23 * a31 * a44 + a24 * a33 * a41 - a21 * a33 * a44 - a23 * a34 * a41 - a24 * a31 * a43,
		a11 * a33 * a44 + a13 * a34 * a41 + a14 * a31 * a43 - a11 * a34 * a43 - a13 * a31 * a44 - a14 * a33 * a41,
		a11 * a24 * a43 + a13 * a21 * a44 + a14 * a23 * a41 - a11 * a23 * a44 - a13 * a24 * a41 - a14 * a21 * a43,
		a11 * a23 * a34 + a13 * a24 * a31 + a14 * a21 * a33 - a11 * a24 * a33 - a13 * a21 * a34 - a14 * a23 * a31,

		a21 * a32 * a44 + a22 * a34 * a41 + a24 * a31 * a42 - a21 * a34 * a42 - a22 * a31 * a44 - a24 * a32 * a41,
		a11 * a34 * a42 + a12 * a31 * a44 + a14 * a32 * a41 - a11 * a32 * a44 - a12 * a34 * a41 - a14 * a31 * a42,
		a11 * a22 * a44 + a12 * a24 * a41 + a14 * a21 * a42 - a11 * a24 * a42 - a12 * a21 * a44 - a14 * a22 * a41,
		a11 * a24 * a32 + a12 * a21 * a34 + a14 * a22 * a31 - a11 * a22 * a34 - a12 * a24 * a31 - a14 * a21 * a32,

		a21 * a33 * a42 + a22 * a31 * a43 + a23 * a32 * a41 - a21 * a32 * a43 - a22 * a33 * a41 - a23 * a31 * a42,
		a11 * a32 * a43 + a12 * a33 * a41 + a13 * a31 * a42 - a11 * a33 * a42 - a12 * a31 * a43 - a13 * a32 * a41,
		a11 * a23 * a42 + a12 * a21 * a43 + a13 * a22 * a41 - a11 * a22 * a43 - a12 * a23 * a41 - a13 * a21 * a42,
		a11 * a22 * a33 + a12 * a23 * a31 + a13 * a21 * a32 - a11 * a23 * a32 - a12 * a21 * a33 - a13 * a22 * a31
	};
	setData(mdata);
	*this *= (invdet);
}

