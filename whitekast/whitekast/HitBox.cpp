#include "Hitbox.h"
#include <GL/freeglut.h>

Hitbox::Hitbox()
{
}

Hitbox::~Hitbox()
{
}

CircleHitbox::CircleHitbox(Vec3f pos, float d, Vec3f scale)
{
	cirlceHitbox = this;
	circle.x = pos.x;
	circle.y = pos.z;
	circle.r = (d/2)*scale.x;
}

void CircleHitbox::shiftColliders(Vec3f pos)
{
	cirlceHitbox = this;
	circle.x = pos.x;
	circle.y = pos.z;
}

LinesHitbox::LinesHitbox(std::vector<cv::Point> coordinates, Vec3f scale, float wkscale)
{
	lineHitbox = this;
	int firstX = 0, firstY = 0;

	bool first = true;

	for (const cv::Point point : coordinates)
	{
		if(first)
		{
			first = false;
			hitline.point1.x = (point.x*wkscale)*scale.x;
			hitline.point1.y = (point.y*wkscale)*scale.y;

			firstX = (point.x*wkscale)*scale.x;
			firstY = (point.y*wkscale)*scale.y;
		}
		else
		{
			hitline.point2.x = (point.x*wkscale)*scale.x;
			hitline.point2.y = (point.y*wkscale)*scale.y;

			hitlines.push_back(hitline);

			hitline.point1.x = (point.x*wkscale)*scale.x;
			hitline.point1.y = (point.y*wkscale)*scale.y;
		}
	}

	hitline.point2.x = firstX;
	hitline.point2.y = firstY;
	
	hitlines.push_back(hitline);
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

void LinesHitbox::flipColliders(::Vec3f pos)
{	
		hitline.point2.x += pos.x * 0.01;
		hitline.point2.y += pos.z * 0.01;
		glBegin(GL_QUADS);
		glColor3f(0, 0, 1);
		glVertex3f(hitline.point1.x, 0, hitline.point1.y);
		glVertex3f(hitline.point2.x, 0, hitline.point2.y);
		glVertex3f(hitline.point2.x, 5, hitline.point2.y);
		glVertex3f(hitline.point1.x, 5, hitline.point1.y);
		glEnd();
		hitlines.at(0) = hitline;	
		int x = 0;
}
