#include <iostream>
#include "Core/Window.h"
#include "Core/Renderer/D3D11/D3D11Graphics.h"

int main()
{
	Window window;
	window.Create(L"Editor", 1280, 720);

	D3D11Graphics d3D11Graphics(window.GetHWND());

	std::cout << "Starting main loop...\n";

	while (window.IsOpen())
	{
		std::cout << "New frame\n";

		window.Update();

		const float c = sin(window.Timer.Peek()) / 2.0f + 0.5f;

		d3D11Graphics.ClearBuffer(c, c, 1.0f);
		d3D11Graphics.DrawTestTriangle();
		d3D11Graphics.EndFrame();
	}
}