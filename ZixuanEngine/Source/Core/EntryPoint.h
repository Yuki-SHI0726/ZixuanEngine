#pragma once

#ifdef ZE_PLATFORM_WINDOWS

ZE::Application* ZE::CreateApplication();

int main(int argc, char** argv[])
{
	ZE::Application* app = ZE::CreateApplication();
	app->Run();
	delete app;
	return 0;
}

#endif