#pragma once
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dcompiler.h>
#include <D3DX10math.h>
#include "bgStd.h"
#include "bgSys.h"
#include "bgCore.h"

struct SimpleVertex
{
	D3DXVECTOR3 Pos;
	D3DXVECTOR4 Color0;
	D3DXVECTOR4 Color1;
};
struct ConstantBuffer
{
	D3DXMATRIX mWorld;
	D3DXMATRIX mView;
	D3DXMATRIX mProj;
};

class bgDX01 : public bgCore
{
public:


public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	bool PreRender();
	bool PostRender();

public:
	bgDX01();
	virtual ~bgDX01();
};

