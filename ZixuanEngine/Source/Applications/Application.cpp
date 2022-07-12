#include "zepch.h"

#include "Application.h"
#include "Events/EventDispatcher.h"
#include "Events/KeyEvent.h"
#include "Utils/Log/Logger.h"

#include <glad/glad.h>

namespace ZE
{
	Application* Application::s_instance = nullptr;

bool Application::Init()
{
	ZE_ASSERT(!s_instance, "Application already exists");
	s_instance = this;

	m_pWindow = Window::Create();
	m_pWindow->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));

	return true;
}

void Application::Run()
{
	while (m_isRunning)
	{
		glClearColor(0, 0.5, 0.5, 1);
		glClear(GL_COLOR_BUFFER_BIT);

		for (Layer* pLayer : m_layerStack)
		{
			pLayer->OnUpdate();
		}

		m_pWindow->OnUpdate();
	}
}

void Application::Shutdown()
{
	ZE_SAFE_DELETE(m_pWindow);
}

void Application::OnEvent(Event& e)
{
#if ZE_DEBUG
	ZE_LOG(Info, e.ToString().c_str());
#endif

	EventDispatcher dispatcher(e);
	dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClose));

	for (auto it = m_layerStack.end(); it != m_layerStack.begin();)
	{
		(*--it)->OnEvent(e);
		if (e.IsHandled())
		{
			break;
		}
	}
}

void Application::PushLayer(Layer* pLayer)
{
	m_layerStack.PushLayer(pLayer);
	pLayer->OnAttach();
}

void Application::PushOverlay(Layer* pOverlay)
{
	m_layerStack.PushOverlay(pOverlay);
	pOverlay->OnAttach();
}

bool Application::OnWindowClose(WindowCloseEvent& windowCloseEvent)
{
	m_isRunning = false;
	return true;
}
}