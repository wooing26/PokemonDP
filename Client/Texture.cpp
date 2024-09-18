#include "pch.h"
#include "Texture.h"

Texture::Texture()
{
}

Texture::~Texture()
{
	
}

Texture* Texture::LoadBmp(HWND hwnd, const std::wstring& path)
{
	HDC hdc = ::GetDC(hwnd);

	_hdc = ::CreateCompatibleDC(hdc);

	_bitmap = (HBITMAP)::LoadImage(nullptr, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION | LR_DEFAULTSIZE);

	if (_bitmap == NULL)
	{
		::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);
	}

	HBITMAP prev = (HBITMAP)::SelectObject(_hdc, _bitmap);
	::DeleteObject(prev);

	BITMAP bit = {};
	::GetObject(_bitmap, sizeof(BITMAP), &bit);
	_size.x = bit.bmWidth;
	_size.y = bit.bmHeight;

	return this;
}

Texture* Texture::LoadPng(HWND hwnd, const std::wstring& path)
{
	HDC hdc = ::GetDC(hwnd);

	_hdc = ::CreateCompatibleDC(hdc);

	Gdiplus::Image* image = Gdiplus::Image::FromFile(path.c_str());

	if (image == NULL)
	{
		::MessageBox(hwnd, path.c_str(), L"Image Load Failed", NULL);
	}

	_size.x = image->GetWidth();
	_size.y = image->GetHeight();

	Gdiplus::Bitmap* bitmap = static_cast<Gdiplus::Bitmap*>(image);
	bitmap->GetHBITMAP(Gdiplus::Color(0, 0, 0), &_bitmap);
	HBITMAP prev = (HBITMAP)::SelectObject(_hdc, _bitmap);
	::DeleteObject(prev);

	delete image;
	image = nullptr;

	return this;
}
