#include "zepch.h"
#include "WindowsInput.h"
#include "Applications/Application.h"

#include <GLFW/glfw3.h>

namespace ZE
{
	Input* Input::s_instance = new WindowsInput();

bool WindowsInput::IsKeyPressedImpl(KeyCode keyCode) const
{
	GLFWwindow* pWindow = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetWindowImplPtr());
	
	const int32 state = glfwGetKey(pWindow, keyCode);
	return state == GLFW_PRESS || state == GLFW_REPEAT;
}

bool WindowsInput::IsMouseButtonPressedImpl(KeyCode button) const
{
	GLFWwindow* pWindow = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetWindowImplPtr());
	
	const int32 state = glfwGetMouseButton(pWindow, button);
	return state == GLFW_PRESS;
}

FVec2 WindowsInput::GetMousePosImpl() const
{
	GLFWwindow* pWindow = static_cast<GLFWwindow*>(Application::Get()->GetWindow()->GetWindowImplPtr());

	double x;
	double y;
	glfwGetCursorPos(pWindow, &x, &y);

	return FVec2(x, y);
}


}