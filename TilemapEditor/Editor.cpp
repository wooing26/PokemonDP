#include "pch.h"
#include "Editor.h"
#include "InputManager.h"

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::Init(HWND mainHwnd, HWND paletteHwnd)
{
	// Main
	_mainHwnd = mainHwnd;
	_mainHdc = ::GetDC(mainHwnd);

	::GetClientRect(mainHwnd, &_mainRect);

	_mainHdcBack = ::CreateCompatibleDC(_mainHdc);											// hdc�� ȣȯ�Ǵ� DC ����
	_mainBmpBack = ::CreateCompatibleBitmap(_mainHdc, _mainRect.right, _mainRect.bottom);	// hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev1 = (HBITMAP)::SelectObject(_mainHdcBack, _mainBmpBack);						// dcBack�� ��Ʈ�� ����
	::DeleteObject(prev1);

	// palette DC
	_paletteHwnd = paletteHwnd;
	_paletteHdc = ::GetDC(paletteHwnd);

	::GetClientRect(paletteHwnd, &_paletteRect);

	_paletteHdcBack = ::CreateCompatibleDC(_mainHdc);														// hdc�� ȣȯ�Ǵ� DC ����
	_paletteBmpBack = ::CreateCompatibleBitmap(_paletteHdcBack, _paletteRect.right, _paletteRect.bottom);	// hdc�� ȣȯ�Ǵ� ��Ʈ�� ����
	HBITMAP prev2 = (HBITMAP)::SelectObject(_paletteHdcBack, _paletteBmpBack);								// dcBack�� ��Ʈ�� ����
	::DeleteObject(prev2);
	

	// Manager Init
	GET_SINGLE(InputManager)->Init(mainHwnd, paletteHwnd);
}

void Editor::Update()
{
	GET_SINGLE(InputManager)->Update();
}

void Editor::Render()
{
	MainRender();
	PaletteRender();
}

void Editor::MainRender()
{
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		std::wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_mainHdcBack, 10, 10, str.c_str(), static_cast<int32>(str.size()));
	}
	// Double Buffering
	::BitBlt(_mainHdc, 0, 0, _mainRect.right, _mainRect.bottom, _mainHdcBack, 0, 0, SRCCOPY);		// ��Ʈ �� : ��� ����
	::PatBlt(_mainHdcBack, 0, 0, _mainRect.right, _mainRect.bottom, BLACKNESS);
}

void Editor::PaletteRender()
{
	{
		POINT mousePos = GET_SINGLE(InputManager)->GetMousePos();
		std::wstring str = std::format(L"Mouse({0}, {1})", mousePos.x, mousePos.y);
		::TextOut(_paletteHdcBack, 10, 10, str.c_str(), static_cast<int32>(str.size()));
	}
	// Double Buffering
	::BitBlt(_paletteHdc, 0, 0, _paletteRect.right, _paletteRect.bottom, _paletteHdcBack, 0, 0, SRCCOPY);		// ��Ʈ �� : ��� ����
	::PatBlt(_paletteHdcBack, 0, 0, _paletteRect.right, _paletteRect.bottom, BLACKNESS);
}
