#pragma once
#include "API.h"
#include <Windows.h>

class CORE_API Window
{
private:
	HWND hWnd;
	HINSTANCE hInstance;

	bool isWindowOpen;

public:
	Window();
	~Window();

	void Create(const wchar_t* windowTitle, int width, int height);
	void Update();
	inline bool IsOpen() { return isWindowOpen; }

private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};