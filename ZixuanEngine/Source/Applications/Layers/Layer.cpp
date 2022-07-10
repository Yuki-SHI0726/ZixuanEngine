#include "zepch.h"
#include "Layer.h"

namespace ZE
{
Layer::Layer(const std::string& name)
	: m_debugName(name)
{
}

Layer::Layer(std::string&& name)
	: m_debugName(std::move(name))
{
}

}
