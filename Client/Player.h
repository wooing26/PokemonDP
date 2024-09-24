#pragma once
#include "Creature.h"

class Flipbook;

class Player : public Creature
{
	using Super = Creature;
public:
	Player();
	virtual ~Player() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	virtual void	TickIdle() override;
	virtual void	TickMove() override;
	virtual void	TickRun() override;
	virtual void	TickBattle() override;

	virtual void	UpdateAnimation() override;

private:
	Flipbook*	_flipbookIdle[4] = {};
	Flipbook*	_flipbookMove[4] = {};
	Flipbook*	_flipbookRun[4] = {};
	Flipbook*	_flipbookBicycle[4] = {};

	bool		_onBicycle = false;
};

