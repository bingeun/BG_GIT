#include "bgCore.h"


bool bgCore::DrawDebug()
{
#ifdef _DEBUG

#endif //_DEBUG
	return true;
}

bool bgCore::DrawDebug(TCHAR * pString, int iX, int iY)
{
#ifdef _DEBUG

#endif //_DEBUG
	return true;
}

bool bgCore::GameRun()
{
	GameFrame();
	GameRender();
	return true;
}

bool bgCore::GameInit()
{
	// Ÿ�̸� & �Է°��� Ŭ���� �ʱ�ȭ
	m_Timer.Init();
	m_Input.Init();

	// ���� ���ӷ��� �ʱ�ȭ
	Init();

	return true;
}

bool bgCore::GameFrame()
{
	m_Timer.Frame();
	m_Input.Frame();
	PreFrame();
	{ // ��ó��
		Frame();
	} // ��ó��
	PostFrame();
	return true;
}

bool bgCore::GameRender()
{
	PreRender();
	{ // ��ó��
		Render();
	m_Timer.Render();
	m_Input.Render();
	} // ��ó��
	PostRender();
	return true;
}

bool bgCore::GameRelease()
{
	Release();

	m_Timer.Release();
	m_Input.Release();
	return true;
}

void bgCore::MsgEvent(MSG msg)
{
	m_Input.MsgEvent(msg);
}

bgCore::bgCore()
{
}


bgCore::~bgCore()
{
}
