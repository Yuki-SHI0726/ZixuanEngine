#include "zepch.h"

#include "Application.h"
#include "Events/EventDispatcher.h"
#include "Events/KeyEvent.h"
#include "Utils/Log/Logger.h"

#include <GLFW/glfw3.h>

namespace ZE
{
bool Application::Init()
{
	m_pWindow = std::unique_ptr<Window>(Window::Create());
	m_pWindow->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));

	return true;
}

void Application::Run()
{
	while (m_isRunning)
	{
		glClearColor(0, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		m_pWindow->OnUpdate();
	}
}

void Application::OnEvent(Event& e)
{
#if ZE_DEBUG
	ZE_LOG(Info, e.GetName());
#endif

	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));
}

bool Application::OnWindowClose(WindowCloseEvent& windowCloseEvent)
{
	m_isRunning = false;
	return true;
}
}