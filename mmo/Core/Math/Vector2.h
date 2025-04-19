#pragma once
#include "Core/API.h"
#include <ostream>

template<typename T>
class CORE_API Vector2
{
public:
	T x;
	T y;

	Vector2() : x(0), y(0) {}
	Vector2(T x, T y) : x(x), y(y) {}

	Vector2 operator+(const Vector2& other) const
	{
		return Vector2(x + other.x, y + other.y);
	}

	Vector2 operator-(const Vector2& other) const
	{
		return Vector2(x - other.x, y - other.y);
	}

	Vector2 operator*(T scalar) const
	{
		return Vector2(x * scalar, y * scalar);
	}

	Vector2 operator/(T scalar) const
	{
		return Vector2(x / scalar, y / scalar);
	}

	Vector2& operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}

	Vector2& operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}

	Vector2& operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2& operator/=(T scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector2& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ")";
		return os;
	}
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;