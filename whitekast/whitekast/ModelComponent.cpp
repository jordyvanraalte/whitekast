#include "ModelComponent.h"

ModelComponent::ModelComponent(std::string path, GameObject* gameobject)
{
	this->gameObject = gameobject;
	gameObject->model = new ObjModel();
	gameObject->model->load(path);
}

ModelComponent::~ModelComponent()
= default;

void ModelComponent::draw()
{
	gameObject->model->draw();
}
