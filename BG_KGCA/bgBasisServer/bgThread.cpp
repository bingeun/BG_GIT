#include "bgThread.h"


unsigned int WINAPI bgThread::HandleRunner(LPVOID parameter)
{
	bgThread* pThread = (bgThread*)parameter;

	if (pThread)
		pThread->Run();

	return 0;
}

bool bgThread::Run()
{
	return true;
}

void bgThread::CreateThread()
{
	if (m_bStarted == true) return;
	m_hThread = _beginthreadex(NULL, 0, HandleRunner, (LPVOID)this, 0, &m_iThreadID);
	m_bStarted = true;
}

bgThread::bgThread(void)
{
	m_bStarted = false;
}


bgThread::~bgThread(void)
{
	CloseHandle((HANDLE)m_hThread);
}
