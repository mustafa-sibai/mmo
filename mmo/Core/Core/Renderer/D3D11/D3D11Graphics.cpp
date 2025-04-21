#include "D3D11Graphics.h"
#include <vector>
#include <DirectXMath.h>
#include "../Vertex.h"
#include <d3dcompiler.h>

#pragma comment(lib, "D3DCompiler.lib")

D3D11Graphics::D3D11Graphics(const HWND& hWnd)  
{  
   phWnd = &hWnd;

   DXGI_SWAP_CHAIN_DESC sd = {};  
   sd.BufferDesc.Width = 0;  
   sd.BufferDesc.Height = 0;  
   sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;  
   sd.BufferDesc.RefreshRate.Numerator = 0;  
   sd.BufferDesc.RefreshRate.Denominator = 0;  
   sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;  
   sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;  
   sd.SampleDesc.Count = 1;  
   sd.SampleDesc.Quality = 0;  
   sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  
   sd.BufferCount = 1;  
   sd.OutputWindow = hWnd;  
   sd.Windowed = TRUE;  
   sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;  
   sd.Flags = 0;  

   // create device and front/back buffers, and swap chain and rendering context  
   D3D11CreateDeviceAndSwapChain(  
       nullptr,  
       D3D_DRIVER_TYPE_HARDWARE,  
       nullptr,  
       0,  
       nullptr,  
       0,  
       D3D11_SDK_VERSION,  
       &sd,  
       &pSwap,  
       &pDevice,  
       nullptr,  
       &pContext  
   );  
   // gain access to texture subresource in swap chain (back buffer)  
   ID3D11Resource* pBackBuffer = nullptr;  
   pSwap->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pBackBuffer));  
   pDevice->CreateRenderTargetView(  
       pBackBuffer,  
       nullptr,  
       &pTarget  
   );  
   pBackBuffer->Release();  
}

D3D11Graphics::~D3D11Graphics()
{
    if (pVertexBuffer != nullptr) pVertexBuffer->Release();
    if (pInputLayout != nullptr) pInputLayout->Release();
    if (pPixelShader != nullptr) pPixelShader->Release();
    if (pVertexShader != nullptr) pVertexShader->Release();
    if (pTarget != nullptr) pTarget->Release();
    if (pContext != nullptr) pContext->Release();
    if (pSwap != nullptr) pSwap->Release();
    if (pDevice != nullptr) pDevice->Release();
}

void D3D11Graphics::EndFrame()
{
	pSwap->Present(1u, 0u);
}

void D3D11Graphics::ClearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red,green,blue,1.0f };
	pContext->ClearRenderTargetView(pTarget, color);
}

void D3D11Graphics::DrawTestTriangle()
{
    // Corrected Vertex structure
    struct Vertex {
        float x, y, z;
    };

    Vertex vertices[] =
    {
        { 0.0f,  0.5f, 0.0f },
        { 0.5f, -0.5f, 0.0f },
        { -0.5f, -0.5f, 0.0f },
    };

    D3D11_BUFFER_DESC BufferData = {};
    BufferData.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    BufferData.Usage = D3D11_USAGE_DEFAULT;
    BufferData.CPUAccessFlags = 0u;
    BufferData.MiscFlags = 0u;
    BufferData.ByteWidth = sizeof(vertices);
    BufferData.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA SubresourceData = {};
    SubresourceData.pSysMem = vertices;

    pDevice->CreateBuffer(&BufferData, &SubresourceData, &pVertexBuffer);

    UINT stride = sizeof(Vertex);
    UINT offset = 0u;
    pContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);

    // Create and bind shaders
    D3DReadFileToBlob(L"PixelShader.cso", &pBlob);
    pDevice->CreatePixelShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pPixelShader);
    pContext->PSSetShader(pPixelShader, nullptr, 0u);

    D3DReadFileToBlob(L"VertexShader.cso", &pBlob);
    pDevice->CreateVertexShader(pBlob->GetBufferPointer(), pBlob->GetBufferSize(), nullptr, &pVertexShader);
    pContext->VSSetShader(pVertexShader, nullptr, 0u);

    // Create input layout
    D3D11_INPUT_ELEMENT_DESC InputElementDescriptors[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };

    pDevice->CreateInputLayout(
        InputElementDescriptors,
        (UINT)std::size(InputElementDescriptors),
        pBlob->GetBufferPointer(),
        pBlob->GetBufferSize(),
        &pInputLayout
    );

    pContext->IASetInputLayout(pInputLayout);

    // Bind render target
    pContext->OMSetRenderTargets(1u, &pTarget, nullptr);

    // Set viewport
    RECT rect;
    GetClientRect(*phWnd, &rect);
    D3D11_VIEWPORT Viewport = {};
    Viewport.Width = static_cast<float>(rect.right - rect.left);
    Viewport.Height = static_cast<float>(rect.bottom - rect.top);
    Viewport.MinDepth = 0.0f;
    Viewport.MaxDepth = 1.0f;
    Viewport.TopLeftX = 0.0f;
    Viewport.TopLeftY = 0.0f;
    pContext->RSSetViewports(1u, &Viewport);

    // Set primitive topology
    pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Draw the triangle
    pContext->Draw((UINT)std::size(vertices), 0u);
}
	// Bind render target
	// should use pTarget->GetAddressOf() instead of &pTarget
	// ID3D11RenderTargetView* pTargets[] =
	// { pTarget };