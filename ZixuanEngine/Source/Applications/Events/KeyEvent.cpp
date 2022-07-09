#include "zepch.h"

#include "KeyEvent.h"

namespace ZE
{
KeyEvent::KeyEvent(KeyCode keyCode)
	: m_keyCode(keyCode)
{
}

KeyPressedEvent::KeyPressedEvent(KeyCode keyCode, uint32 repeatCount)
	: KeyEvent(keyCode)
	, m_repeatCount(repeatCount)
{
}

std::string KeyPressedEvent::ToString() const
{
	std::stringstream ss;
	ss << "KeyPressedEvent: " << m_keyCode << " (" << m_repeatCount << " repeats)";
	return ss.str();
}

KeyReleasedEvent::KeyReleasedEvent(KeyCode keyCode)
	: KeyEvent(keyCode)
{
}

std::string KeyReleasedEvent::ToString() const
{
	std::stringstream ss;
	ss << "KeyReleased: " << m_keyCode;
	return ss.str();
}

}