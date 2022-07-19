#pragma once

#include "Applications/Input/Input.h"

namespace ZE
{

class WindowsInput : public Input
{
protected:
	virtual bool IsKeyPressedImpl(KeyCode keyCode) const override final;

	virtual bool IsMouseButtonPressedImpl(KeyCode button) const override final;
	virtual FVec2 GetMousePosImpl() const override final;
};

}
