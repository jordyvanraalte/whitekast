#pragma once

class PointCounter
{
private:
	int points;
	const int bumperPoints = 5;
	const int flipperPoints = 2;
	const int specialPoints = 500;
public:
	PointCounter();
	~PointCounter();

	void hitSpecial();
	void hitBumper();
	void hitFlipper();
	void resetPoints();
	int getPoints();
	void setPoints(int points);

	static PointCounter* getInstance();
};