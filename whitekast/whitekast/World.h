#pragma once

class World
{
public:
	World();
	~World();

	void idle(void);
	void display(void);
	void reshape(int width, int height);
	static World* getWorld();
};


