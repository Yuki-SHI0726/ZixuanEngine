#pragma once

#include "Core/Core.h"

namespace ZE
{
class ZE_API Application
{
public:
	virtual ~Application() = default;

	void Run();
};

/** To be defined in client */
Application* CreateApplication();
}