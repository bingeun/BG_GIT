#include "bgWorkThread.h"
#include "bgServerIOCP.h"
#include "bgUser.h"

bool bgWorkThread::Run()
{
	DWORD			dwTransfer;
	ULONG_PTR		keyValue;
	LPOVERLAPPED	overlapped;
	BOOL			rReturn;
	while (true)
	{
		rReturn = ::GetQueuedCompletionStatus(I_ServerIOCP.m_hIOCP, &dwTransfer, &keyValue, &overlapped, INFINITE);
		bgUser* pUser = (bgUser*)keyValue;
		if (rReturn == TRUE)
		{
			if (dwTransfer == 0)
			{
				// 유저 삭제 처리
				pUser->DeleteUser();
			}
			if (dwTransfer != 0 && overlapped != 0)
			{
				pUser->Dispatch(dwTransfer, overlapped);
			}
		}
		else
		{
			// 한개의 소켓으로 보내고 받고 할 경우에 발생
			if (GetLastError() != ERROR_OPERATION_ABORTED)
			{
				if (dwTransfer == 0)
				{
					// 유저 삭제 처리
					pUser->DeleteUser(pUser->m_Socket);
				}
			}
		}
	}
	return true;
}

bgWorkThread::bgWorkThread(void)
{
}

bgWorkThread::~bgWorkThread(void)
{
}
