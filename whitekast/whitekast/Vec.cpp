#include "Vec.h"

Vec3f::Vec3f(float x, float y, float z)
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

Vec3f Vec3f::operator-(const Vec3f& other)
{
	return Vec3f(x - other.x, y - other.y, z - other.z);
}

Vec3f Vec3f::normalized() const
{
	float len = length();
	return Vec3f(x / len, y / len, z / len);
}

float Vec3f::length() const
{
	return sqrt(x * x + y * y + z * z);
}



Vec2f::Vec2f(float x, float y)
{
	this->x = x;
	this->y = y;
}
Vec2f::Vec2f()
{
	this->x = 0;
	this->y = 0;
}
Vec2f::Vec2f(Vec2f& other)
{
	this->x = other.x;
	this->y = other.y;
}

float& Vec2f::operator [](int index)
{
	return v[index];
}

