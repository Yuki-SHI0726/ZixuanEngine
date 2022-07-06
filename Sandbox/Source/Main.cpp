#include "CoreMinimal.h"

class Sandbox : public ZE::Application
{
	
};

ZE::Application* ZE::CreateApplication()
{
	return new Sandbox();
}

#ifdef ZE_PLATFORM_WINDOWS

int main(int argc, char** argv[])
{
	ZE::Application* app = ZE::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif