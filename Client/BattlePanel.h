#pragma once
#include "Panel.h"

class Pokemon;

class BattlePanel : public Panel
{
	using Super = Panel;
public:
	BattlePanel();
	virtual ~BattlePanel() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	void			SetMyPokemon(Pokemon* pokemon);
	void			SetEnemyPokemon(Pokemon* pokemon);

private:
	Pokemon*		_myPokemon = nullptr;
	Pokemon*		_enemyPokemon = nullptr;
};

