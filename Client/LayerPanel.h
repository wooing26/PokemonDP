#pragma once
#include "Panel.h"

class LayerPanel : public Panel
{
	using Super = Panel;
public:
	LayerPanel();
	virtual ~LayerPanel() override;

	virtual void	BeginPlay() override;
	virtual void	Tick() override;
	virtual void	Render(HDC hdc) override;

	void			OnClickLayerButton();
};

