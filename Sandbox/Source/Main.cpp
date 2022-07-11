#include "Applications/Application.h"

class ExampleLayer : public ZE::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{ 
	}

	virtual void OnUpdate() override final
	{
		//ZE_LOG(Prompt, "ExampleLayer::Update");
	}

	virtual void OnEvent(ZE::Event& e) override final
	{
		if (!e.IsInCategory(ZE::EventCategory::Mouse) && 
			!e.IsInCategory(ZE::EventCategory::Application))
		{
		}
	}
};

class Sandbox : public ZE::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}
};

ZE::Application* ZE::CreateApplication()
{
	return new Sandbox();
}

#ifdef ZE_PLATFORM_WINDOWS

int main(int argc, char** argv[])
{
	ZE::Application* pApp = ZE::CreateApplication();
	if (pApp->Init())
	{
		pApp->Run();
	}
	pApp->Shutdown();

	ZE_DELETE(pApp);
	return 0;
}

#endif