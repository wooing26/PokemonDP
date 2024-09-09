#pragma once
#include "Panel.h"

class EditPanel : public Panel
{
	using Super = Panel;
public:
	EditPanel();
	virtual ~EditPanel() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	void			OnClickTilemapButton();
	void			OnClickBattleButton();
};

