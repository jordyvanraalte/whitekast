#pragma once

#include "WhitekastObject.h"
#include "DeathState.h"

class World;
class AudioManager;
class GameObject;
class StateManager;

class Game
{
public:

	int lives = 1;
	Game(const char * title, int argc, char * argv[]);
	~Game();

	void startGame();
	void initGlut(const char* title, int argc, char* argv[]);
	void handleEvents();
	void reset();
	void getDesktopResolution(int& horizontal, int& vertical);
	void stop();
	void initObjects();
	void initFlippers();
	bool running() { return isRunning; }
	static Game* getInstance();

private:
	bool isRunning;
	const int worldSize = 10;
	int boardWidth;
	int boardHeight;
	
	std::list<GameObject*> objects;
	AudioManager* audiomanager;
};
