#include "vec2.h"

vec2::vec2(float f) : vec2(f, f)
{
}

vec2::vec2(const vec2& v)
{
	this->x = v.x;
	this->y = v.y;
}

vec2::vec2(float x, float y) : x(x), y(y)
{
}

//Sets x member to x
void vec2::setX(float x)
{
	this->x = x;
}

//Sets y member to y
void vec2::setY(float y)
{
	this->y = y;
}

//Sets x and y
void vec2::set(float x, float y)
{
	this->x = x;
	this->y = y;
}

//Sets this vec2's members to another vec2's members
void vec2::set(const vec2& v)
{
	this->x = v.x;
	this->y = v.y;
}

float vec2::getX() const
{
	return x;
}

float vec2::getY() const
{
	return y;
}

float vec2::calculateMagnitudeS() const
{
	return (x * x) + (y * y);
}

//Gets the length of the magnitude but doesn't store it
float vec2::calculateMagnitude() const
{
	return sqrtf((x * x) + (y * y));
}

void vec2::negate()
{
	x = -x;
	y = -y;
}

float vec2::dot(const vec2& v2) const
{
	return (x * v2.x) + (y * v2.y);
}

void vec2::rotate(float degrees)
{
	float r = degreesToRadians_F(degrees);
	float c = cosf(r);
	float s = sinf(r);
	x = x * c - y * s;
	y = x * s + y * c;
}

vec2 vec2::rotated(float degrees) const
{
	float r = degreesToRadians_F(degrees);
	float c = cosf(r);
	float s = sinf(r);
	return vec2(x * c - y * s, x * s + y * c);
}

void vec2::rotateR(float radians)
{
	float c = cosf(radians);
	float s = sinf(radians);
	x = x * c - y * s;
	y = x * s + y * c;
}

vec2 vec2::rotatedR(float radians) const
{
	float c = cosf(radians);
	float s = sinf(radians);
	return vec2(x * c - y * s, x * s + y * c);
}

float vec2::getRadians() const
{
	return atan2f(y, x);
}

vec2 vec2::getCopy() const
{
	return vec2(x, y);
}

vec3 vec2::toHomogeneous() const
{
	return vec3(x, y, 1);
}

vec3 vec2::toVec3() const
{
	return vec3(x, y, 0);
}

bool vec2::operator==(const vec2& v2) const
{
	return x == v2.x && y == v2.y;
}

vec2 vec2::normalized() const
{
	float m = calculateMagnitude();
	if (m == 0)
	{
		return vec2(0, 0);
	}
	return vec2(x / m, y / m);
}

void vec2::normalize()
{
	float m = calculateMagnitude();
	if (m != 0)
	{
		x /= m;
		y /= m;
	}
}


vec2 vec2::operator+(const vec2& v2) const
{
	return vec2(x + v2.x, y + v2.y);
}

vec2 vec2::operator-(const vec2& v2) const
{
	return vec2(x - v2.x, y - v2.y);
}

vec2 vec2::operator-() const
{
	return vec2(-x, -y);
}

void vec2::operator+=(const vec2& v2)
{
	x += v2.x;
	y += v2.y;
}

void vec2::operator-=(const vec2& v2)
{
	x -= v2.x;
	y -= v2.y;
}

vec2 vec2::operator*(const vec2& v2) const
{
	return vec2(x * v2.x, y * v2.y);
}

vec2 vec2::operator*(float f) const
{
	return vec2(x * f, y * f);
}

void vec2::operator*=(float f)
{
	x /= f;
	y /= f;
}

void vec2::operator*=(const vec2& v2)
{
	x *= v2.x;
	y *= v2.y;
}

vec2 vec2::operator/(const vec2& v2) const
{
	return vec2(x / v2.x, y / v2.y);
}

vec2 vec2::operator/(float f) const
{
	return vec2(x / f, y / f);
}

void vec2::operator/=(float f)
{
	x /= f;
	y /= f;
}

void vec2::operator/=(const vec2& v2)
{
	x /= v2.x;
	y /= v2.y;
}

bool vec2::operator>(const vec2 &v2) {
	return x > v2.x && y > v2.y;
}

bool vec2::operator<(const vec2 &v2) {
	return x < v2.x && y < v2.y;
}

vec2* vec2::operator()(const vec2& v2)
{
	x = v2.x;
	y = v2.y;
	return this;
}

bool vec2::isNull() const
{
	return isnan(x) || isnan(y);
}

float vec2::perpDot(const vec2 &v1, const vec2 &v2)
{
	return (v1.x * v2.y) - (v1.y * v2.x);
}

vec2 vec2::perp(const vec2 &v1, float s)
{
	return vec2(s * v1.y, -s * v1.x);
}

std::ostream &operator<<(std::ostream &stream, const vec2 &vec) {
	stream << "< " << vec.getX() << ", " << vec.getY() << " >";
	return stream;
}