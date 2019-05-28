#include "ModelComponent.h"

ModelComponent::ModelComponent(std::string path)
{
	model = new ObjModel();
	model->load(path);
}

ModelComponent::~ModelComponent()
= default;

void ModelComponent::draw()
{
	model->draw();
}
