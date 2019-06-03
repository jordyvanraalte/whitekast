#pragma once

#include "Component.h"
#include "DrawComponent.h"

class FlipComponent : public Component
{
	float speed = 100.0f;
	bool up = true;
	bool flipping = false;
	bool left = true;
public:
	FlipComponent(const bool l);
	~FlipComponent();
	bool isFlipping() const;
	bool isUp() const;
	bool isLeft() const;
	void setUp(const bool up);
	virtual void handleEvent(float elapsedTime) override;
	virtual void setHandle(bool handle) override;
};
