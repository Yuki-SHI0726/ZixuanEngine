#include "zepch.h"

#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
#include "Utils/Log/Logger.h"

#include <GLFW/glfw3.h>

namespace ZE
{
Application::Application()
{
	m_pWindow = std::unique_ptr<Window>(Window::Create());
}

void Application::Run()
{
	while (m_isRunning)
	{
		glClearColor(1, 0, 1, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		m_pWindow->OnUpdate();
	}
}
}