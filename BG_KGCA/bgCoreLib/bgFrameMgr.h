#pragma once
#include "bgFrame.h"
#include "bgBitmapMgr.h"

#define I_FrameMgr bgFrameMgr::GetInstance()

class bgFrameMgr : public bgSingleton<bgFrameMgr>
{
private:
	friend class bgSingleton<bgFrameMgr>;

public:
	map<INT, bgFrame*>	m_List;
	int			m_iKeyCount;

public:
	INT			Add(TCHAR* pszName);
	bgFrame*	GetPtr(INT iKey);
	bgFrame*	GetPtr(TCHAR* szName);
	INT			GetKey(TCHAR* szName);
	bool		Release();

private:
	bgFrameMgr();
public:
	virtual ~bgFrameMgr();
};
