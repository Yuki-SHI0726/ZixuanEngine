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

	template<typename EventType>
	bool Dispatch(EventFn<EventType> func);

private:
	Event& m_event;
};

template<typename EventType>
inline bool EventDispatcher::Dispatch(EventFn<EventType> func)
{
	if (m_event.GetEventType() == EventType::GetStaticType())
	{
		m_event.m_handled = func(*reinterpret_cast<EventType*>(&m_event));
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