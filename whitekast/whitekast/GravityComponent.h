#pragma once
#include "Component.h"

class GravityComponent : public Component
{
private:
	::Vec3f gravity{};

public:
	GravityComponent(::Vec3f g);
	~GravityComponent();

	void update(float elapsedTime) override;
};

