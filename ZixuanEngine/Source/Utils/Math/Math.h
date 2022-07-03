#pragma once

#include <algorithm>
#include <cmath>

#undef min

namespace ZE
{

#define PI 3.14159f	// Pi value

//--------------------------------------------------------------------------------------------
// Convert a radians to degrees 
// Degrees = Radians * 180 / Pi
//--------------------------------------------------------------------------------------------
constexpr float RadiansToDegrees(float radians)
{
	return (radians * 180 / PI);
}

//--------------------------------------------------------------------------------------------
// Convert a degrees to radians 
// Radians = Degrees * Pi / 180
//--------------------------------------------------------------------------------------------
constexpr float DegreesToRadius(float degrees)
{
	return (degrees * PI / 180);
}

//--------------------------------------------------------------------------------------------
// Constexpr Abs function
//--------------------------------------------------------------------------------------------
template <typename Type>
Type constexpr Abs(Type x)
{
    return x > 0
        ? x
        : -x;
}

//--------------------------------------------------------------------------------------------
// Checks if two floating point values are nearly equal
//--------------------------------------------------------------------------------------------
template <typename Type>
bool constexpr IsExtremelyClose(Type first, Type second, Type epsilon = static_cast<Type>(0.001))
{
    return Abs(first - second) < epsilon;
}

//--------------------------------------------------------------------------------------------
// Returns the min of two angles
//--------------------------------------------------------------------------------------------
constexpr float AngleDiff(float first, float second)
{
    return std::min(std::abs(second - first), 2 * PI - std::abs(second - first));
}

}
