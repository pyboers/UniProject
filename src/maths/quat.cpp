//From IGA_C
#include "quat.h"
#include "mat4.h"
quat::quat() : quat(0, 0, 0, 0) {}

quat::quat(float w, float x, float y, float z) : w(w), x(x), y(y), z(z){}

quat::quat(vec3 axis, float angle)
{
	float sinHalfAngle = sinf(angle / 2);
	x = axis.getX() * sinHalfAngle;
	y = axis.getY() * sinHalfAngle;
	z = axis.getZ() * sinHalfAngle;
	w = cosf(angle / 2);
}

float quat::length() const
{
	return sqrtf(x * x + y * y + z * z + w * w);
}

quat quat::normalized() const
{
	float length = this->length();
	return quat(w / length, x / length, y / length, z / length);
}

quat quat::conjugate() const
{
	return quat(w, -x, -y, -z);
}

quat quat::operator*(float r) const
{
	return quat(w * r, x * r, y * r, z * r);
}

quat quat::operator*(quat r) const
{
	return quat(w * r.w - x * r.x - y * r.y - z * r.z,
				x * r.w + w * r.x + y * r.z - z * r.y,
				y * r.w + w * r.y + z * r.x - x * r.z,
				z * r.w + w * r.z + x * r.y - y * r.x);
}

quat quat::operator*=(quat r) {
	set(w * r.w - x * r.x - y * r.y - z * r.z,
			x * r.w + w * r.x + y * r.z - z * r.y,
			y * r.w + w * r.y + z * r.x - x * r.z,
			z * r.w + w * r.z + x * r.y - y * r.x);
}


quat quat::operator*(vec3 r) const
{
	return quat(-x * r.getX() - y * r.getY() - z * r.getZ(),
				w * r.getX() + y * r.getZ() - z * r.getY(),
				w * r.getY() + z * r.getX() - x * r.getZ(),
				w * r.getZ() + x * r.getY() - y * r.getX());
}

quat quat::operator-(quat r) const
{
	return quat(w - r.w, x - r.x, y - r.y, z - r.z);
}

quat quat::operator+(quat r) const
{
	return quat(w + r.w, x + r.x, y + r.y, z + r.z);
}

vec3 quat::rotatedVec3(const vec3& v2) const
{
	quat conjugate = this->conjugate();

	quat w = ((*this) * v2) * conjugate;

	return vec3(w.getX(), w.getY(), w.getZ());
}

void quat::rotateVec3(vec3& v2) const
{
	quat conjugate = this->conjugate();

	quat w = ((*this) * v2) * conjugate;

	return v2.set(w.getX(), w.getY(), w.getZ());
}

mat4 quat::toRotationMatrix() const{
	vec3 forward = vec3(2.0f * (x * z - w * y), 2.0f * (y * z + w * x), 1.0f - 2.0f * (x * x + y * y));
	vec3 up = vec3(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z * z), 2.0f * (y * z - w * x));
	vec3 right = vec3(1.0f - 2.0f * (y * y + z * z), 2.0f * (x * y - w * z), 2.0f * (x * z + w * y));
	mat4 m = mat4();
	m.initRotation(forward, up, right);
	return m;
}

float quat::dot(quat r) const
{
	return x * r.x + y * r.y + z * r.z + w * r.w;
}

quat quat::nLerp(quat dest, float lerpFactor, bool shortest) const
{
	quat correctedDest = dest;

	if (shortest && this->dot(dest) < 0) {
		correctedDest = quat(-dest.w, -dest.x, -dest.y, -dest.z);
	}

	return (((correctedDest - (*this)) * lerpFactor) + (*this)).normalized();
}

