#include "zepch.h"
#include "ImGuiLayer.h"

#include "Applications/Platforms/OpenGL/ImGuiOpenGLRenderer.h"
#include "Applications/Application.h"

#include <imgui.h>
#include <GLFW/glfw3.h>
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
}
}