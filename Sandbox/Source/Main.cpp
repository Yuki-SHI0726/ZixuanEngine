#include "Applications/Application.h"
#include "Applications/Layers/ImGuiLayer.h"

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
	virtual bool Init() override final
	{
		ZE::Application::Init();

		PushLayer(new ExampleLayer());
		PushOverlay(new ZE::ImGuiLayer());

		return true;
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