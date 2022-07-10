#pragma once

#include "Core/Core.h"
#include "Windows/Window.h"
#include "Events/ApplicationEvent.h"
#include "Layers/LayerStack.h"

namespace ZE
{
class ZE_API Application
{
public:
	virtual ~Application() = default;

	bool Init();
	void Run();
	void Shutdown();

	void OnEvent(Event& e);

	void PushLayer(Layer* pLayer) { m_layerStack.PushLayer(pLayer); }
	void PushOverlay(Layer* pOverlay) { m_layerStack.PushOverlay(pOverlay); }

private:
	bool OnWindowClose(WindowCloseEvent& windowCloseEvent);

private:
	LayerStack m_layerStack;
	Window* m_pWindow = nullptr;
	bool m_isRunning = true;
};

/** To be defined in client */
Application* CreateApplication();
}