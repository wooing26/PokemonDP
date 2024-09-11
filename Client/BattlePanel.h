#pragma once
#include "Panel.h"

class BattlePanel : public Panel
{
	using Super = Panel;
public:
	BattlePanel();
	virtual ~BattlePanel() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;
};

