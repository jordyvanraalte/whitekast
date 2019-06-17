#include "Vec.h"

Vec3f::Vec3f(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vec3f::Vec3f()
{
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vec3f::Vec3f(const Vec3f& other)
{
	this->x = other.x;
	this->y = other.y;
	this->z = other.z;
}

float& Vec3f::operator [](int index)
{
	return v[index];
}

void Vec3f::applyTime(const float elapsedtime)
{
	this->x = this->x * elapsedtime;
	this->y = this->y * elapsedtime;
	this->z = this->z * elapsedtime;
}

double Vec3f::magnitude() const
{
	return sqrt(pow(this->x, 2) + pow(this->z, 2) + pow(this->y, 2));
}

Vec2f::Vec2f(const float x, const float y)
{
	this->x = x;
	this->y = y;
}
Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}
Vec2f::Vec2f(const Vec2f& other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](int index)
{
	return v[index];
}

float Vec2f::vectorDotProduct(::Vec2f& v1, ::Vec2f& v2)
{
	return (v1.x * v2.x) + (v1.y * v2.y);
}

Vec2f Vec2f::vectorNormalised(::Vec2f& v)
{
	float magnitude = sqrt((v.x*v.x) + (v.y*v.y));
	return Vec2f((v.x / magnitude), (v.y / magnitude));
}

double Vec2f::magnitude() const
{
	return sqrt(pow(this->x, 2) + pow(this->y, 2));
}
