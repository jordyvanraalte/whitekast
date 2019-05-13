#pragma once

#include <iostream>
#include "GameObject.h"
#include "WhitekastObject.h"

class World
{
public:
	World(int horizontal, int vertical, std::list<GameObject*> objectlist);
	~World();

	void idle(void);
	void display();
	void displayVisionObjects(vector<WhitekastObject>);
	void reshape(int width, int height);
	void keyboard(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void mousePassiveMotion(int x, int y);
	static World* getWorld();
};


