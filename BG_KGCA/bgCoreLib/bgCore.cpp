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
	// 타이머 & 입력관련 클래스 초기화
	m_Timer.Init();
	m_Input.Init();

	// 실제 게임로직 초기화
	Init();

	return true;
}

bool bgCore::GameFrame()
{
	m_Timer.Frame();
	m_Input.Frame();
	PreFrame();
	{ // 전처리
		Frame();
	} // 후처리
	PostFrame();
	return true;
}

bool bgCore::GameRender()
{
	Render();
	m_Timer.Render();
	m_Input.Render();
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
