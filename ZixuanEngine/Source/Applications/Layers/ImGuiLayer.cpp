#include "zepch.h"
#include "ImGuiLayer.h"

#include "Applications/Platforms/OpenGL/ImGuiOpenGLRenderer.h"
#include "Applications/Application.h"
#include "Applications/Events/EventDispatcher.h"

#include <imgui.h>

// Temp
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3_loader.h>

namespace ZE
{
ImGuiLayer::ImGuiLayer()
	: Layer("ImGuiLayer")
{
}

void ImGuiLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui::StyleColorsDark();

	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplOpenGL3_Init("#version 410");
}

void ImGuiLayer::OnDettach()
{
}

void ImGuiLayer::OnUpdate()
{
	ImGuiIO& io = ImGui::GetIO();
	Application* pApplication = Application::Get();
	io.DisplaySize = ImVec2(pApplication->GetWindow()->GetWidth(), pApplication->GetWindow()->GetHeight());

	const f32 time = static_cast<f32>(glfwGetTime());
	io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
	m_time = time;

	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	static bool show = true;
	ImGui::ShowDemoWindow(&show);

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void ImGuiLayer::OnEvent(Event& inEvent)
{
	EventDispatcher dispatcher(inEvent);
	dispatcher.Dispatch<MouseButtonPressedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtonPressedEvent));
	dispatcher.Dispatch<MouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseButtonReleasedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseMovedEvent));
	dispatcher.Dispatch<MouseScrolledEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnMouseScrolledEvent));
	dispatcher.Dispatch<KeyPressedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyPressedEvent));
	dispatcher.Dispatch<KeyReleasedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyReleasedEvent));
	dispatcher.Dispatch<KeyTypedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnKeyTypedEvent));
	dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FUNCTION(ImGuiLayer::OnWindowResizedEvent));
}

bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();

	io.MouseDown[e.GetMouseButton()] = true;

	return false;
}

bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();

	io.MouseDown[e.GetMouseButton()] = false;

	return false;
}

bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();

	io.MousePos = ImVec2(e.GetX(), e.GetY());

	return false;
}

bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();

	io.MouseWheelH += e.GetY();
	io.MouseWheel += e.GetX();

	return false;
}

bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();

	io.KeysDown[e.GetKeyCode()] = true;
	io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
	io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
	io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
	io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];

	return false;
}

bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();

	io.KeysDown[e.GetKeyCode()] = false;

	return false;
}

bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();

	KeyCode keyCode = e.GetKeyCode();
	if (keyCode > 0 && keyCode < 0x10000)
	{
		io.AddInputCharacter(keyCode);
	}

	return false;
}

bool ImGuiLayer::OnWindowResizedEvent(WindowResizedEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();

	io.DisplaySize = ImVec2(e.GetWidth(), e.GetHeight());
	io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);

	return false;
}
}