#include "bgServerIOCP.h"

bool bgServerIOCP::Init()
{
	m_hIOCP = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, WORKER_THREAD_COUNT);
	for (int iThread = 0; iThread < WORKER_THREAD_COUNT; iThread++)
	{
		m_WorkerThread[iThread].CreateThread();
	}
	return true;
}

bool bgServerIOCP::Release()
{
	return true;
}

void bgServerIOCP::AddHandleToIOCP(HANDLE hClientSocket, DWORD dwReturnKey)
{
	::CreateIoCompletionPort(hClientSocket, m_hIOCP, dwReturnKey, 0);
	return;
}

bgServerIOCP::bgServerIOCP(void)
{
}

bgServerIOCP::~bgServerIOCP(void)
{
}
