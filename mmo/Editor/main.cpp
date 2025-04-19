#include <iostream>
#include "Core/Window.h"

int main()
{
	Window window;
	window.Create(L"Editor", 1280, 720);

    std::cout << "Starting main loop...\n";
    while (window.IsOpen()) {
        std::cout << "New frame\n";

        window.Update();
        const float c = sin(window.Timer.Peek()) / 2.0f + 0.5f;
        window.GetD3D11Graphics().ClearBuffer(c, c, 1.0f);
        window.GetD3D11Graphics().EndFrame();
    }
}
