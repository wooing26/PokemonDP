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

	void			SetBattleMode(bool onBattle) { _onBattle = onBattle; }
	bool			GetBattleMode() { return _onBattle; }

private:
	bool			_onBattle = false;
};

