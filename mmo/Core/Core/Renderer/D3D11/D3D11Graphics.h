#pragma once
#include "Core/API.h"
#include <d3d11.h>

class CORE_API D3D11Graphics
{
private:
	ID3D11Device* pDevice = nullptr;
	IDXGISwapChain* pSwap = nullptr;
	ID3D11DeviceContext* pContext = nullptr;
	ID3D11RenderTargetView* pTarget = nullptr;

	// Triangle rendering resources
	ID3D11VertexShader* pVertexShader = nullptr;
	ID3D11PixelShader* pPixelShader = nullptr;
	ID3D11InputLayout* pInputLayout = nullptr;
	ID3D11Buffer* pVertexBuffer = nullptr;

public:
	D3D11Graphics(const HWND& hWnd);
	D3D11Graphics(const D3D11Graphics&) = delete;
	D3D11Graphics& operator=(const D3D11Graphics&) = delete;
	~D3D11Graphics();
	void EndFrame();
	void ClearBuffer(float red, float green, float blue) noexcept;
	void InitTriangle();
	void DrawTestTriangle();
};