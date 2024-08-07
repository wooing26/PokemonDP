#pragma once
#include "ResourceBase.h"

class Texture : public ResourceBase
{
public:
	Texture();
	virtual ~Texture();

public:
	Texture*		LoadBmp(HWND hwnd, const std::wstring& path);
	Texture*		LoadPng(HWND hwnd, const std::wstring& path);	
	HDC				GetDC() { return _hdc; }
	Gdiplus::Image*	GetImage() { return _image; }

	void			SetSize(Vec2Int size) { _size = size; }
	Vec2Int			GetSize() { return _size; }

	void			SetTransparent(uint32 transparent) { _transparent = transparent; }
	uint32			GetTransparent() { return _transparent; }

private:
	HDC					_hdc = {};
	HBITMAP				_bitmap = {};
	Gdiplus::Image*		_image = nullptr;
	Vec2Int				_size = {};
	uint32				_transparent = RGB(255, 0, 255);
};

