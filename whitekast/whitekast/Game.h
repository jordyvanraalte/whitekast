#pragma once
class Game
{
public:
	Game(const char* title, int argc, char* argv[]);
	~Game();

	void handleEvents();
	void update();
	void getDesktopResolution(int& horizontal, int& vertical);
	void makeObjects();

	void clean();
	bool running() { return isRunning; }

private:
	bool isRunning;

};

