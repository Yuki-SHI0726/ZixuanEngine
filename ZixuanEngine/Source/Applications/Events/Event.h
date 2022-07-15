#pragma once
#include <zepch.h>

namespace ZE
{
enum class EventType
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum class EventCategory : uint32
{
	None = 0,
	Application  = BIT(0),
	Input		 = BIT(1),
	Keyboard	 = BIT(2),
	Mouse		 = BIT(3),
	MouseButton  = BIT(4),
};

#define EVENT_CLASS_TYPE(type) \
	static EventType GetStaticType() { return EventType::##type; }\
	virtual EventType GetEventType() const override { return GetStaticType(); }\
	virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) \
	virtual uint32 GetCategoryFlags() const override { return category; }

/** Base class for events */
class ZE_API Event
{
	friend class EventDispatcher;

public:
	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual uint32 GetCategoryFlags() const = 0;
	bool IsInCategory(EventCategory category) const { return GetCategoryFlags() & static_cast<uint32>(category); }
	virtual std::string ToString() const { return GetName(); }
	bool IsHandled() const { return m_handled; }

protected:
	bool m_handled = false;
};
}