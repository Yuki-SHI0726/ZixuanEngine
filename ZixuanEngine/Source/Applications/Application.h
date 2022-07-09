#pragma once

#include "Core/Core.h"
#include "Windows/Window.h"

namespace ZE
{
class ZE_API Application
{
public:
	Application();
	virtual ~Application() = default;

	bool Init();
	void Run();

private:
	std::unique_ptr<Window> m_pWindow;
	bool m_isRunning = true;
};

/** To be defined in client */
Application* CreateApplication();
}