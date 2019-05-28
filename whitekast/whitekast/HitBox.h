#pragma once
#include <list>
#include "Vec.h"

class Hitbox
{

protected:

	Hitbox* currentHitbox;

public:

	Hitbox();
	~Hitbox();

	virtual void shiftColliders(::Vec3f pos) {};
	virtual Hitbox* getHitbox() const { return currentHitbox; };

};

class CircleHitbox : public Hitbox
{


public:

	CircleHitbox* cirlceHitbox;

	struct Circle
	{
		float x, y, r;
	};

	Circle circle;


	CircleHitbox();
	CircleHitbox(::Vec3f pos, float radius); 
	~CircleHitbox();

	Hitbox* getHitbox() const override;
	void shiftColliders(::Vec3f pos) override;
};

class LinesHitbox : public Hitbox
{

public:


	LinesHitbox* lineHitbox;

	struct Hitline
	{
		::Vec2f point1;
		::Vec2f point2;
	};

	std::list<Hitline> hitlines;

	LinesHitbox();
	~LinesHitbox();

	Hitbox* getHitbox() const override;
	void shiftColliders(::Vec3f pos) override;
};
