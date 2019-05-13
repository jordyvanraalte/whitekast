#pragma once

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
	Vec3f();
	Vec3f(const Vec3f& other);
	Vec3f(const float x, const float y, const float z);
	float& operator [](int);
};

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
};

