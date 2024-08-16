#pragma once


class Graphic
{
public:
	Graphic();
	~Graphic();

	HRESULT		Init(HWND hwnd);
	void		Render();
	void		Clear();

	void		Resize(uint32 width, uint32 height);

private:
	ID2D1Factory*			_directFactory = nullptr;
	ID2D1HwndRenderTarget*	_renderTarget = nullptr;
	ID2D1SolidColorBrush* myLightSlateGrayBrush = nullptr;
	ID2D1SolidColorBrush* myCornflowerBlueBrush = nullptr;
};

