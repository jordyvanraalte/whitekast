#include "BallComponent.h"
#include <GL/freeglut.h>


BallComponent::BallComponent()
{
	this->speed = 0;
}


BallComponent::~BallComponent()
{
}

void BallComponent::draw()
{
	
}

void BallComponent::update() 
{
	speed -= 1;
}