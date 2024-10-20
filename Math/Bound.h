#pragma once
#include "Vector2.h"
struct Bound
{

	Vector2 lowerBound;
	Vector2 upperBound;

	float Area() const
	{
		Vector2 d = upperBound - lowerBound;
		return d.x * d.y;
	}

	Bound Union(const Bound& ohter) const
	{
		Bound C;
		C.lowerBound.x = min(lowerBound.x, ohter.lowerBound.x);
		C.lowerBound.y = min(lowerBound.y, ohter.lowerBound.y);
		C.upperBound.x = max(upperBound.x, ohter.upperBound.x);
		C.upperBound.y = max(upperBound.y, ohter.upperBound.y);
		return C;
	}


	Bound(Vector2 c, Vector2 s) :
		lowerBound(c),
		upperBound(s)
	{}

	Bound(float x, float y, float width, float height) :
		lowerBound{ x - width / 2.f,y - height / 2.f },
		upperBound{ x + width / 2.f, y + height / 2.f }
	{}

	Bound()
		: upperBound{}
		, lowerBound{}
	{

	}

	bool Contains(const Vector2& point) const
	{
		return (point.x >= lowerBound.x &&
			point.x <= upperBound.x &&
			point.y >= lowerBound.y &&
			point.y <= upperBound.y);
	}

	bool Contains(const Bound& range) const
	{
		if (range.lowerBound.x >= lowerBound.x && range.upperBound.x <= upperBound.x &&
			range.lowerBound.y >= lowerBound.y && range.upperBound.y <= upperBound.y)
		{
			return true;
		}
		return false;
	}

	bool Intersects(const Bound& range) const
	{
		if (upperBound.x < range.lowerBound.x || lowerBound.x > range.upperBound.x)
			return false; // x축 안교차

		if (upperBound.y < range.lowerBound.y || lowerBound.y > range.upperBound.y)
			return false; // y축 안교차

		return true; // x, y 둘다 안교차 아님
	}

	std::wstring to_wstring() const
	{
		std::wstring ret;
		ret += L"LowerBound (";
		ret += std::to_wstring(lowerBound.x);
		ret += L", ";
		ret += std::to_wstring(lowerBound.y);
		ret += L")\n";
		ret += L"UpperBound (";
		ret += std::to_wstring(upperBound.x);
		ret += L", ";
		ret += std::to_wstring(upperBound.y);
		ret += L")\n";
		return ret;
	}
};

