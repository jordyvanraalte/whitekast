#pragma once

#include <list>
#include <string>
#include "Vec.h"
#include "ObjModel.h"
#include "HitBox.h"

class Component;
class DrawComponent;
class FlipComponent;
class CollideComponent;

class GameObject
{
	DrawComponent* drawComponent = nullptr;
	FlipComponent* flipComponent = nullptr;
	CollideComponent* collideComponent = nullptr;

	std::list<Component*> components;
	
	::Vec3f vectemp;

public:
	GameObject(bool isVisionObject);
	GameObject(std::string fileName);
	~GameObject();

	bool isVisionObject;
	ObjModel *model;
	std::vector<cv::Point> coordinates;

	::Vec3f velocity;
	::Vec3f position;
	::Vec3f lastPosition;
	bool hasCollided;
	::Vec3f rotation;
	::Vec3f scale = ::Vec3f(1, 1, 1);
	::Vec3f rotationPoint;
	
	void addComponent(Component* component);
	void loadModel(const std::string& fileName);
	std::list<Component*> getComponents();

	void update(float elapsedTime);
	void handleEvent(float elapsedTime);
	void draw();

	void setCoordinates(std::vector<cv::Point> coordinates);
	Hitbox* getHitbox() const;

	template<class T>
	T* getComponent()
	{
		for (auto c : components)
		{
			T* t = dynamic_cast<T*>(c);
			if (t)
				return t;
		}
	}

	template<class T>
	void removeComponent()
	{
		components.remove_if([](Component * c)
			{
				T* t = dynamic_cast<T*>(c);
				return t != nullptr;
			});
	}
};
