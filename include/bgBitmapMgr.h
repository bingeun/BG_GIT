#pragma once
#include "bgBitmap.h"

#define I_BitmapMgr bgBitmapMgr::GetInstance()

class bgBitmapMgr : public bgSingleton<bgBitmapMgr>
{
private:
	friend class bgSingleton<bgBitmapMgr>;

public:
	map<INT, bgBitmap*>	m_List;
	INT			m_iKeyCount;

public:
	INT			Add(TCHAR* pszName, TCHAR* pszNameMask = NULL);
	bgBitmap*	GetPtr(INT iKey);
	bgBitmap*	GetPtr(TCHAR* szName);
	INT			GetKey(TCHAR* szName);
	bool		Release();

private:
	bgBitmapMgr();
public:
	virtual ~bgBitmapMgr();
};
