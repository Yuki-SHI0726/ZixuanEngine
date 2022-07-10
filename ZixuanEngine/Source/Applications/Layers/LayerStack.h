#pragma once

#include "Core.h"
#include "Layer.h"

#include <vector>

namespace ZE
{
class ZE_API LayerStack
{
public:
	LayerStack();
	~LayerStack();

	void PushLayer(Layer* pLayer);
	void PushOverlay(Layer* pOverlay);
	void PopLayer(Layer* pLayer);
	void PopOverlay(Layer* pOverlay);

	std::vector<Layer*>::iterator begin() { return m_layers.begin(); }
	std::vector<Layer*>::iterator end() { return m_layers.end(); }

private:
	std::vector<Layer*> m_layers;
	std::vector<Layer*>::iterator m_layerInsert;
};
}

