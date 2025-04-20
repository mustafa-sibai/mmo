#pragma once
#include "Core/API.h"

class CORE_API Mouse
{
public:
	enum class ButtonCode
	{
		LeftButton = 0,
		RightButton,
		MiddleButton,
		XButton1,
		XButton2,
		ButtonCount
	};

	bool IsButtonPressed(ButtonCode button);
	bool IsButtonReleased(ButtonCode button);
	bool IsButtonHeld(ButtonCode button);

	void Update();
};