#pragma once

#include "Core.h"
#include "Applications/Events/Event.h"

namespace ZE
{

class ZE_API Layer
{
public:
	Layer() = default;
	Layer(const std::string& name);
	Layer(std::string&& name);
	virtual ~Layer() = default;

	virtual void OnAttach() {}
	virtual void OnDettach() {}
	virtual void OnUpdate() {}
	virtual void OnEvent(Event& inEvent) {}

	const std::string& GetName() const { return m_debugName; }

protected:
	std::string m_debugName = "Layer";
};
}