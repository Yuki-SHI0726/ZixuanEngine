#pragma once
#include "zepch.h"
#include "Core.h"
#include "Utils/Typedefs.h"

namespace ZE
{
class ZE_API Input
{
public:
	static bool IsKeyPressed(KeyCode keyCode) { return s_instance->IsKeyPressedImpl(keyCode); }

	static bool IsMouseButtonPressed(KeyCode button){ return s_instance->IsMouseButtonPressedImpl(button); }
	static FVec2 GetMousePos() { return s_instance->GetMousePosImpl(); }

	static void Shutdown();

protected:
	virtual bool IsKeyPressedImpl(KeyCode keyCode) const = 0;

	virtual bool IsMouseButtonPressedImpl(KeyCode button) const = 0;
	virtual FVec2 GetMousePosImpl() const = 0;

private:
	static Input* s_instance;
};
}