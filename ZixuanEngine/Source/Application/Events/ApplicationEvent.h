#pragma once

#include "Event.h"

namespace ZE
{
/** Event when a window got resized */
class ZE_API WindowResizeEvent : public Event
{
public: 
	WindowResizeEvent(uint32 width, uint32 height);

	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Application))

	uint32 GetWidth() const { return m_width; }
	uint32 GetHeight() const { return m_height; }
	virtual std::string ToString() const override final;

private:
	uint32 m_width = 0;
	uint32 m_height = 0;
};

/** Event when a window got closed */
class ZE_API WindowCloseEvent : public Event
{
public:
	WindowCloseEvent() = default;

	EVENT_CLASS_TYPE(WindowClose)
	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Application))
};

/** Event when application ticks */
class ZE_API AppTickEvent : public Event
{
public:
	AppTickEvent() = default;

	EVENT_CLASS_TYPE(AppTick)
	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Application))
};

/** Event when application updates */
class ZE_API AppUpdateEvent : public Event
{
public:
	AppUpdateEvent() = default;

	EVENT_CLASS_TYPE(AppUpdate)
	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Application))
};

/** Event when application renders */
class ZE_API AppRenderEvent : public Event
{
public:
	AppRenderEvent() = default;

	EVENT_CLASS_TYPE(AppRender)
	EVENT_CLASS_CATEGORY(static_cast<uint32>(EventCategory::Application))
};
}