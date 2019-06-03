#pragma once

class LivesCounter
{
private:
	int lives;

public:
	LivesCounter();
	~LivesCounter();

	void loseLive();
	void resetLives();
	int getLives();
	void setLives(int lives);

	static LivesCounter* getInstance();
};