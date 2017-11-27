#include "vec4.h"

vec4::vec4(float f) : vec4(f, f, f, f) {}

vec4::vec4(const vec4 & v) {
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}

vec4::vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {
}

void vec4::setX(float x) {
	this->x = x;
}

void vec4::setY(float y) {
	this->y = y;
}

void vec4::setZ(float z) {
	this->z = z;
}

void vec4::setW(float w) {
	this->w = w;
}

void vec4::set(float x, float y, float z, float w) {
	this->y = y;
	this->x = x;
	this->z = z;
	this->w = w;
}

void vec4::set(const vec4 & v2) {
	x = v2.x;
	y = v2.y;
	z = v2.z;
	w = v2.w;
}

float vec4::getX() const {
	return x;
}

float vec4::getY() const {
	return y;
}

float vec4::getZ() const {
	return z;
}

float vec4::getW() const {
	return w;
}

float vec4::calculateMagnitudeS() const {
	return ((x * x) + (y * y) + (z * z) + (w * w));
}


float vec4::calculateMagnitude() const {
	return sqrtf((x * x) + (y * y) + (z * z) + (w * w));
}

vec4 vec4::normalized() const {
	float amt = calculateMagnitude();
	if (amt == 0) {
		return vec4(0, 0, 0, 0);
	}
	return vec4(x / amt, y / amt, z / amt, w / amt);
}

void vec4::normalize() {
	float amt = calculateMagnitude();
	if (amt != 0) {
		x /= amt;
		y /= amt;
		z /= amt;
		w /= amt;
	}
}

void vec4::negate() {
	x = -x;
	y = -y;
	z = -z;
	w = -w;
}

float vec4::dot(const vec4& v2) const {
	return (x * v2.x) + (y * v2.y) + (z * v2.z) + (w * v2.w);
}

vec4 vec4::getCopy() const
{
	return vec4(x, y, z, w);
}

bool vec4::operator==(const vec4& v2) const
{	
	return x == v2.x && y == v2.y && z == v2.z && w == v2.w;
}

vec4 vec4::operator+(const vec4& v2) const
{
	return vec4(x + v2.x, y + v2.y, z + v2.z, w + v2.w);
}

vec4 vec4::operator-(const vec4& v2) const
{
	return vec4(x - v2.x, y - v2.y, z - v2.z, w - v2.w);
}

vec4 vec4::operator-() const {
	return vec4(-x, -y, -z, -w);
}

void vec4::operator+=(const vec4& v2) {
	x += v2.x;
	y += v2.y;
	z += v2.z;
	w += v2.w;
}

void vec4::operator-=(const vec4& v2) {
	x -= v2.x;
	y -= v2.y;
	z -= v2.z;
	w -= v2.w;
}

vec4 vec4::operator*(const vec4& v2) const {
	return vec4(x * v2.getX(), y * v2.getY(), z * v2.getZ(), w * v2.getW());
}

vec4 vec4::operator*(float f) const {
	return vec4(x * f, y * f, z * f, w * f);
}

void vec4::operator*=(float f)
{
	x *= f;
	y *= f;
	z *= f;
	w *= f;
}

void vec4::operator*=(const vec4& v2)
{
	x *= v2.getX();
	y *= v2.getY();
	z *= v2.getZ();
	w *= v2.getW();
}

vec4 vec4::operator/(const vec4& v2) const
{
	return vec4(x / v2.getX(), y / v2.getY(), z / v2.getZ(), w / v2.getW());
}

vec4 vec4::operator/(float f) const
{
	return vec4(x / f, y / f, z / f, w / f);
}

void vec4::operator/=(float f)
{
	x /= f;
	y /= f;
	z /= f;
	w /= f;
}

void vec4::operator/=(const vec4& v2)
{
	x /= v2.getX();
	y /= v2.getY();
	z /= v2.getZ();
	w /= v2.getW();
}

vec4* vec4::operator()(const vec4& v2)
{
	x = v2.x;
	y = v2.y;
	z = v2.z;
	w = v2.w;
	return this;
}