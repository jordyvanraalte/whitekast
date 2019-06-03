#pragma once
class Game;

class State
{
public:
	State();
	~State();
	virtual void handle(Game* game);
	

};

