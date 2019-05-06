#pragma once

class World
{
private:
	World(const char* titel, int argc, char *argv[], int width, int height);
	~World();

	void idle(void);
	void display(void);
	void reshape(int width, int height);

public:
	World* getWorld(const char* titel, int argc, char* argv[], int width, int height);
};


