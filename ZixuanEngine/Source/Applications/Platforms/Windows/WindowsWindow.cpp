#include "zepch.h"
#include "WindowsWindow.h"

namespace ZE
{
static bool s_glfwInitialized = false;

Window* Window::Create(const WindowProps& props)
{
	return new WindowsWindow(props);
}

WindowsWindow::WindowsWindow(const WindowProps& props)
{
	Init(props);
}

WindowsWindow::~WindowsWindow()
{
	Shutdown();
}

void WindowsWindow::OnUpdate()
{
	glfwPollEvents();
	glfwSwapBuffers(m_pWindow);
}

void WindowsWindow::SetVSync(bool enabled)
{
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else
	{		
		glfwSwapInterval(0);
	}

	m_data.m_vsync = enabled;
}

bool WindowsWindow::IsVSync() const
{
	return m_data.m_vsync;
}

void WindowsWindow::Init(const WindowProps& props)
{
	m_data.m_title = props.m_title;
	m_data.m_width = props.m_width;
	m_data.m_height = props.m_height;

	ZE_LOG(Info, "Creating window {%s} (%d, %d)", props.m_title.c_str(), props.m_width, props.m_height);

	if (!s_glfwInitialized)
	{
		const int32 initResult = glfwInit();
		ZE_ASSERT(initResult == GLFW_TRUE, "Failed initializing glfw");
		s_glfwInitialized = true;
	}

	m_pWindow = glfwCreateWindow(static_cast<int32>(props.m_width), static_cast<int32>(props.m_height), m_data.m_title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_pWindow);
	glfwSetWindowUserPointer(m_pWindow, &m_data);
	SetVSync(true);
}

void WindowsWindow::Shutdown()
{
	glfwDestroyWindow(m_pWindow);
}
}
