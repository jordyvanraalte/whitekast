#pragma once

#include <list>
#include <string>
#include "Vec.h"
#include "ObjModel.h"

class Component;
class DrawComponent;
class FlipComponent;

class GameObject
{
	DrawComponent* drawComponent = nullptr;
	FlipComponent* flipComponent = nullptr;
	ObjModel* model = nullptr;

	std::list<Component*> components;
public:
	GameObject();
	GameObject(std::string fileName);
	~GameObject();


	::Vec3f position;
	::Vec3f rotation;
	::Vec3f scale = ::Vec3f(1, 1, 1);
	::Vec3f rotationPoint;


	void addComponent(Component* component);
	std::list<Component*> getComponents();
	void update(float elapsedTime);
	void handleEvent(float elapsedTime);
	void draw();

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


