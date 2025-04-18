#include <iostream>
#include "Window.h"

int main()
{
	Window window;
	window.Create(L"MMO", 1280, 720);

	while (window.IsOpen())
	{
		window.Update();
	}
}