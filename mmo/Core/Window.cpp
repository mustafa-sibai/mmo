#include "Window.h"
#include <string>

Window::Window() :
	hWnd(nullptr), hInstance(GetModuleHandle(nullptr)), isWindowOpen(false)
{
}

Window::~Window()
{
}

void Window::Create(const wchar_t* windowTitle, int width, int height)
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

	// Create the window
	hWnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		windowTitle,                    // Window text
		WS_OVERLAPPEDWINDOW,            // Window style
		CW_USEDEFAULT, CW_USEDEFAULT,   // Position
		width, height,                  // Size
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
}

void Window::Update()
{
	MSG msg;
	// Continue to retrieve messages until WM_QUIT is received.
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));

	switch (message)
	{
	case WM_CREATE:
	{
		// Retrieve the pointer passed via CreateWindowEx.
		CREATESTRUCT* cs = reinterpret_cast<CREATESTRUCT*>(lParam);
		Window* window = reinterpret_cast<Window*>(cs->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));
		// Continue with default creation.
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	case WM_DESTROY:
		if (window)
			window->isWindowOpen = false;

		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}