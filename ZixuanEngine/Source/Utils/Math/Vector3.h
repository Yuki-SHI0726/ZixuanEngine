#pragma once
#include "Utils/Typedefs.h"

#include <assert.h>
#include <iostream>
#include <math.h>
#include <algorithm>

namespace ZE
{
template<typename Type>
class Vector3
{
public:
	Type x;
	Type y;
	Type z;

public:
	Vector3();
	Vector3(Type inX, Type inY, Type inZ);

	/** @return		The length of this vector */
	f32 Length() const;

	/** @return		The squared length of this vector */
	f32 SquaredLength() const;

	/** @return		The dot product with the other vector */
	f32 Dot(const Vector3<Type>& other) const;

	/** @return		The dot product of two vectors */
	static f32 Dot(const Vector3<Type>& a, const Vector3<Type>& b);

	/** @return		The cross product with the other vector */
	Vector3<Type> Cross(const Vector3<Type>& other) const;
	
	/** @return		The cross product of two vectors */
	static Vector3<Type> Cross(const Vector3<Type>& a, const Vector3<Type>& b);

	/** Normalize this vector to the length of 1 */
	void Normalize();

	/** @return		Normalized copy of this vector */
	Vector3 Normalized();

	/** @return		Normalized copy of this vector */
	static Vector3 Normalized(const Vector3<Type>& vector);

	/** @return		Distance from this vector to another */
	f32 DistanceTo(const Vector3<Type>& other) const;

	/** @return		Squared Distance from this vector to another */
	float DistanceToSquared(const Vector3<Type>& other) const;

	/** Clamps this vector from low to high */
	static Vector3 Clamp(const Vector3<Type>& val, const Vector3<Type>& low, const Vector3<Type>& high);

	/** Rotates this vector counter-clockwisely through Z-axis */
	void RotateZCCW(f32 angleRadians);

	/** Rotates this vector clockwisely through Z-axis */
	void RotateZCW(f32 angleRadians);

	/** @return		A copy with all negative components of this vector */
	Vector3 operator-() const;

	// Operator with value
	Vector3 operator+(Type num) const;
	Vector3 operator-(Type num) const;
	Vector3 operator*(Type num) const;
	Vector3 operator/(Type num) const;

	// Operator with another vector
	Vector3 operator+(const Vector3<Type>& other) const;
	Vector3 operator-(const Vector3<Type>& other) const;
	Vector3 operator*(const Vector3<Type>& other) const;
	Vector3 operator/(const Vector3<Type>& other) const;
	
	// Operator= with another vector
	void operator+=(const Vector3<Type>& other);
	void operator-=(const Vector3<Type>& other);
	void operator*=(const Vector3<Type>& other);
	void operator/=(const Vector3<Type>& other);

