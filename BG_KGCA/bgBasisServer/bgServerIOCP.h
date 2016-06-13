#pragma once
#include "bgWorkThread.h"
#include "bgUser.h"

#define I_ServerIOCP bgServerIOCP::GetInstance()

#define WORKER_THREAD_COUNT 3

class bgServerIOCP : public bgSingleton<bgServerIOCP>, public bgServerObj
{
private:
	friend class bgSingleton<bgServerIOCP>;

public:
	HANDLE			m_hIOCP;
	bgWorkThread	m_WorkerThread[WORKER_THREAD_COUNT];

public:
	bool			Init();
	bool			Release();
	void			AddHandleToIOCP(HANDLE hClientSocket, DWORD dwReturnKey);

public:
	bgServerIOCP(void);
	~bgServerIOCP(void);
};
