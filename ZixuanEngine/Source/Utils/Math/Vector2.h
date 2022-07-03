#pragma once

#include "Math.h"

#include <cmath>
#include <iostream>
#include <assert.h>
#include <string>

namespace ZE
{
	template<typename Type>
	class Rect;

template<typename Type = float>
class Vector2
{
public:
	Type x;
	Type y;

	// Members
	constexpr Vector2() = default;
	constexpr Vector2(Type _x, Type _y);
	constexpr Vector2(const Vector2&) = default;
	constexpr Vector2& operator=(const Vector2&) = default;
	~Vector2() = default;
	template<typename U> constexpr Vector2<Type>(const Vector2<U>& other);

	// API
	bool IsInside(const Rect<Type>& rect) const;
	float DistanceTo(Vector2<Type> other) const;
	float DistanceToSquared(Vector2<Type> other) const;
	float Length() const;
	float SquaredLength() const;
	float Dot(Vector2<Type> right) const;
	static float Dot(Vector2<Type> x, Vector2<Type> right);
	void Normalize();
	static Vector2<Type> Normalized(Vector2<Type> vector);
	Vector2<Type> Normalized();
	void RotateCounterClockwise(float angleRadians);
	void RotateClockwise(float angleRadians);
	static Vector2<Type> FromAngle(Type angle) { return { std::cos(angle), std::sin(angle) }; }
	void ClampMagnitude(Type maxLength)
	{
		float oldLength = Length();

		if (IsExtremelyClose(oldLength, static_cast<Type>(0)))
		{
			return;
		}

		float length = std::clamp(oldLength, static_cast<Type>(0), maxLength);

		*this /= oldLength;
		*this *= length;
	}
	std::string ToString() const;

	// Operators value
	Vector2<Type> operator-(Type value) const;
	Vector2<Type> operator+(Type value) const;
	Vector2<Type> operator*(Type value) const;
	Vector2<Type> operator/(Type value) const;
	Vector2<Type> operator+=(Type value);
	Vector2<Type> operator-=(Type value);
	Vector2<Type> operator*=(Type value);
	Vector2<Type> operator/=(Type value);

	// Other vector operator
	Vector2<Type> operator+(const Vector2<Type>& right) const;
	Vector2<Type> operator-(const Vector2<Type>& right) const;
	Vector2<Type> operator*(const Vector2<Type>& right) const;
	Vector2<Type> operator/(const Vector2<Type>& right) const;
	Vector2<Type> operator+=(const Vector2<Type>& right);
	Vector2<Type> operator-=(const Vector2<Type>& right);
	Vector2<Type> operator*=(const Vector2<Type>& right);
	Vector2<Type> operator/=(const Vector2<Type>& right);
	bool operator== (const Vector2<Type>& other);

