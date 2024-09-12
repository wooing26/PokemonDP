#pragma once
#include <windows.h>
#include <string>

class Utils
{
public:
	static void DrawText(HDC hdc, Vec2Int pos, const std::wstring& str);
	static void DrawTextSize(HDC hdc, Vec2Int pos, int32 size, const std::wstring& str);
	static void DrawTextRect(HDC hdc, RECT rect, const std::wstring& str);

	static void DrawRect(HDC hdc, Vec2Int pos, int32 w, int32 h);

	static void DrawCircle(HDC hdc, Vec2Int pos, int32 radius);

	static void DrawLine(HDC hdc, Vec2Int from, Vec2Int to);

	static void DrawLineColored(HDC hdc, Vec2Int from, Vec2Int to, COLORREF color);
};

