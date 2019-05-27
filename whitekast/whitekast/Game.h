#pragma once
#include "WhitekastObject.h"

class World;
class AudioManager;
class GameObject;
class StateManager;


class Game
{
public:
	Game(const char * title, int argc, char * argv[]);
	~Game();

	void startGame();
	void initGlut(const char* title, int argc, char* argv[]);
	void handleEvents();
	void update();
	void getDesktopResolution(int& horizontal, int& vertical);
	void clean();
	void initObjects();
	bool running() { return isRunning; }

private:
	bool isRunning;
	int worldSize = 10;
	std::list<GameObject*> objects;
	AudioManager* audiomanager;
};

