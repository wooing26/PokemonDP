#pragma once
#include "GameObject.h"

class Flipbook;

class Player : public GameObject
{
	using Super = GameObject;
public:
	Player();
	virtual ~Player();

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	virtual void	TickIdle() override;
	virtual void	TickMove() override;
	virtual void	TickSkill() override;

	virtual void	UpdateAnimation() override;

private:
	Flipbook* _flipbookIdle[4] = {};
	Flipbook* _flipbookMove[4] = {};
	Flipbook* _flipbookRun[4] = {};
	Flipbook* _flipbookBicycle[4] = {};
};

