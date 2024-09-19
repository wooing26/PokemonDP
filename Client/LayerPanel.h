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

	void			OnClickLayerButton0();
	void			OnClickLayerButton1();
	void			OnClickLayerButton2();
	void			OnClickLayerButton3();

	int32			GetSelectedLayer() { return _selectedLayer; }

	RECT			GetRect() { return _rect; }

private:
	int32			_selectedLayer = 0;
	RECT			_rect = {};
};

