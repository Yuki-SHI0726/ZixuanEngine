#include "zepch.h"
#include "WindowsWindow.h"
#include "Applications/Events/ApplicationEvent.h"
#include "Applications/Events/KeyEvent.h"
#include "Applications/Events/MouseEvent.h"

namespace ZE
{
static bool s_glfwInitialized = false;

static void ZE_GLFWErrorCallback(int32 error_code, const char* description)
{
	ZE_LOG(Error, "GLFW error: %d, %s", error_code, description);
}

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
		glfwSetErrorCallback(ZE_GLFWErrorCallback);
		s_glfwInitialized = true;
	}

	m_pWindow = glfwCreateWindow(static_cast<int32>(props.m_width), static_cast<int32>(props.m_height), m_data.m_title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_pWindow);
	glfwSetWindowUserPointer(m_pWindow, &m_data);
	SetVSync(true);
	SetEventCallbacks();
}

void WindowsWindow::Shutdown()
{
	glfwDestroyWindow(m_pWindow);
}

void WindowsWindow::SetEventCallbacks()
{
	glfwSetWindowSizeCallback(m_pWindow, [](GLFWwindow* pWindow, int32 width, int32 height)
		{
			WindowData* pData = static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));
			pData->m_width = width;
			pData->m_height = height;

			WindowResizeEvent windowResizeEvent(width, height);
			pData->m_eventCallback(windowResizeEvent);
		});

	glfwSetWindowCloseCallback(m_pWindow, [](GLFWwindow* pWindow)
		{
			WindowData* pData = static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

			WindowCloseEvent windowCloseEvent;
			pData->m_eventCallback(windowCloseEvent);
		});

	glfwSetKeyCallback(m_pWindow, [](GLFWwindow* pWindow, int32 key, int32 scancode, int32 action, int32 mods)
		{
			WindowData* pData = static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

			switch (action)
			{
			case GLFW_PRESS:
			{
				KeyPressedEvent keyPressedEvent(key, 0);
				pData->m_eventCallback(keyPressedEvent);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent keyReleasedEvent(key);
				pData->m_eventCallback(keyReleasedEvent);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedEvent keyRepeatEvent(key, 1);
				pData->m_eventCallback(keyRepeatEvent);
				break;
			}
			default:
			{
				ZE_ASSERT(false, "Unsupported key action");
				break;
			}
			}
		});

	glfwSetMouseButtonCallback(m_pWindow, [](GLFWwindow* pWindow, int32 button, int32 action, int32 mods)
		{
			WindowData* pData = static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

			switch (action)
			{
			case GLFW_PRESS:
			{
				MouseButtonPressedEvent mouseButtonPressedEvent(button);
				pData->m_eventCallback(mouseButtonPressedEvent);
				break;
			}
			case GLFW_RELEASE:
			{
				MouseButtonReleasedEvent mouseButtonReleasedEvent(button);
				pData->m_eventCallback(mouseButtonReleasedEvent);
				break;
			}
			default:
			{
				ZE_ASSERT(false, "Unsupported mouse action");
				break;
			}
			}
		});

	glfwSetScrollCallback(m_pWindow, [](GLFWwindow* pWindow, f64 xoffset, f64 yoffset)
		{
			WindowData* pData = static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

			MouseScrolledEvent mouseScrolledEvent(static_cast<f32>(xoffset), static_cast<f32>(yoffset));
			pData->m_eventCallback(mouseScrolledEvent);
		});

	glfwSetCursorPosCallback(m_pWindow, [](GLFWwindow* pWindow, f64 xpos, f64 ypos)
		{
			WindowData* pData = static_cast<WindowData*>(glfwGetWindowUserPointer(pWindow));

			MouseMovedEvent mouseMovedEvent(static_cast<f32>(xpos), static_cast<f32>(ypos));
			pData->m_eventCallback(mouseMovedEvent);
		});
}
}
