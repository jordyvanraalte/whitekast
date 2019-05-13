#pragma once

#include <GL/freeglut.h>

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void translate(float x, float y, float z);
	virtual void draw(void);

	void debug(void);
	
};

