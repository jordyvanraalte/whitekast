#pragma once

#include <iostream>
#include "GameObject.h"
#include "WhitekastObject.h"

#define _USE_MATH_DEFINES
#include <math.h>

class World
{
public:
	World(int horizontal, int vertical, std::list<GameObject*>& objectlist);
	~World();

	void idle(void);
	void display();
	void reshape(int width, int height);
	void move(float angle, float fac);
	void keyboard(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void mousePassiveMotion(int x, int y);
	static World* getWorld();
	void makePlatform();
};
