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

	virtual bool Init();
	virtual void Run();
	virtual void Shutdown();

	virtual void OnEvent(Event& e);

	void PushLayer(Layer* pLayer);
	void PushOverlay(Layer* pOverlay);

	const Window* GetWindow() const { return m_pWindow; }
	Window* GetWindow() { return m_pWindow; }

	static Application* Get() { return s_instance; }

private:
	bool OnWindowClose(WindowCloseEvent& windowCloseEvent);

private:
	static Application* s_instance;

	LayerStack m_layerStack;
	Window* m_pWindow = nullptr;
	bool m_isRunning = true;
};

/** To be defined in client */
Application* CreateApplication();
}