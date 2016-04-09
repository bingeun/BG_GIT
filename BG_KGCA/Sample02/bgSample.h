#pragma once
#include "bgCore.h"
#include "bgBitmap.h"

class bgSample : public bgCore
{
public:
	HDC			m_hScreenDC;
	bgBitmap	m_Background;
	bgBitmap	m_Hero;
	float		m_iX;
	float		m_iY;

public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();

public:
	bgSample();
	virtual ~bgSample();
};

