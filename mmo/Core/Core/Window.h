#pragma once
#include <memory>

#include "Core/API.h"
#include <Windows.h>

#include "Timer.h"
#include "Renderer/D3D11/D3D11Graphics.h"

class CORE_API Window
{
private:
	HWND hWnd;
	HINSTANCE hInstance;

	int Width;
	int Height;

	bool isWindowOpen;

public:
	Window();
	~Window();

	void Create(const wchar_t* InWindowTitle, int InWidth, int InHeight);
	void Update();
	inline bool IsOpen() { return isWindowOpen; }

	const HWND& GetHWND() const { return hWnd; }

	Timer Timer;
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
