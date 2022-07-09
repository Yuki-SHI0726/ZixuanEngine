#include "zepch.h"

#include "MouseEvent.h"

#include <sstream>

namespace ZE
{

MouseMovedEvent::MouseMovedEvent(f32 x, f32 y)
	: m_mouseX(x)
	, m_mouseY(y)
{
}

std::string MouseMovedEvent::ToString() const
{
	std::stringstream ss;
	ss << "MouseMovedEvent: " << m_mouseX << ", " << m_mouseY;
	return ss.str();
}

MouseScrolledEvent::MouseScrolledEvent(f32 xOffset, f32 yOffset)
	: m_xOffset(xOffset)
	, m_yOffset(yOffset)
{
}

std::string MouseScrolledEvent::ToString() const
{
	std::stringstream ss;
	ss << "MouseScrolledEvent: " << m_xOffset << ", " << m_yOffset;
	return ss.str();
}

MouseButtonEvent::MouseButtonEvent(KeyCode button)
	: m_button(button)
{
}

MouseButtonPressedEvent::MouseButtonPressedEvent(KeyCode button)
	: MouseButtonEvent(button)
{
}

std::string MouseButtonPressedEvent::ToString() const
{
	std::stringstream ss;
	ss << "MouseButtonPressedEvent: " << m_button;
	return ss.str();
}

MouseButtonReleasedEvent::MouseButtonReleasedEvent(KeyCode button)
	: MouseButtonEvent(button)
{
}

std::string MouseButtonReleasedEvent::ToString() const
{
	std::stringstream ss;
	ss << "MouseButtonReleasedEvent: " << m_button;
	return ss.str();
}


}