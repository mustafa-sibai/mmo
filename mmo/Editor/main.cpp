#include <iostream>
#include "Core/Window.h"

int main()
{
	Window window;
	window.Create(L"Editor", 1280, 720);

	while (window.IsOpen())
	{
		window.Update();
	}
}