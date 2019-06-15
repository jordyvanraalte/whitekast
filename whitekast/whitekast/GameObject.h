/*
	Component
	Purpose: Class that has multiple functions for components.

	@version 2.1 - 2019/06/03
*/

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
	~GameObject();

	bool isVisionObject;
	ObjModel *model;
	std::vector<cv::Point> coordinates;

	::Vec3f velocity;
	::Vec3f position;
	::Vec3f rotation;
	::Vec3f scale = ::Vec3f(1, 1, 1);
	::Vec3f color = ::Vec3f(1, 1, 1);
	::Vec3f rotationPoint;

	::Vec3f lastPosition;
	bool isColliding;
	bool isCollider;
	
	/*
		Adds a component to the component list.

		@param component - the component that you want to add to the list.
		@return void.
	*/
	void addComponent(Component* component);

	/*
		Loads a model in to the gameObject.

		@param fileName - searces the file name to load the model in the file
		@return bool.
	*/
	void loadModel(const std::string& fileName);

	/*
		Returns the componentlist

		@param -
		@return list with components.
	*/
	std::list<Component*> getComponents();

	/*
		updates the GameObject.

		@param elapsedTime - elapsed time since last call.
		@return void.
	*/
	void update(float elapsedTime);

	/*
		Handles an event.

		@param elapsedTime - elapsed time since last call
		@return bool.
	*/
	void handleEvent(float elapsedTime);

	/*
		Draws the gameObject.

		@param -
		@return void.
	*/
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
