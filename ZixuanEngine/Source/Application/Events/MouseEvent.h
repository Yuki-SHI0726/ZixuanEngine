#pragma once
#include "Event.h"

namespace ZE
{
class ZE_API MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(f32 x, f32 y);

	f32 GetX() const { return m_mouseX; }
	f32 GetY() const { return m_mouseY; }

	virtual std::string ToString() const override final;

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Mouse) | static_cast<uint32>(EventCategory::Input))

private:
	f32 m_mouseX = 0.0f; 
	f32 m_mouseY = 0.0f; 
};

class ZE_API MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(f32 xOffset, f32 yOffset);

	f32 GetX() const { return m_xOffset; }
	f32 GetY() const { return m_yOffset; }

	virtual std::string ToString() const override final;

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Mouse) | static_cast<uint32>(EventCategory::Input))

private:
	f32 m_xOffset = 0.0f;
	f32 m_yOffset = 0.0f;
};

class ZE_API MouseButtonEvent : public Event
{
public:
	KeyCode GetMouseButton() const { return m_button; }

	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Mouse) | static_cast<uint32>(EventCategory::Input))

protected:
	MouseButtonEvent(KeyCode button);

	KeyCode m_button;
};

class ZE_API MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(KeyCode button);

	virtual std::string ToString() const override final;

	EVENT_CLASS_TYPE(MouseButtonPressed)
};

class ZE_API MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(KeyCode button);

	virtual std::string ToString() const override final;

	EVENT_CLASS_TYPE(MouseButtonReleased)
};
}
