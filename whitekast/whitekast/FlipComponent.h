#pragma once

#include "Component.h"
#include "DrawComponent.h"

class FlipComponent : public Component
{
	float speed = 100.0f;
	bool up = true;
	bool flipping = true;
	bool left = true;
public:
	FlipComponent(const bool l);
	~FlipComponent();

	/*
		Returns a boolean, that says if the flipper is currently flipping.

		@param -
		@return bool.
	*/
	bool isFlipping() const;

	/*
		Returns a boolean, that says if the flipper is currently up.

		@param -
		@return bool.
	*/
	bool isUp() const;
	
	bool isLeft() const;

	/*
		Returns a boolean, that says if the flipper is currently set up.

		@param -
		@return bool.
	*/
	void setUp(const bool up);

	virtual void handleEvent(float elapsedTime) override;
	virtual void setHandle(bool handle) override;
};
