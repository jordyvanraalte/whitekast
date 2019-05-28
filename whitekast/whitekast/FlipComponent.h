#pragma once

#include "Component.h"
#include "DrawComponent.h"

class FlipComponent : public Component
{
	float speed = 100.0f;
	bool up = true;
	bool flipping = true;
public:
	FlipComponent();
	~FlipComponent();
	bool isFlipping() const;
	bool isUp() const;
	void setUp(const bool up);
	virtual void handleEvent(float elapsedTime) override;
	virtual void setHandle(bool handle) override;
};