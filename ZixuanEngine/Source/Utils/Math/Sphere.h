#pragma once
#include "Vector3.h"
#include "Utils/Math/Math.h"

#include <assert.h>

namespace ZE
{
//---------------------------------------------------------------------------------------------------------------------
// Custom Circle 3d class
//---------------------------------------------------------------------------------------------------------------------
template<typename Type = float>
class Sphere
{
public:
	Sphere(const Vector3<Type>& center, Type radius);
	Sphere();	

	bool IsOverlapping(const Sphere<Type>& other) const;
	float Volume() const;
	float Circumference() const;
	float Area() const;

public:
	Vector3<Type> m_center;
	Type m_radius;
	Type m_diameter;
};

template<typename Type>
inline Sphere<Type>::Sphere(const Vector3<Type>& center, Type radius)
	: m_center{ center }
	, m_radius{ radius }
	, m_diameter{ m_radius * 2 }
{
	assert(m_radius >= 0);
}

template<typename Type>
inline Sphere<Type>::Sphere()
	: m_center{ 0.0f,0.0f,0.0f }
	, m_radius{ 10.0f }
	, m_diameter{ m_radius * 2 }
{
}

//---------------------------------------------------------------------------------------------------------------------
// Check if this circle is overlapping with the other
// Formula:
//		If their centers' distance is less than this->m_radius + other.m_radius, then they are overlapping, return true
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline bool Sphere<Type>::IsOverlapping(const Sphere<Type>& other) const
{
	const f32 centerDistance = this->m_center.DistanceTo(other.m_center);
	return centerDistance < (this->m_radius + other.m_radius);
}

//---------------------------------------------------------------------------------------------------------------------
// Get Volume
// Formula:
//		Volume = (4/3) * Pi * (r^3)
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline float Sphere<Type>::Volume() const
{
	return (4 * PI * std::powf(m_radius, 3)) / 3;
}

//---------------------------------------------------------------------------------------------------------------------
// Get Circumference
// Formula:
//		Circumference = 2 * Pi * r
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline  float Sphere<Type>::Circumference() const
{
	return 2 * m_radius * PI;
}

//---------------------------------------------------------------------------------------------------------------------
// Get Area
// Formula:
//		Area = 4 * Pi * (radius^2)
//---------------------------------------------------------------------------------------------------------------------
template<typename Type>
inline float Sphere<Type>::Area() const
{
	return 4 * PI * (m_radius * m_radius);
}
}