#pragma once
#include "Applications/Windows/Window.h"

#include <GLFW/glfw3.h>

namespace ZE
{
class ZE_API WindowsWindow : public Window
{
	struct WindowData
	{
		EventCallbackFn m_eventCallback;
		std::string m_title;
		uint32 m_width = 0;
		uint32 m_height = 0;
		bool m_vsync = true;
	};

public:
	WindowsWindow(const WindowProps& props);
	virtual ~WindowsWindow();

	virtual void OnUpdate() override final;

	virtual uint32 GetWidth() const override final { return m_data.m_width; }
	virtual uint32 GetHeight() const override final { return m_data.m_height; }

	virtual void SetEventCallback(const EventCallbackFn& callback) override final { m_data.m_eventCallback = callback; }
	virtual void SetVSync(bool enabled) override final;
	virtual bool IsVSync() const override final;

	virtual void* GetWindowImplPtr() const override final { return m_pWindow; }

private:
	virtual void Init(const WindowProps& props);
	virtual void Shutdown();

	void SetEventCallbacks();

private:
	GLFWwindow* m_pWindow = nullptr;
	WindowData m_data;
};
}