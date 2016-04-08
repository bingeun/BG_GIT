#include "bgSample.h"



bool bgSample::Init()
{
	return true;
}

bool bgSample::Frame()
{
	return true;
}

bool bgSample::Render()
{
	m_Timer.Render();
	HDC hdc = GetDC(this->m_hWnd);
	SetBkMode(hdc, TRANSPARENT);
	TextOut(hdc, 0, 0, m_Timer, m_csBuffer, _tcslen(m_Timer.m_csBuffer));
	ReleaseDC(m_hWnd, hdc);
	return true;
}

bool bgSample::Release()
{
	m_Timer.Release();
	return true;
}

bgSample::bgSample()
{
}


bgSample::~bgSample()
{
}
