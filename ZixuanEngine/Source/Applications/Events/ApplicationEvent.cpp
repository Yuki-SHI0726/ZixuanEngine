#include "zepch.h"

#include "ApplicationEvent.h"

namespace ZE
{
WindowResizedEvent::WindowResizedEvent(uint32 width, uint32 height)
	: m_width(width)
	, m_height(height)
{
}

std::string WindowResizedEvent::ToString() const
{
	std::stringstream ss;
	ss << "WindowResizeEvent: " << m_width << ", " << m_height;
	return ss.str();
}
}