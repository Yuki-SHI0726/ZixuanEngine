#pragma once

#include "Applications/Layers/Layer.h"

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
	f32 m_time = 0.0f;
};
}

