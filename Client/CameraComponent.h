#pragma once
#include "Component.h"

class CameraComponent : public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent();

	virtual void BeginPlay();
	virtual void TickComponent();
	virtual void Render(HDC hdc);


};

