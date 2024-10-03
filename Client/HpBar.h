#pragma once
#include "UI.h"

class Sprite;
class Pokemon;

struct Status
{
	int32   level = 50;
	int32	hp = 500;
	int32   maxHp = 500;
	int32	exp = 0;
	int32	maxExp = 500;
};

class HpBar : public UI
{
	using Super = UI;
public:
	HpBar();
	virtual ~HpBar() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	void			SetIsMine(bool isMine) { _isMine = isMine; }

	void			SetPokemon(Pokemon* pokemon);

private:
	Pokemon*		_pokemon = nullptr;

	Sprite*			_statusBar = nullptr;
	Sprite*			_numbers[10] = {};
	Sprite*			_expBar = nullptr;

	Sprite*			_currentHpBar = nullptr;
	int32			_standardHp = 0;
	Sprite*			_hpBar[3] = {};

	int32			_ratio = 4;

	bool			_isMine = true;
};

