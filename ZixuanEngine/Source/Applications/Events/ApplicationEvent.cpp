#include "zepch.h"

#include "ApplicationEvent.h"

namespace ZE
{
WindowResizeEvent::WindowResizeEvent(uint32 width, uint32 height)
	: m_width(width)
	, m_height(height)
{
}

std::string WindowResizeEvent::ToString() const
{
	std::stringstream ss;
	ss << "WindowResizeEvent: " << m_width << ", " << m_height;
	return ss.str();
}
}