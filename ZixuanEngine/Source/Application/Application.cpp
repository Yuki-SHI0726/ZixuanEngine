#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Utils/Log/Logger.h"

namespace ZE
{
void Application::Run()
{
	Logger::Get().Print("Zixuan Engine Yes");

	WindowResizeEvent e(1280, 720);
	KeyPressedEvent e2(1, 1);
	if (e.IsInCategory(EventCategory::Application))
	{
		Logger::Get().Print(e.ToString());

	}
	else
	{

	}
		Logger::Get().Print(e2.ToString());
}
}