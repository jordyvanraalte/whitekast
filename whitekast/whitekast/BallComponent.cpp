#include "BallComponent.h"
#include <GL/freeglut.h>


BallComponent::BallComponent() : ball(new ObjModel("Models/Pinballs/pinball_3.1.obj")), speed(0)
{

}


BallComponent::~BallComponent()
{
}

void BallComponent::draw()
{
	ball->draw();
}

void BallComponent::update() 
{
	speed -= 1;
}
