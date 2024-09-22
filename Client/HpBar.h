#pragma once
#include "UI.h"

class Sprite;

struct Status
{
	int32   level = 50;
	int32	hp = 21;
	int32   maxHp = 21;
	int32	exp = 100;
	int32	maxExp = 100;
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

	void			SetStatus(Status status) { _status = status; }
	void			SetHp(int32 hp) { _status.hp = hp; }
	void			SetExp(int32 exp) { _status.exp = exp; }

private:
	Sprite*			_statusBar = nullptr;
	Sprite*			_numbers[10] = {};
	Sprite*			_expBar = nullptr;

	Sprite*			_currentHpBar = nullptr;
	int32			_standardHp = 0;
	Sprite*			_hpBar[3] = {};

	int32			_ratio = 4;

	bool			_isMine = true;

	Status			_status = {};
};

