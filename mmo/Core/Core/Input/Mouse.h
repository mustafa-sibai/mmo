#pragma once
#include "Core/API.h"
#include "Core/Window.h"
#include "Core/Math/Vector2.h"

class CORE_API Mouse
{
	friend class Engine;
private:
	const Window& window;

	static constexpr int totalMouseButtons = 5;

	bool current[totalMouseButtons] = { false };
	bool prev[totalMouseButtons] = { false };

public:
	enum class ButtonCode
	{
		LeftButton,
		RightButton,
		MiddleButton,
		XButton1,
		XButton2
	};

public:

	bool IsButtonPressed(ButtonCode button);
	bool IsButtonReleased(ButtonCode button);
	bool IsButtonHeld(ButtonCode button);

	Vector2f GetPosition(bool relativeToWindow = false) const;

private:
	Mouse(const Window& window);
	Mouse(const Mouse&) = delete;
	Mouse(Mouse&&) = delete;
	Mouse& operator=(const Mouse&) = delete;
	~Mouse() = default;

	int GetVirtualKey(ButtonCode button) const;
	void Update();
};