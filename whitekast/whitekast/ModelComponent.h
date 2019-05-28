#pragma once
#include "DrawComponent.h"
#include "ObjModel.h"
#include "GameObject.h"

class ModelComponent : public DrawComponent
{

	ObjModel *model;

public:

	ModelComponent(const std::string path);
	~ModelComponent();

	void draw() override;
};

