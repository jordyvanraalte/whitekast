/*
	Component
	Purpose: Base class for components, so they can be stored in the same list.
			 Also provides overrides for components.

	@version 1.5 - 2019/06/03
*/

#pragma once
#include "Vec.h"

class GameObject;

class Component
{
protected:
	GameObject* gameObject;

public:
	explicit Component();
	virtual ~Component();

	/*
		Updates the component.

		@param elapsedTime - elapsed time since last call.
		@return virtual void.
	*/
	virtual void update(float elapsedTime) {};

	/*
		handles an event when called

		@param elapsedTime - elapsed time since last call.
		@return virtual void.
	*/
	virtual void handleEvent(float elapsedTime) {};

	/*
		Sets a boolean

		@param handle - boolean to set handle off or on.
		@return virtual void.
	*/
	virtual void setHandle(bool handle) {};

	/*
		Sets the gameobject to the parameter object.

		@param gameObject - Sets this->gameObject.
		@return virtual inline.
	*/
	virtual inline void setGameObject(GameObject* gameObject) { this->gameObject = gameObject; }
};

