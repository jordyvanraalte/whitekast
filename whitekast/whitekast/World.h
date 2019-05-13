#pragma once

#include <vector>
#include "GameObject.h"

class World
{
public:
	World(int horizontal, int vertical, std::list<GameObject*> objectlist);
	~World();

	void idle(void);
	void display();
	void reshape(int width, int height);
	void keyboard(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void mousePassiveMotion(int x, int y);
	static World* getWorld();
};


