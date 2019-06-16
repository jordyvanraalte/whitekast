#pragma once

#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include "DeathState.h"

class World;
class AudioManager;
class GameObject;
class StateManager;
class PointCounter;
class LivesCounter;

class Game
{
public:

	int lives = 1;
	Game(const char * title, int argc, char * argv[]);
	~Game();

	void startGame();
	void startVisionThread();
	void initGlut(const char* title, int argc, char* argv[]);
	void handleEvents();
	void death();
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
	PointCounter* pointCounter;
	LivesCounter* livesCounter;
	WhitekastVision vision;
};
