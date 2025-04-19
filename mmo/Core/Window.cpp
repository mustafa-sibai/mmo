#include "Window.h"

#include <iostream>
#include <string>

Window::Window() :
	hWnd(nullptr), hInstance(GetModuleHandle(nullptr)), Width(0), Height(0), isWindowOpen(false)
{
}

Window::~Window()
{
}

void Window::Create(const wchar_t* InWindowTitle, int InWidth, int InHeight)
{
	const wchar_t CLASS_NAME[] = L"CoreClass";

	WNDCLASS wc = { 0 };
	wc.lpfnWndProc = Window::WndProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = CLASS_NAME;
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	if (!RegisterClass(&wc))
	{
		MessageBox(nullptr, L"Window Registration Failed!", L"Error", MB_ICONERROR);
		return;
	}

	Width = InWidth;
	Height = InHeight;

	// Create the window
	hWnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		InWindowTitle,                    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style
		CW_USEDEFAULT, CW_USEDEFAULT,   // Position
		InWidth, InHeight,                  // Size
		nullptr,                        // Parent window    
		nullptr,                        // Menu
		hInstance,                      // Instance handle
		this							// Additional application data
	);

	if (!hWnd)
	{
		MessageBox(nullptr, L"Window Creation Failed!", L"Error", MB_ICONERROR);
		return;
	}

	ShowWindow(hWnd, SW_NORMAL);
	UpdateWindow(hWnd);

	isWindowOpen = true;

	pD3D11Graphics = std::make_unique<D3D11Graphics>(hWnd);
}

void Window::Update()
{
MSG msg = { 0 };

	// Non-blocking message loop using PeekMessage
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);

		// Exit the loop if a WM_QUIT message is received
		if (msg.message == WM_QUIT)
		{
			isWindowOpen = false;
			break;
		}
	}
}

D3D11Graphics& Window::GetD3D11Graphics()
{
		return *pD3D11Graphics;
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message) {
	case WM_CREATE: {
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		window = reinterpret_cast<Window*>(cs->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		break;
	}

	case WM_DESTROY: {
		if (window) window->isWindowOpen = false;
		PostQuitMessage(0);
		return 0;
	}

	case WM_SIZE: {
		if (window) {
			window->Width = LOWORD(lParam);
			window->Height = HIWORD(lParam);
			// Note: Renderer handles resize separately!
		}
		break;
	}
	}

	return DefWindowProc(hWnd, message, wParam, lParam);
}