quat quat::sLerp(quat dest, float lerpFactor, bool shortest) const
{
	float epsilon = 1e3f;

	float cos = this->dot(dest);
	quat correctedDest = dest;

	if (shortest && cos < 0) {
		cos = -cos;
		correctedDest = quat(-dest.w, -dest.x, -dest.y, -dest.z);
	}

	if (fabsf(cos) >= 1 - epsilon) {
		return nLerp(correctedDest, lerpFactor, false);
	}

	float sin = sqrtf(1.0f - cos * cos);
	float angle = atan2f(sin, cos);
	float invSin = 1.0f / sin;

	float srcFactor = sinf((1.0f - lerpFactor) * angle) * invSin;
	float destFactor = sinf((lerpFactor)* angle) * invSin;

	return ((*this) * srcFactor) + (correctedDest * destFactor);
}

vec3 quat::getForward() const
{
	return this->rotatedVec3(vec3(0, 0, 1));
}

vec3 quat::getBack() const
{
	return this->rotatedVec3(vec3(0, 0, -1));
}

vec3 quat::getUp() const
{
	return this->rotatedVec3(vec3(0, 1, 0));
}

vec3 quat::getDown() const
{
	return this->rotatedVec3(vec3(0, -1, 0));
}

vec3 quat::getRight() const
{
	return this->rotatedVec3(vec3(1, 0, 0));
}

vec3 quat::getLeft() const
{
	return this->rotatedVec3(vec3(-1, 0, 0));
}

void quat::set(float w, float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

void quat::set(quat r)
{
	this->x = r.x;
	this->y = r.y;
	this->z = r.z;
	this->w = r.w;
}

quat quat::fromEulerDeg(vec3 eulerAngles)
{
	return fromEuler(vec3(degreesToRadians_F(eulerAngles.getX()),
						  degreesToRadians_F(eulerAngles.getY()), degreesToRadians_F(eulerAngles.getZ())));
}

quat quat::fromEuler(vec3 eulerAngles)
{
	//eulerAngles = [phi, theta, yota]
	float phi = eulerAngles.getX();
	float theta = eulerAngles.getY();
	float yota = eulerAngles.getZ();


	//locally store all cos/sin so we don't have to calculate them twice each
	float cosHalfPhi = cosf(phi / 2.0f);
	float sinHalfPhi = sinf(phi / 2.0f);
	float cosHalfTheta = cosf(theta / 2.0f);
	float sinHalfTheta = sinf(theta / 2.0f);
	float cosHalfYota = cosf(yota / 2.0f);
	float sinHalfYota = sinf(yota / 2.0f);

	float q0 = cosHalfPhi * cosHalfTheta * cosHalfYota + sinHalfPhi * sinHalfTheta * sinHalfYota;
	float q1 = sinHalfPhi * cosHalfTheta * cosHalfYota - cosHalfPhi * sinHalfTheta * sinHalfYota;
	float q2 = cosHalfPhi * sinHalfTheta * cosHalfYota + sinHalfPhi * cosHalfTheta * sinHalfYota;
	float q3 = cosHalfPhi * cosHalfTheta * sinHalfYota - sinHalfPhi * sinHalfTheta * cosHalfYota;

	return quat(q0, q1, q2, q3);
}

vec3 quat::toEulerAngles() const
{
	return vec3(toEulerX(), toEulerY(), toEulerZ());
}

float quat::toEulerX() const
{
	return atanf((2 * ((w*x) + (y*z))) / (1 - (2 * (x*x + y*y))));
}

float quat::toEulerY() const
{
	return asinf(2 * ((w*y) - (z*x)));
}

float quat::toEulerZ() const
{
	return atanf((2 * ((w*z) + (x*y))) / (1 - (2 * (y*y + z*z))));
}

float quat::getX() const
{
	return x;
}

void quat::setX(float x)
{
	this->x = x;
}

float quat::getY() const
{
	return y;
}

void quat::setY(float y)
{
	this->y = y;
}

float quat::getZ() const
{
	return z;
}

void quat::setZ(float z)
{
	this->z = z;
}

float quat::getW() const
{
	return w;
}

void quat::setW(float w)
{
	this->w = w;
}

bool quat::operator==(const quat& other) const
{
	return x == other.x && y == other.y && z == other.z && w == other.w;
}

quat quat::getCopy() const
{
	return quat(w, x, y, z);
}

quat quat::inverse() const {
	return conjugate();
	//TODO: add some stuff about unit quat
}
