#include "Applications/Application.h"

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
	ZE::Application* pApp = ZE::CreateApplication();
	if (pApp->Init())
	{
		pApp->Run();
	}
	ZE_DELETE(pApp);
	return 0;
}

#endif