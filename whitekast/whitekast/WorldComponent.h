#pragma once

#include "DrawComponent.h"
#include <iostream>
#include <list>
#include "Texture.h"

class WorldComponent : public DrawComponent
{
public:
	float size;
	Texture texture1;
	Texture texture2;
	Texture texture3;
	Texture texture4;
	Texture texture5;

	WorldComponent(float size, Texture texture1, Texture texture2, Texture texture3, Texture texture4, Texture texture5);
	~WorldComponent();

	virtual void draw() override;
};

