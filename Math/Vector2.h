#pragma once

#include <d2d1.h>
#include <math.h>
#include <stdlib.h>

#define FLT_EPSILON      1.192092896e-07F        // smallest such that 1.0+FLT_EPSILON != 1.0'// float.h

struct Vector3
{
	float x;
	float y;
	float z;


	Vector3(float x, float y, float z) :
		x(x),
		y(y),
		z(z)
	{
	}

	Vector3& operator =(const Vector3& origin)
	{
		this->x = origin.x;
		this->y = origin.y;
		this->z = origin.z;
		return *this;
	}

	Vector3 CrossProduct(Vector3 other)
	{
		return Vector3(this->y * other.z - this->z * other.y,
			this->z * other.x - this->x * other.z,
			this->x * other.y - this->y * other.x);
	}
};




struct Vector2
{
	float x;
	float y;


	Vector2() :
		x(0.f),
		y(0.f)
	{

	}

	Vector2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	Vector2(const Vector2& origin)
	{
		this->x = origin.x;
		this->y = origin.y;
	}

	Vector2(Vector2&& origin) noexcept
	{
		this->x = origin.x;
		this->y = origin.y;
	}

	Vector2(const D2D1_POINT_2F& origin)
	{
		this->x = origin.x;
		this->y = origin.y;
	}

	float Length() const
	{
		return sqrtf(x * x + y * y);
	}

	Vector2 Normalize()
	{

		float length = Length();
		if (length < FLT_EPSILON)
		{
			return Vector2(0.f, 0.f);
		}
		float invLength = 1.0f / length;
		x *= invLength;
		y *= invLength;

		return Vector2(x, y);
	}

	Vector2(D2D1_POINT_2F& origin)
	{
		this->x = origin.x;
		this->y = origin.y;
	}


	// x 스케일 사용해서 계산
	Vector2 GetWidthVector(float rotation)
	{
		Vector2 ret;
		ret.x = x / 2.f * (float)cos(rotation);
		ret.y = x / 2.f * (float)sin(rotation);
		return ret;
	}

	// y 스케일 사용해서 계산
	Vector2 GetHeightVector(float rotation)
	{
		Vector2 ret;
		ret.x = y / 2.f * (float)-sin(rotation);
		ret.y = y / 2.f * (float)cos(rotation);
		return ret;
	}


	Vector2 operator+ (Vector2 other)
	{
		Vector2 ret;
		ret.x = this->x + other.x;
		ret.y = this->y + other.y;
		return ret;
	}

	void operator-=(const Vector2& other)
	{
		this->x -= other.x;
		this->y -= other.y;
	}

	void operator+=(const Vector2& other)
	{
		this->x += other.x;
		this->y += other.y;
	}

	Vector2 operator* (Vector2 other)
	{
		Vector2 ret;
		ret.x = this->x * other.x;
		ret.y = this->y * other.y;
		return ret;
	}

	Vector2 operator* (D2D1::Matrix3x2F other)
	{

		D2D1_POINT_2F tempPoint = { this->x, this->y };
		tempPoint = tempPoint * other;
		Vector2 ret = { tempPoint.x, tempPoint.y };
		return ret;
	}


	Vector2 operator* (float scalar) const
	{
		Vector2 ret;
		ret.x = this->x * scalar;
		ret.y = this->y * scalar;
		return ret;
	}
	Vector2 operator/ (float scalar) const
	{
		Vector2 ret;
		ret.x = this->x / scalar;
		ret.y = this->y / scalar;
		return ret;
	}

	Vector2 operator-()const
	{
		return Vector2(-x, -y);
	}
	// 	Vector2(int x, int y)
	// 	{
	// 		this->x = x;
	// 		this->y = y;
	// 	}

	bool operator==(Vector2 other)
	{
		return (fabsf(this->x - other.x) <= 0.00001 && fabsf(this->y - other.y) <= 0.00001);

	}

	Vector2 GetDistanceVector(Vector2 other)
	{
		float x = this->x - other.x;
		float y = this->y - other.y;
		return Vector2(x, y);
	}

	float AbsDotProduct(Vector2 other)
	{
		return (float)fabsf(this->x * other.x + this->y * other.y);
	}

	float Dot(const Vector2& other) const
	{
		return (float)(this->x * other.x + this->y * other.y);
	}


	float length()
	{
		return (float)sqrt(pow(this->x, 2) + pow(this->y, 2));
	}

	float Cross(const Vector2& other)
	{
		return (this->x * other.y - other.x * this->y);
	}

	Vector2& operator =(const D2D1_POINT_2F& origin)
	{
		this->x = origin.x;
		this->y = origin.y;
		return *this;
	}

	Vector2& operator =(const Vector2& origin)
	{
		this->x = origin.x;
		this->y = origin.y;
		return *this;
	}

	static Vector2 X() { return { 1.f, 0.f }; }
	static Vector2 Y() { return { 0.f, 1.f }; }
	// 2023.08.03 김동일
	// Collider OBB 충돌처리에서 가로세로 벡터를 구하기 위한 함수
	static Vector2 RotateRadian(const Vector2& _point, const Vector2& _center, float _radian);
};




inline Vector2 operator- (const Vector2& a, const Vector2& b)
{
	return Vector2(a.x - b.x, a.y - b.y);
}

inline Vector2 operator* (float scalar, Vector2 a)
{
	Vector2 ret;
	ret.x = a.x * scalar;
	ret.y = a.y * scalar;
	return ret;
}

inline float Cross(const Vector2& a, const Vector2& b)
{
	return a.x * b.y - a.y * b.x;
}

inline Vector2 Cross(const Vector2& a, float s)
{
	return Vector2(s * a.y, -s * a.x);
}

inline Vector2 Cross(float s, const Vector2& a)
{
	return Vector2(-s * a.y, s * a.x);
}

inline float Dot(const Vector2& a, const Vector2& b)
{
	return (float)(a.x * b.x + a.y * b.y);
}

inline Vector2 MulT(const D2D1::Matrix3x2F& A, const Vector2& v)
{
	Vector2 col1 = Vector2(A._11, A._21);
	Vector2 col2 = Vector2(A._12, A._22);
	return Vector2(col1.Dot(v), col2.Dot(v));
}

// triple product (A x B) x C = B(A.dot(C)) - A(B.dot(C))
inline Vector2 TripleProduct(const Vector2& a, const Vector2& b, const Vector2& c)
{
	return b * (a.Dot(c)) - a * (b.Dot(c));
}

inline Vector2 Vector2::RotateRadian(const Vector2 & point, const Vector2 & center, float radian)
{
	float cosTheta = static_cast<float>(cos(radian));
	float sinTheta = static_cast<float>(sin(radian));

	Vector2 relative = point - center;
	Vector2 rotated{};
	rotated.x = center.x + relative.x * cosTheta - relative.y * sinTheta;
	rotated.y = center.y + relative.x * sinTheta + relative.y * cosTheta;

	return rotated;
}