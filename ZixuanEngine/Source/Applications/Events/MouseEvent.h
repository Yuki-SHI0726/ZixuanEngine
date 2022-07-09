#pragma once
#include "Event.h"

namespace ZE
{
/** Event when mouse moved */
class ZE_API MouseMovedEvent : public Event
{
public:
	MouseMovedEvent(f32 x, f32 y);

	EVENT_CLASS_TYPE(MouseMoved)
	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Mouse) | static_cast<uint32>(EventCategory::Input))

	f32 GetX() const { return m_mouseX; }
	f32 GetY() const { return m_mouseY; }
	virtual std::string ToString() const override final;

private:
	f32 m_mouseX = 0.0f; 
	f32 m_mouseY = 0.0f; 
};

/** Event when mouse wheel button scrolled */
class ZE_API MouseScrolledEvent : public Event
{
public:
	MouseScrolledEvent(f32 xOffset, f32 yOffset);

	EVENT_CLASS_TYPE(MouseScrolled)
	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Mouse) | static_cast<uint32>(EventCategory::Input))

	f32 GetX() const { return m_xOffset; }
	f32 GetY() const { return m_yOffset; }
	virtual std::string ToString() const override final;

private:
	f32 m_xOffset = 0.0f;
	f32 m_yOffset = 0.0f;
};

/** Event when mouse button triggered */
class ZE_API MouseButtonEvent : public Event
{
public:
	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Mouse) | static_cast<uint32>(EventCategory::Input))
	
	KeyCode GetMouseButton() const { return m_button; }

protected:
	MouseButtonEvent(KeyCode button);

protected:
	KeyCode m_button;
};

/** Event when mouse button pressed */
class ZE_API MouseButtonPressedEvent : public MouseButtonEvent
{
public:
	MouseButtonPressedEvent(KeyCode button);

	EVENT_CLASS_TYPE(MouseButtonPressed)

	virtual std::string ToString() const override final;
};

/** Event when mouse button released */
class ZE_API MouseButtonReleasedEvent : public MouseButtonEvent
{
public:
	MouseButtonReleasedEvent(KeyCode button);

	EVENT_CLASS_TYPE(MouseButtonReleased)

	virtual std::string ToString() const override final;
};
}
