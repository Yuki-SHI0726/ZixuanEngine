#pragma once
#include "Applications/Events/Event.h"

namespace ZE
{
struct WindowProps
{
	std::string m_title = "Zixuan Engine";
	uint32 m_width = 1280;
	uint32 m_height = 720;

	WindowProps() = default;

	WindowProps(const std::string& title, uint32 width, uint32 height)
		: m_title(title)
		, m_width(width)
		, m_height(height)
	{
	}
};


class ZE_API Window
{
public:
	using EventCallbackFn = std::function<void(Event&)>;

public:
	virtual ~Window() = default;

	virtual void OnUpdate() = 0;

	virtual uint32 GetWidth() const = 0;
	virtual uint32 GetHeight() const = 0;

	// Window attributes
	virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
	virtual void SetVSync(bool enabled) = 0;
	virtual bool IsVSync() const = 0;

	static Window* Create(const WindowProps& props = WindowProps());
};
}
