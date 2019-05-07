#pragma once

#include <vector>
#include "GameObject.h"

class World
{

public:
	World();
	~World();

	void idle(void);
	void display(std::vector<GameObject> objects);
	void reshape(int width, int height);
	static World* getWorld();
};


