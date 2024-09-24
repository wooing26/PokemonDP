#pragma once
#include "GameObject.h"

class Creature : public GameObject
{
	using Super = GameObject;
public:
	Creature();
	virtual ~Creature() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	virtual void	TickIdle() override {}
	virtual void	TickMove() override {}
	virtual void	TickRun() override {}
	virtual void	TickBattle() override {}

	virtual void	UpdateAnimation() override {}
};

