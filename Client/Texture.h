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

	void			SetTransparent(Gdiplus::Color transparent) { _transparent = transparent; }
	Gdiplus::Color	GetTransparent() { return _transparent; }

private:
	HDC					_hdc = {};
	HBITMAP				_bitmap = {};
	Gdiplus::Image*		_image = nullptr;
	Vec2Int				_size = {};
	Gdiplus::Color		_transparent = Gdiplus::Color(147, 187, 236);

private:
	
};

