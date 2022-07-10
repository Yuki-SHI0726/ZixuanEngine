#include "zepch.h"
#include "LayerStack.h"

namespace ZE
{
LayerStack::LayerStack()
{
	m_layerInsert = m_layers.begin();
}

LayerStack::~LayerStack()
{
	for (Layer* pLayer : m_layers)
	{
		ZE_SAFE_DELETE(pLayer);
	}
}

void LayerStack::PushLayer(Layer* pLayer)
{
	m_layerInsert = m_layers.emplace(m_layerInsert, pLayer);
}

void LayerStack::PushOverlay(Layer* pOverlay)
{
	m_layers.emplace_back(pOverlay);
}

void LayerStack::PopLayer(Layer* pLayer)
{
	auto it = std::find(m_layers.begin(), m_layers.end(), pLayer);
	if (it != m_layers.end())
	{
		m_layers.erase(it);
		m_layerInsert--;
	}
}

void LayerStack::PopOverlay(Layer* pOverlay)
{
	auto it = std::find(m_layers.begin(), m_layers.end(), pOverlay);
	if (it != m_layers.end())
	{
		m_layers.erase(it);
	}
}
}