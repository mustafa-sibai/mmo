#pragma once
#include <memory>

#include "API.h"
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

	HWND GetHandle() const { return hWnd; }  // Allows Renderer to access HWND
	D3D11Graphics& GetD3D11Graphics();
	std::unique_ptr<D3D11Graphics> pD3D11Graphics;

	Timer Timer;
private:
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
