#pragma once

#include <vector>
#include "GameObject.h"

class World
{

public:
	World(int horizontal, int vertical);
	~World();

	World* createWorld(int, int);
	void idle(void);
	void display(std::vector<GameObject> objects);
	void reshape(int width, int height);
	void keyboard(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	static World* getWorld();
};


