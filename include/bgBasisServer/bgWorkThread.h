#pragma once
#include "bgThread.h"

class bgWorkThread : public bgThread
{
public:
	HANDLE		m_hIOCP;

public:
	bool		Run();
	void		Set(HANDLE hIOCP) { m_hIOCP = hIOCP; }

public:
	bgWorkThread(void);
	~bgWorkThread(void);
};
