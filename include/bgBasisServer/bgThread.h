#pragma once
#include "bgSynchronize.h"

class bgThread : public bgServerObj
{
public:
	unsigned int	m_hThread;
	unsigned int	m_iThreadID;
	bool			m_bStarted;

public:
	void			CreateThread();
	virtual bool	Run();
	static unsigned int WINAPI	HandleRunner(LPVOID parameter);

public:
	bgThread(void);
	~bgThread(void);
};
