#include "Hitbox.h"

Hitbox::Hitbox()
{
}

Hitbox::~Hitbox()
{
}

CircleHitbox::CircleHitbox(Vec3f pos, float d)
{
	cirlceHitbox = this;
	circle.x = pos.x;
	circle.y = pos.y;
	circle.r = (d/2);
}

Hitbox* CircleHitbox::getHitbox() const
{
	return cirlceHitbox;
}

void CircleHitbox::shiftColliders(Vec3f pos)
{
	currentHitbox = this;
	circle.x = pos.x;
	circle.y = pos.z;
}

LinesHitbox::LinesHitbox()
{
	
}

Hitbox* LinesHitbox::getHitbox() const
{
	return lineHitbox;
}

void LinesHitbox::shiftColliders(Vec3f pos)
{
	for (Hitline line : hitlines)
	{
		line.point1.x += pos.x;
		line.point1.y += pos.y;

		line.point2.x += pos.x;
		line.point2.y += pos.y;
	}
}
