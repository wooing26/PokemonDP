#include "pch.h"
#include "Utils.h"

void Utils::DrawText(HDC hdc, Vec2Int pos, const wstring& str)
{
	::TextOut(hdc, pos.x, pos.y, str.c_str(), static_cast<int32>(str.size()));
}

void Utils::DrawRect(HDC hdc, Vec2Int pos, int32 w, int32 h)
{
	::Rectangle(hdc, pos.x - w / 2, pos.y - h / 2, pos.x + w / 2, pos.y + h / 2);
}

void Utils::DrawCircle(HDC hdc, Vec2Int pos, int32 radius)
{
	::Ellipse(hdc, pos.x - radius, pos.y - radius, pos.x + radius, pos.y + radius);
}

void Utils::DrawLine(HDC hdc, Vec2Int from, Vec2Int to)
{
	::MoveToEx(hdc, from.x, from.y, nullptr);
	::LineTo(hdc, to.x, to.y);
}

void Utils::DrawLineColored(HDC hdc, Vec2Int from, Vec2Int to, COLORREF color)
{
	HPEN pen = ::CreatePen(PS_SOLID, 1, color);
	HPEN oldPen = (HPEN)::SelectObject(hdc, (HGDIOBJ)pen);

	DrawLine(hdc, from, to);

	::SelectObject(hdc, (HGDIOBJ)oldPen);
	::DeleteObject((HGDIOBJ)pen);
}