	// Friends
	friend std::ostream& operator<<(std::ostream& Stream, const Vector2& Vector) { Stream << "Vector2{" << Roundedf(Vector.x) << "," << Roundedf(Vector.y) << "}";		return Stream; }

private:
	float static Roundedf(float component) { return std::roundf(component * 1000.f) * 0.001f; }
};

//---------------------------------------------------------------------------------------
// Ctors
//---------------------------------------------------------------------------------------
template<typename Type>
inline constexpr Vector2<Type>::Vector2(Type _x, Type _y)
	: x(_x)
	, y(_y)
{
}

//---------------------------------------------------------------------------------------
// Ctor for handling type conflicts. i.e. FVec2 floatVec2 = IVec2(lhs);
//---------------------------------------------------------------------------------------
template<typename Type>
template<typename U>
inline constexpr Vector2<Type>::Vector2(const Vector2<U>& other)
	: x(static_cast<Type>(other.x))
	, y(static_cast<Type>(other.y))
{
}
//---------------------------------------------------------------------------------------
// Determines whether a point is inside a rectangle. Return true if the point is inside rect
//---------------------------------------------------------------------------------------
template<typename Type>
inline bool Vector2<Type>::IsInside(const Rect<Type>& rect) const
{
	return rect.Contains(*this);
}

//---------------------------------------------------------------------------------------------------------------------
// Operator << overloading
// Formula:
//		Distance = square root((x1 - x2)^2 + (y1 - y2)^2)
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline float Vector2<Type>::DistanceTo(Vector2<Type> other) const
{
	return std::sqrtf(DistanceToSquared(other));
}

//---------------------------------------------------------------------------------------------------------------------
// Get squared distance to other vector
// Formula:
//		Distance = (x1 - x2)^2 + (y1 - y2)^2
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline float Vector2<Type>::DistanceToSquared(Vector2<Type> other) const
{
	float dx = (this->x - other.x) * (this->x - other.x);	// (x1 - x2)^2
	float dy = (this->y - other.y) * (this->y - other.y);	// (y1 - y2)^2
	return (dx + dy);
}

//---------------------------------------------------------------------------------------------------------------------
// Returns the distance from 0,0,0 to *this.
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline float Vector2<Type>::Length() const
{
	return std::sqrtf(SquaredLength());
}

//---------------------------------------------------------------------------------------------------------------------
// Returns the square of the distance from 0, 0, 0 to * this.
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline float Vector2<Type>::SquaredLength() const
{
	return static_cast<float>((x * x) + (y * y));
}

//---------------------------------------------------------------------------------------------------------------------
// a · b = | a | × | b | × cos(θ)
// θ = acos(a·b), where a and b should be normalized before dot calculation
// 
// Where:
// | a | is the magnitude(length) of vector a
// | b | is the magnitude(length) of vector b
// θ is the angle between a and b
//
// Or
//
// a · b = ax × bx + ay × by
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline float Vector2<Type>::Dot(Vector2<Type> right) const
{
	return static_cast<float>((this->x * right.x) +
		(this->y * right.y));
}
template<typename Type>
inline float Vector2<Type>::Dot(Vector2<Type> x, Vector2<Type> right)
{
	return static_cast<float>((x.x * right.x) +
		(x.y * right.y));
}

//---------------------------------------------------------------------------------------------------------------------
// Returns the dot product of *this and right.
// The dot product is a float value equal to the magnitudes of the two vectors multiplied together and then multiplied by the cosine of the angle between them.
// a · b = |a||b| × cos(θ)
// Where:
// | a | is the magnitude(length) of vector a
// | b | is the magnitude(length) of vector b
// θ is the angle between a and b
//
// θ = acos([AB]/[|A||B|])
// θ = acos(A·B), (AB) needs to be normalized before dot operation
//
// Or
//
// a · b = ax × bx + ay × by
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline void Vector2<Type>::Normalize()
{
	if (x == 0.0f && y == 0.0f)
		return;

	float length = Length();
	x /= length;
	y /= length;
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::Normalized(Vector2<Type> vector)
{
	Vector2<Type> copy = vector;
	copy.Normalize();
	return copy;
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::Normalized()
{
	Vector2<Type> copy = *this;
	copy.Normalize();
	return copy;
}

//---------------------------------------------------------------------------------------------------------------------
// Rotate vector CCW
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline void Vector2<Type>::RotateCounterClockwise(float angleRadians)
{
	Vector2<Type> copy = *this;
	x = (copy.x * std::cos(angleRadians)) - (copy.y * std::sin(angleRadians));
	y = (copy.x * std::sin(angleRadians)) + (copy.y * std::cos(angleRadians));
}

//---------------------------------------------------------------------------------------------------------------------
// Rotate vector CW
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline void Vector2<Type>::RotateClockwise(float angleRadians)
{
	Vector2<Type> temp = *this;
	x = (temp.x * std::cos(angleRadians)) + (temp.y * std::sin(angleRadians));
	y = (-temp.x * std::sin(angleRadians)) + (temp.y * std::cos(angleRadians));
}

//---------------------------------------------------------------------------------------------------------------------\
// Returns a string contains vector data
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline std::string Vector2<Type>::ToString() const
{
	std::string vecStr;
	vecStr += std::to_string(x);
	vecStr += ", ";
	vecStr += std::to_string(y);
	return vecStr;
}

//---------------------------------------------------------------------------------------------------------------------
// Operator values
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator+(Type value) const
{
	return Vector2<Type>
	{
		this->x + value,
			this->y + value,
	};
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator-(Type value) const
{
	return Vector2<Type>
	{
		this->x - value,
			this->y - value,
	};
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator*(Type value) const
{
	return Vector2<Type>
	{
		this->x* value,
			this->y* value,
	};
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator/(Type value) const
{
	return Vector2<Type>
	{
		this->x / value,
			this->y / value,
	};
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator+=(Type val)
{
	*this = *this + val;
	return *this;
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator-=(Type val)
{
	*this = *this - val;
	return *this;
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator*=(Type val)
{
	*this = *this * val;
	return *this;
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator/=(Type val)
{
	*this = *this / val;
	return *this;
}
template <typename Type>
inline Vector2<Type> operator+(Type lhs, const Vector2<Type>& rhs)
{
	return rhs + lhs;
}
template <typename Type>
inline Vector2<Type> operator-(Type lhs, const Vector2<Type>& rhs)
{
	return rhs - lhs;
}
template <typename Type>
inline Vector2<Type> operator*(Type lhs, const Vector2<Type>& rhs)
{
	return rhs * lhs;
}
template <typename Type>
inline Vector2<Type> operator/(Type lhs, const Vector2<Type>& rhs)
{
	return rhs / lhs;
}
//---------------------------------------------------------------------------------------------------------------------
// Vector other operator
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator+(const Vector2<Type>& right) const
{
	return Vector2<Type>
	{
		this->x + right.x,
			this->y + right.y,
	};
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator-(const Vector2<Type>& right) const
{
	return Vector2<Type>
	{
		this->x - right.x,
			this->y - right.y,
	};
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator*(const Vector2<Type>& right) const
{
	return Vector2<Type>
	{
		this->x * right.x,
			this->y * right.y,
	};
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator/(const Vector2<Type>& right) const
{
	return Vector2<Type>
	{
		this->x / right.x,
			this->y / right.y,
	};
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator+=(const Vector2<Type>& right)
{
	*this = *this + right;
	return *this;
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator-=(const Vector2<Type>& right)
{
	*this = *this - right;
	return *this;
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator*=(const Vector2<Type>& right)
{
	*this = *this * right;
	return *this;
}
template<typename Type>
inline bool Vector2<Type>::operator==(const Vector2<Type>& right)
{
	if constexpr (std::is_floating_point_v<Type>)
		return (IsExtremelyClose(x, right.x)) && (IsExtremelyClose(y, right.y));
	else
		return (x == right.x) && (y == right.y);
}
template<typename Type>
inline Vector2<Type> Vector2<Type>::operator/=(const Vector2<Type>& right)
{
	*this = *this / right;
	return *this;
}
template <typename Type>
inline Vector2<Type> operator+(const Vector2<Type>& lhs, const Vector2<Type>& rhs)
{
	return rhs + lhs;
}
template <typename Type>
inline Vector2<Type> operator-(const Vector2<Type>& lhs, const Vector2<Type>& rhs)
{
	return rhs - lhs;
}
template <typename Type>
inline Vector2<Type> operator*(const Vector2<Type>& lhs, const Vector2<Type>& rhs)
{
	return rhs * lhs;
}
template <typename Type>
inline Vector2<Type> operator/(const Vector2<Type>& lhs, const Vector2<Type>& rhs)
{
	return rhs / lhs;
}
template <typename Type>
inline Vector2<Type> operator-(const Vector2<Type>& other)
{
	return Vector2<Type>(-other.x, -other.y);
}
// Alias
using IVec2 = Vector2<int>;
using FVec2 = Vector2<float>;
}