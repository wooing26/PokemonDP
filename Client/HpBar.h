#pragma once
#include "UI.h"

class Sprite;

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

private:
	Sprite*			_hpBar = nullptr;
	bool			_isMine = true;
};

