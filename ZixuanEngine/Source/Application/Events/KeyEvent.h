#pragma once
#include "Event.h"

namespace ZE
{
class ZE_API KeyEvent : public Event
{
public:
	KeyCode GetKeyCode() const { return m_keyCode; }

	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Keyboard) | static_cast<uint32>(EventCategory::Input))

protected:
	KeyEvent(KeyCode keyCode);

	KeyCode m_keyCode = 0;
};

class ZE_API KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(KeyCode keyCode, uint32 repeatCount);

	uint32 GetRepeatCount() const { return m_repeatCount; }
	virtual std::string ToString() const override final;

	EVENT_CLASS_TYPE(KeyPressed);

private:
	uint32 m_repeatCount = 0;
};

class ZE_API KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(KeyCode keyCode);

	virtual std::string ToString() const override final;

	EVENT_CLASS_TYPE(KeyReleased);
};
}
