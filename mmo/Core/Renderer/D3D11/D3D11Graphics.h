#pragma once
#include "API.h"
#include <d3d11.h>

class CORE_API D3D11Graphics
{
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;

public:

	D3D11Graphics(HWND hWnd);
	D3D11Graphics(const D3D11Graphics&) = delete;
	D3D11Graphics& operator=(const D3D11Graphics&) = delete;
	~D3D11Graphics();
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;

};