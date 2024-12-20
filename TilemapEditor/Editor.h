#pragma once

class Editor
{
public:
	Editor();
	~Editor();

public:
	void Init(HWND mainHwnd, HWND paletteHwnd);
	void Update();
	void Render();

private:
	void MainRender();
	void PaletteRender();

private:
	HWND	_mainHwnd = {};
	HDC		_mainHdc = {};
	HWND	_paletteHwnd = {};
	HDC		_paletteHdc = {};

private:
	// Double Buffering
	// Main
	RECT	_mainRect;
	HDC		_mainHdcBack = {};
	HBITMAP _mainBmpBack = {};

	// Palette
	RECT	_paletteRect;
	HDC		_paletteHdcBack = {};
	HBITMAP _paletteBmpBack = {};
};

