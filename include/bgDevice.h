#pragma once
#include "bgWindow.h"
#include <d3d11.h>

class bgDevice : public bgWindow
{
public:
	ID3D11Device*			m_pd3dDevice;
	ID3D11DeviceContext*	m_pImmediateContext;
	IDXGISwapChain*			m_pSwapChain;
	ID3D11RenderTargetView*	m_pRenderTargetView;
	D3D_FEATURE_LEVEL		m_FeatureLevel;
	D3D_DRIVER_TYPE			m_DriverType;
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;
	D3D11_VIEWPORT			m_ViewPort;

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

	bgDevice();
	virtual ~bgDevice();
};
