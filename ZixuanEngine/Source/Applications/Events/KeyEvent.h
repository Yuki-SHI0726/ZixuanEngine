#pragma once
#include "Event.h"

namespace ZE
{
/** Event for keyboard keys */
class ZE_API KeyEvent : public Event
{
public:
	KeyCode GetKeyCode() const { return m_keyCode; }

	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Keyboard) | static_cast<uint32>(EventCategory::Input))

protected:
	KeyEvent(KeyCode keyCode);

	KeyCode m_keyCode = 0;
};

/** Event for keyboard key pressed */
class ZE_API KeyPressedEvent : public KeyEvent
{
public:
	KeyPressedEvent(KeyCode keyCode, uint32 repeatCount);

	EVENT_CLASS_TYPE(KeyPressed);

	uint32 GetRepeatCount() const { return m_repeatCount; }
	virtual std::string ToString() const override final;

private:
	uint32 m_repeatCount = 0;
};

/** Event for keyboard key released */
class ZE_API KeyReleasedEvent : public KeyEvent
{
public:
	KeyReleasedEvent(KeyCode keyCode);

	EVENT_CLASS_TYPE(KeyReleased);

	virtual std::string ToString() const override final;
};

/** Event for keyboard key typed */
class ZE_API KeyTypedEvent : public KeyEvent
{
public:
	KeyTypedEvent(KeyCode keyCode);

	EVENT_CLASS_TYPE(KeyTyped);

	virtual std::string ToString() const override final;
};
}