	// Operator= with value
	void operator+=(Type num);
	void operator-=(Type num);
	void operator*=(Type num);
	void operator/=(Type num);
};

template<typename Type>
inline Vector3<Type>::Vector3()
	: x(static_cast<Type>(0))
	, y(static_cast<Type>(0))
	, z(static_cast<Type>(0))
{
}

template<typename Type>
inline Vector3<Type>::Vector3(Type inX, Type inY, Type inZ)
	: x(inX)
	, y(inY)
	, z(inZ)
{
}

template<typename Type>
inline float Vector3<Type>::Length() const
{
	return sqrtf(SquaredLength());
}

template<typename Type>
inline f32 Vector3<Type>::SquaredLength() const
{
	return static_cast<f32>((x * x) + (y * y) + (z * z));
}

template<typename Type>
inline f32 Vector3<Type>::Dot(const Vector3& other) const
{
	return static_cast<f32>((this->x * other.x) +
							  (this->y * other.y) +
							  (this->z * other.z));
}

template<typename Type>
inline f32 Vector3<Type>::Dot(const Vector3& x, const Vector3& right)
{
	return static_cast<f32>((x.x * right.x) +
							  (x.y * right.y) +
							  (x.z * right.z));
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::Cross(const Vector3<Type>& right) const
{
	const f32 x = (this->y * right.z) - (this->z * right.y);
	const f32 y = (this->z * right.x) - (this->x * right.z);
	const f32 z = (this->x * right.y) - (this->y * right.x);
	return Vector3{ x,y,z };
}

template<typename Type>
inline  Vector3<Type> Vector3<Type>::Cross(const Vector3<Type>& x, const Vector3<Type>& right)
{
	const f32 x = (x.y * right.z) - (x.z * right.y);
	const f32 y = (x.z * right.x) - (x.x * right.z);
	const f32 z = (x.x * right.y) - (x.y * right.x);
	return Vector3{ x, y ,z };
}

template<typename Type>
inline void Vector3<Type>::Normalize()
{
	if (x == static_cast<Type>(0) && y == static_cast<Type>(0) && z == static_cast<Type>(0))
	{
		return;
	}

	const f32 length = Length();
	x /= length;
	y /= length;
	z /= length;
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::Normalized()
{
	Vector3<Type> copy = *this;
	copy.Normalize();
	return copy;
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::Normalized(const Vector3<Type>& vector)
{
	Vector3<Type> copy = vector;
	copy.Normalize();
	return copy;
}

template<typename Type>
inline f32 Vector3<Type>::DistanceTo(const Vector3<Type>& other) const
{
	return sqrtf(DistanceToSquared(other));
}

template<typename Type>
inline f32 Vector3<Type>::DistanceToSquared(const Vector3<Type>& other) const
{
	const f32 dx = (this->x - other.x) * (this->x - other.x);	// (x1 - x2)^2
	const f32 dy = (this->y - other.y) * (this->y - other.y);	// (y1 - y2)^2
	const f32 dz = (this->z - other.z) * (this->z - other.z);	// (y1 - y2)^2
	return (dx + dy + dz);
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::Clamp(const Vector3<Type>& val, const Vector3<Type>& low, const Vector3<Type>& high)
{
	if (val.Length() < low.Length())
	{
		return low.Length();
	}
	else if (val.Length() > high.Length())
	{
		return high.Length();
	}
	else
	{
		return val.Length();
	}
}

template<typename Type>
inline void Vector3<Type>::RotateZCCW(f32 angleRadians)
{
	Vector3<Type> temp = *this;
	x = (temp.x * std::cos(angleRadians)) - (temp.y * std::sin(angleRadians));
	y = (temp.x * std::sin(angleRadians)) + (temp.y * std::cos(angleRadians));
}

template<typename Type>
inline void Vector3<Type>::RotateZCW(f32 angleRadians)
{
	Vector3 temp = *this;
	x = (temp.x * std::cos(angleRadians)) + (temp.y * std::sin(angleRadians));
	y = (-temp.x * std::sin(angleRadians)) + (temp.y * std::cos(angleRadians));
}

template<typename Type>
inline void Vector3<Type>::operator+=(const Vector3<Type>& other)
{
	*this = *this + other;
}

template<typename Type>
inline void Vector3<Type>::operator-=(const Vector3<Type>& other)
{
	*this = *this - other;
}

template<typename Type>
inline void Vector3<Type>::operator*=(const Vector3<Type>& other)
{
	*this = *this * other;
}

template<typename Type>
inline void Vector3<Type>::operator/=(const Vector3<Type>& other)
{
	*this = *this / other;
}

template<typename Type>
inline void Vector3<Type>::operator+=(Type num)
{
	*this = *this + num;
}

template<typename Type>
inline void Vector3<Type>::operator-=(Type num)
{
	*this = *this - num;
}

template<typename Type>
inline void Vector3<Type>::operator*=(Type num)
{
	*this = *this * num;
}

template<typename Type>
inline void Vector3<Type>::operator/=(Type num)
{
	*this = *this / num;
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::operator+(const Vector3<Type>& other) const
{
	return Vector3<Type>
	{
		this->x + other.x,
			this->y + other.y,
			this->z + other.z
	};
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::operator-(const Vector3<Type>& other) const
{
	return Vector3<Type>
	{
		this->x - other.x,
			this->y - other.y,
			this->z - other.z
	};
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::operator*(const Vector3<Type>& other) const
{
	return Vector3<Type>
	{
		this->x * other.x,
			this->y * other.y,
			this->z * other.z
	};
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::operator/(const Vector3<Type>& other) const
{
	return Vector3<Type>
	{
		this->x / other.x,
			this->y / other.y,
			this->z / other.z
	};
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::operator+(Type num) const
{
	return Vector3<Type>
	{
		this->x + num,
			this->y + num,
			this->z + num
	};
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::operator-(Type num) const
{
	return Vector3
	{
		this->x - num,
			this->y - num,
			this->z - num
	};
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::operator*(Type num) const
{
	return Vector3
	{
		this->x * num,
			this->y * num,
			this->z * num
	};
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::operator/(Type num) const
{
	return Vector3
	{
		this->x / num,
			this->y / num,
			this->z / num
	};
}

template<typename Type>
Vector3<Type> operator+(float num, const Vector3<Type>& other)
{
	return other + num;
}

template<typename Type>
Vector3<Type> operator-(float num, const Vector3<Type>& other)
{
	return other - num;
}

template<typename Type>
Vector3<Type> operator*(float num, const Vector3<Type>& other)
{
	return other * num;
}

template<typename Type>
inline Vector3<Type> operator/(float num, const Vector3<Type>& other)
{
	return other / num;
}

template<typename Type>
inline Vector3<Type> Vector3<Type>::operator-() const
{
	return Vector3{ -x, -y, -z };
}

// Alias
using IVec3 = Vector3<int32>;
using FVec3 = Vector3<f32>;
}