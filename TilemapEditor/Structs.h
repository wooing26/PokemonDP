#pragma once
#include <Windows.h>
#include <cmath>

struct Vector
{
	Vector() {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(int32 x, int32 y) : x(x), y(y) {}
	Vector(POINT pt) : x((float)pt.x), y((float)pt.y) {}


	float x = 0;
	float y = 0;
};