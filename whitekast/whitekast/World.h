#pragma once

#include <iostream>
#include "GameObject.h"
#include "WhitekastObject.h"
#include "WhitekastVision.h"
#include "CollisionManager.h"

#define _USE_MATH_DEFINES
#include <math.h>

class World
{

	std::list<GameObject*> gameObjects;
	GameObject* ball;
	CollisionManager* collisionManager;

	float lastFrameTime;

	float lookAtX;
	float lookAtY;
	bool keys[255];
	int width, height;

public:
	World(int horizontal, int vertical, std::list<GameObject*>& objectlist, WhitekastVision whitekastVision, GameObject* ball);
	~World();

	float deltaTime;

	void idle(void);
	void display();
	void reshape(int width, int height);
	void move(float angle, float fac);
	void keyboard(unsigned char key, int mouseX, int mouseY);
	void keyboardUp(unsigned char key, int mouseX, int mouseY);
	void mousePassiveMotion(int x, int y);
	void mouseClick(int button, int state, int x, int y);
	static World* getWorld();
	void makePlatform();
	Vec2f mirrorVectorInLine(::Vec2f d, LinesHitbox::Hitline b) const;

	void displayUI(int points, int lifepoints, int highScore);
};
