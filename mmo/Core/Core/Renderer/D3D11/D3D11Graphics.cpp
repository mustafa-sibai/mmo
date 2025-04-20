#include "D3D11Graphics.h"
#include <d3dcompiler.h>
#include <vector>
#include <DirectXMath.h>

// Vertex structure
struct Vertex
{
    DirectX::XMFLOAT3 pos;
    DirectX::XMFLOAT4 color;
};

D3D11Graphics::D3D11Graphics(const HWND& hWnd)
{
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

    InitTriangle();
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


void D3D11Graphics::InitTriangle()
{
    // Compile vertex shader
    ID3DBlob* pVSBlob = nullptr;
    D3DCompileFromFile(
        L"Shaders.hlsl",
        nullptr,
        nullptr,
        "VS",
        "vs_5_0",
        0,
        0,
        &pVSBlob,
        nullptr
    );

    pDevice->CreateVertexShader(
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        nullptr,
        &pVertexShader
    );

    // Create input layout
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
    };

    pDevice->CreateInputLayout(
        layout,
        2,
        pVSBlob->GetBufferPointer(),
        pVSBlob->GetBufferSize(),
        &pInputLayout
    );
    pVSBlob->Release();

    // Compile pixel shader
    ID3DBlob* pPSBlob = nullptr;
    D3DCompileFromFile(
        L"Shaders.hlsl",
        nullptr,
        nullptr,
        "PS",
        "ps_5_0",
        0,
        0,
        &pPSBlob,
        nullptr
    );

    pDevice->CreatePixelShader(
        pPSBlob->GetBufferPointer(),
        pPSBlob->GetBufferSize(),
        nullptr,
        &pPixelShader
    );
    pPSBlob->Release();

    // Create vertex buffer
    Vertex vertices[] =
    {
        { DirectX::XMFLOAT3(0.0f, 0.5f, 0.0f), DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },  // Top - red
        { DirectX::XMFLOAT3(0.5f, -0.5f, 0.0f), DirectX::XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) }, // Right - green
        { DirectX::XMFLOAT3(-0.5f, -0.5f, 0.0f), DirectX::XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) } // Left - blue
    };

    D3D11_BUFFER_DESC bd = {};
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0u;
    bd.MiscFlags = 0u;
    bd.ByteWidth = sizeof(vertices);
    bd.StructureByteStride = sizeof(Vertex);

    D3D11_SUBRESOURCE_DATA sd = {};
    sd.pSysMem = vertices;

    pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer);
}

void D3D11Graphics::DrawTestTriangle()
{
    // Bind the vertex buffer to the pipeline
    UINT stride = sizeof(Vertex);
    UINT offset = 0u;
    pContext->IASetVertexBuffers(0u, 1u, &pVertexBuffer, &stride, &offset);

    // Set primitive topology
    pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    // Bind input layout
    pContext->IASetInputLayout(pInputLayout);

    // Bind shaders
    pContext->VSSetShader(pVertexShader, nullptr, 0u);
    pContext->PSSetShader(pPixelShader, nullptr, 0u);

    // Draw the triangle
    pContext->Draw(3u, 0u);
}