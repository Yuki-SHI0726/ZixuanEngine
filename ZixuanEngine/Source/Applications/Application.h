#pragma once

#include "Core/Core.h"
#include "Windows/Window.h"
#include "Events/ApplicationEvent.h"

namespace ZE
{
class ZE_API Application
{
public:
	virtual ~Application() = default;

	bool Init();
	void Run();

	void OnEvent(Event& e);

private:
	bool OnWindowClose(WindowCloseEvent& windowCloseEvent);

private:
	std::unique_ptr<Window> m_pWindow;
	bool m_isRunning = true;
};

/** To be defined in client */
Application* CreateApplication();
}