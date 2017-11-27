#include "vec3.h"

vec3 vec3::getCrossProduct(vec3 v1, vec3 v2)
{
	float cx = (v1.y * v2.z) - (v1.z * v2.y);
	float cy = (v1.z * v2.x) - (v1.x * v2.z);
	float cz = (v1.x * v2.y) - (v1.y * v2.x);
	return vec3(cx, cy, cz);
}

vec3::vec3(float f) : vec3(f, f, f) {}

vec3::vec3(const vec3 & v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
}

vec3::vec3(float x, float y, float z) : x(x), y(y), z(z) {
}

void vec3::setX(float x)
{
	this->x = x;
}

void vec3::setY(float y)
{
	this->y = y;
}

void vec3::setZ(float z)
{
	this->z = z;
}

void vec3::set(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void vec3::set(const vec3 & v2)
{
	this->x = v2.x;
	this->y = v2.y;
	this->z = v2.z;
}

float vec3::getX() const
{
	return x;
}

float vec3::getY() const
{
	return y;
}

float vec3::getZ() const
{
	return z;
}

float vec3::calculateMagnitudeS() const {
	return (x * x) + (y * y) + (z * z);
}


float vec3::calculateMagnitude() const
{
	return sqrtf((x * x) + (y * y) + (z * z));
}

vec3 vec3::normalized() const
{
	float amt = calculateMagnitude();
	if (amt == 0) {
		return vec3(0, 0, 0);
	}
	return vec3(x / amt, y / amt, z / amt);
}

void vec3::normalize()
{
	float amt = calculateMagnitude();
	if (amt != 0) {
		x /= amt;
		y /= amt;
		z /= amt;
	}
}

void vec3::negate()
{
	x = -x;
	y = -y;
	z = -z;
}

float vec3::dot(const vec3 & v2) const
{
	return (x * v2.x) + (y * v2.y) + (z * v2.z);
}

vec3 vec3::getCopy() const
{
	return vec3(x, y, z);
}

vec4 vec3::toHomogeneous() const
{
	return vec4(x, y, z, 1);
}

vec4 vec3::toVec4() const
{
	return vec4(x, y, z, 0);
}

bool vec3::operator==(const vec3 & v2) const
{
	return x == v2.x && y == v2.y && z == v2.z;
}

vec3 vec3::operator+(const vec3 & v2) const
{
	return vec3(x + v2.x, y + v2.y, z + v2.z);
}

vec3 vec3::operator-(const vec3 & v2) const
{
	return vec3(x - v2.x, y - v2.y, z - v2.z);
}

vec3 vec3::operator-() const {
	return vec3(-x, -y, -z);
}

void vec3::operator+=(const vec3 & v2)
{
	x += v2.x;
	y += v2.y;
	z += v2.z;
}

void vec3::operator-=(const vec3 & v2)
{
	x -= v2.x;
	y -= v2.y;
	z -= v2.z;
}

vec3 vec3::operator*(const vec3 & v2) const
{
	return vec3(x * v2.getX(), y * v2.getY(), z * v2.getZ());
}

vec3 vec3::operator*(float f) const
{
	return vec3(x * f, y * f, z * f);
}

void vec3::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
}

void vec3::operator*=(const vec3 & v2)
{
	x *= v2.getX();
	y *= v2.getY();
	z *= v2.getZ();
}

vec3 vec3::operator/(const vec3 & v2) const
{
	return vec3(x / v2.getX(), y / v2.getY(), z / v2.getZ());
}

vec3 vec3::operator/(float f) const
{
	return vec3(x / f, y / f, z / f);
}

void vec3::operator/=(float f)
{
	x /= f;
	y /= f;
	z /= f;
}

void vec3::operator/=(const vec3 & v2)
{
	x /= v2.getX();
	y /= v2.getY();
	z /= v2.getZ();
}

vec3* vec3::operator()(const vec3& v2)
{
	x = v2.x;
	y = v2.y;
	z = v2.z;
	return this;
}