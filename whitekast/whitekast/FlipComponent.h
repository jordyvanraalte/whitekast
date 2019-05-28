#pragma once

#include "Component.h"
#include "DrawComponent.h"

class FlipComponent : public Component
{
	float speed = 30.0f;
	bool flipping = false;
public:
	FlipComponent();
	~FlipComponent();
	bool isFlipping() const;
	void setFlipping (const bool flipping);
	virtual void handleEvent(float elapsedTime) override;
};