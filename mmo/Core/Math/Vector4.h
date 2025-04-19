#pragma once
#include "Core/API.h"
#include <ostream>

template<typename T>
class CORE_API Vector4
{
public:
	T x;
	T y;
	T z;
	T w;

	Vector4() : x(0), y(0), z(0), w(0) {}
	Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}

	Vector4 operator+(const Vector4& other) const
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}

	Vector4 operator-(const Vector4& other) const
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}

	Vector4 operator*(T scalar) const
	{
		return Vector4(x * scalar, y * scalar, z * scalar, w * scalar);
	}

	Vector4 operator/(T scalar) const
	{
		return Vector4(x / scalar, y / scalar, z / scalar, w / scalar);
	}

	Vector4& operator+=(const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}

	Vector4& operator-=(const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}

	Vector4& operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;
		w *= scalar;
		return *this;
	}

	Vector4& operator/=(T scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;
		w /= scalar;
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const Vector4& vec)
	{
		os << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")";
		return os;
	}
};

typedef Vector4<float> Vector4f;
typedef Vector4<int> Vector4i;