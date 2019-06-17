#pragma once

#include "WhitekastObject.h"
#include "WhitekastVision.h"

class World;
class AudioManager;
class GameObject;
class StateManager;
class PointCounter;
class LivesCounter;
class HighScore;

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
	HighScore*	  highScore;
	WhitekastVision vision;
	GameObject* ball;

	int horizontal = 0;
	int vertical = 0;
};
