#pragma once
#include "Utils/Math/Vector2.h"

namespace ZE
{
class Cone
{
private:
	ZE::FVec2 m_center;
	ZE::FVec2 m_dir;
	float m_length;
	float m_angle;	// In degrees for both sides, capped from 0 to 180

public:
	Cone(const ZE::FVec2& center, float length, const ZE::FVec2& dir, float angle);

	bool IsPointInside(const ZE::FVec2& point) const;
};

inline Cone::Cone(const ZE::FVec2& center, float length, const ZE::FVec2& dir, float angle)
	: m_center(center)
	, m_length(length)
	, m_dir(dir)
	, m_angle(angle)
{
}

inline bool Cone::IsPointInside(const ZE::FVec2& point) const
{
	// If length to the point is greater than my length, it's out
	ZE::FVec2 dirToPoint = point - m_center;
	if (dirToPoint.Length() > m_length)
	{
		return false;
	}

	// Check if angle is in
	float dotResult = ZE::FVec2::Dot(dirToPoint.Normalized(), m_dir);
	float angle = RadiansToDegrees(std::acos(dotResult));
	return angle < m_angle / 2;
}
}