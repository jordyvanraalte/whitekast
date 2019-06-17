#pragma once

class HighScore
{
public:
	HighScore();
	~HighScore();
	int getHighScore();
	void setHighScore(int highScore);
	static HighScore* getInstance();
};