#include "PointCounter.h"

static PointCounter* pointCounterInstance;

PointCounter::PointCounter()
{
	points = 0;
}

PointCounter::~PointCounter()
{

}

void PointCounter::hitBumper()
{
	points = points + bumperPoints;
}
void PointCounter::hitFlipper()
{
	points = points + flipperPoints;
}

void PointCounter::resetPoints()
{
	points = 0;
}
int PointCounter::getPoints()
{
	return points;
}

void PointCounter::setPoints(int points)
{
	this->points = points;
}

PointCounter* PointCounter::getInstance()
{
	if (pointCounterInstance == nullptr)
		pointCounterInstance = new PointCounter();

	return pointCounterInstance;
}
