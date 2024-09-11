#pragma once
#include <windows.h>
#include <cmath>

using int8		= __int8;
using int16		= __int16;
using int32		= __int32;
using int64		= __int64;
using uint8		= unsigned __int8;
using uint16	= unsigned __int16;
using uint32	= unsigned __int32;
using uint64	= unsigned __int64;

struct Vector
{
	Vector() {}
	Vector(float x, float y) : x(x), y(y) {}
	Vector(int32 x, int32 y) : x((float)x), y((float)y) {}
	Vector(POINT pt) : x((float)pt.x), y((float)pt.y) {}

	Vector operator+(const Vector& other)
	{
		return Vector(x + other.x, y + other.y);
	}

	Vector operator-(const Vector& other)
	{
		return Vector(x - other.x, y - other.y);
	}

	Vector operator*(float value)
	{
		return Vector(x * value, y * value);
	}

	void operator+=(const Vector& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const Vector& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(float ratio)
	{
		x *= ratio;
		y *= ratio;
	}

	bool operator==(const Vector& other)
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const Vector& other)
	{
		return !((*this) == other);
	}

	float LengthSquared()
	{
		return x * x + y * y;
	}

	float Length()
	{
		return ::sqrt(LengthSquared());
	}

	void Normalize()
	{
		float length = Length();

		if (length < 0.00000001f)
			return;

		x /= length;
		y /= length;
	}

	float Dot(const Vector& other)
	{
		return x * other.x + y * other.y;
	}

	// z 방향 (크기만)
	float Cross(const Vector& other)
	{
		return x * other.y - y * other.x;
	}

	float x = 0;
	float y = 0;
};

struct VectorInt
{
	VectorInt() {}
	VectorInt(int32 x, int32 y) : x(x), y(y) {}
	VectorInt(POINT pt) : x((int32)pt.x), y((int32)pt.y) {}

	VectorInt operator+(const VectorInt& other)
	{
		return VectorInt(x + other.x, y + other.y);
	}

	VectorInt operator-(const VectorInt& other)
	{
		return VectorInt(x - other.x, y - other.y);
	}

	VectorInt operator*(float value)
	{
		return VectorInt(x * value, y * value);
	}

	void operator+=(const VectorInt& other)
	{
		x += other.x;
		y += other.y;
	}

	void operator-=(const VectorInt& other)
	{
		x -= other.x;
		y -= other.y;
	}

	void operator*=(int32 ratio)
	{
		x *= ratio;
		y *= ratio;
	}

	bool operator==(const VectorInt& other)
	{
		return x == other.x && y == other.y;
	}

	bool operator!=(const VectorInt& other)
	{
		return !((*this) == other);
	}

	int32 LengthSquared()
	{
		return x * x + y * y;
	}

	float Length()
	{
		return (float)::sqrt(LengthSquared());
	}

	void Normalize()
	{
		float length = Length();

		if (length < 0.00000001f)
			return;

		x /= length;
		y /= length;
	}

	int32 Dot(const VectorInt& other)
	{
		return x * other.x + y * other.y;
	}

	// z 방향 (크기만)
	int32 Cross(const VectorInt& other)
	{
		return x * other.y - y * other.x;
	}

	int32 x = 0;
	int32 y = 0;
};

using Pos = Vector;
using Vec2 = Vector;
using Vec2Int = VectorInt;