#include "CoreMinimal.h"
//
class Sandbox : public ZE::Application
{
	
};

ZE::Application* ZE::CreateApplication()
{
	return new Sandbox();
}
