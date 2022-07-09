#pragma once

#include "Event.h"

namespace ZE
{
class EventDispatcher
{
	template<typename Type>
	using EventFn = std::function<bool(Type&)>;

public:
	EventDispatcher(Event& inEvent);

	template<typename Type>
	bool Dispatch(EventFn<Type> func);

private:
	Event& m_event;
};

template<typename Type>
inline bool EventDispatcher::Dispatch(EventFn<Type> func)
{
	if (m_event.GetEventType() == Type::GetStaticType())
	{
		m_event.m_handled = func(*(Type*)&m_event);
		return true;
	}
	return false;
}

inline std::ostream& operator<<(std::ostream& os, const Event& InEvent)
{
	os << InEvent.ToString();
	return os;
}
}