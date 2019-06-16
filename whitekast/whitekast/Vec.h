#pragma once

#include <math.h>

#define PI 3.14159265
#define DEG_TO_RAD PI / 180.0f


class Vec3f
{
public:
	union
	{
		struct
		{
			float x, y, z;
		};
		float v[3];
	};
	::Vec3f();
	Vec3f(const Vec3f& other);
	Vec3f(const float x, const float y, const float z);

	float& operator [](int);
	void applyTime(const float elapsedtime);

	double magnitude() const;
};

inline ::Vec3f operator +(const ::Vec3f& lhs, const ::Vec3f& rhs)
{
	return ::Vec3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

inline ::Vec3f operator -(const ::Vec3f& lhs, const ::Vec3f& rhs)
{
	return ::Vec3f(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
}

class Vec2f
{
public:
	union
	{
		struct
		{
			float x, y;
		};
		float v[2];
	};
	Vec2f();
	Vec2f(const float x, const float y);
	Vec2f(const Vec2f& other);
	
	float& operator [](int);
	static float vectorDotProduct(::Vec2f& v1, ::Vec2f& v2);
	static Vec2f vectorNormalised(::Vec2f& v);

	double magnitude() const;
};

inline ::Vec2f operator +(const ::Vec2f& lhs, const ::Vec2f& rhs)
{
	return ::Vec2f(lhs.x + rhs.x, lhs.y + rhs.y);
}

inline ::Vec2f operator -(const ::Vec2f& lhs, const ::Vec2f& rhs)
{
	return ::Vec2f(lhs.x - rhs.x, lhs.y - rhs.y);
}

inline ::Vec2f operator *(const ::Vec2f& v, float f)
{
	return ::Vec2f(v.x * f , v.y * f);
}

inline ::Vec2f operator *(float f, const ::Vec2f& v)
{
	return ::Vec2f(v.x * f, v.y * f);
}

inline ::Vec2f rotateVector(::Vec2f& v, const float angle)
{
	auto radAngle = static_cast<float>(angle * DEG_TO_RAD);

	return ::Vec2f(
		static_cast<float>(v.x * cos(radAngle) - v.y * sin(radAngle)),
		static_cast<float>(v.x * sin(radAngle) + v.y * cos(radAngle))
	);
}


