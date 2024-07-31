#pragma once
#include <windows.h>
#include <string>
using namespace std;

class Utils
{
public:
	static void DrawText(HDC hdc, Vec2Int pos, const wstring& str);

	static void DrawRect(HDC hdc, Vec2Int pos, int32 w, int32 h);

	static void DrawCircle(HDC hdc, Vec2Int pos, int32 radius);

	static void DrawLine(HDC hdc, Vec2Int from, Vec2Int to);

	static void DrawLineColored(HDC hdc, Vec2Int from, Vec2Int to, COLORREF color);
};

