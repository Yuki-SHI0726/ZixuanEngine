#pragma once

#include "Applications/Layers/Layer.h"
#include "Applications/Events/MouseEvent.h"
#include "Applications/Events/ApplicationEvent.h"
#include "Applications/Events/KeyEvent.h"

namespace ZE
{
class ZE_API ImGuiLayer : public Layer
{
public:
	ImGuiLayer();

	virtual void OnAttach() override final;
	virtual void OnDettach() override final;
	virtual void OnUpdate() override final;
	virtual void OnEvent(Event& inEvent) override final;

private:
	bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
	bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
	bool OnMouseMovedEvent(MouseMovedEvent& e);
	bool OnMouseScrolledEvent(MouseScrolledEvent& e);
	bool OnKeyPressedEvent(KeyPressedEvent& e);
	bool OnKeyReleasedEvent(KeyReleasedEvent& e);
	bool OnKeyTypedEvent(KeyTypedEvent& e);
	bool OnWindowResizedEvent(WindowResizedEvent& e);

private:
	f32 m_time = 0.0f;
};
}

