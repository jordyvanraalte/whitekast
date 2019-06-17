#pragma once
#include "DrawComponent.h"
#include "ObjModel.h"
#include "GameObject.h"

class ModelComponent : public DrawComponent
{

public:

	ModelComponent(const std::string path, GameObject *gameObject);
	~ModelComponent();

	void draw() override;
};

