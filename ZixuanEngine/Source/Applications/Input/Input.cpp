#include "zepch.h"
#include "Input.h"

void ZE::Input::Shutdown()
{
	ZE_SAFE_DELETE(s_instance);
}
