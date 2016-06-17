#include "bgDX01.h"

HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut)
{
	HRESULT hr = S_OK;

	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
	dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

	ID3DBlob* pErrorBlob;
	hr = D3DX11CompileFromFile(szFileName, NULL, NULL, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, NULL, ppBlobOut, &pErrorBlob, NULL);
	if (FAILED(hr))
	{
		if (pErrorBlob != NULL)
			OutputDebugStringA((char*)pErrorBlob->GetBufferPointer());
		if (pErrorBlob) pErrorBlob->Release();
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();

	return S_OK;
}

HRESULT InitDevice()
{
	HRESULT hr = S_OK;
	m_ViewPort.Width = 800;
	m_ViewPort.Height = 600;
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_pImmediateContext->RSSetViewports(1, &m_ViewPort);

	return S_OK;
}

void CleanupDevice()
{
	if (g_pImmediateContext) g_pImmediateContext->ClearState();

	if (g_pConstantBuffer) g_pConstantBuffer->Release();
	if (g_pVertexBuffer) g_pVertexBuffer->Release();
	if (g_pIndexBuffer) g_pIndexBuffer->Release();
	if (g_pVertexLayout) g_pVertexLayout->Release();
	if (g_pVertexShader) g_pVertexShader->Release();
	if (g_pPixelShader) g_pPixelShader->Release();

	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pImmediateContext) g_pImmediateContext->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();
}

bool bgDX01::Init()
{
	return true;
}

bool bgDX01::Frame()
{
	return true;
}

bool bgDX01::Render()
{
	return true;
}

bool bgDX01::Release()
{
	CleanupDevice();

	return true;
}

bool bgDX01::PreRender()
{
	float ClearColor[4] = { 0.0f, 0.2f, 0.5f, 1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
	return true;
}

bool bgDX01::PostRender()
{
	m_pSwapChain->Present(0, 0);
	return true;
}

bgDX01::bgDX01()
{
}

bgDX01::~bgDX01()
{
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstatnce, LPWSTR lpCmdLine, int nCmdShow)
{
	bgDX01 win;
	if (win.SetWindow(hInstance) == true)
	{
		win.CenterWindow();
		win.Run();
	}
	return 0;
}
