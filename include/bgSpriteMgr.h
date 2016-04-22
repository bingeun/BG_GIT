#pragma once
#include "bgSprite.h"
#include "bgBitmapMgr.h"

#define I_SpriteMgr bgSpriteMgr::GetInstance()
#define DEFAULT_LIFETIME (0.2f)

class bgSpriteMgr : public bgSingleton<bgSpriteMgr>
{
private:
	friend class bgSingleton<bgSpriteMgr>;

public:
	map<INT, bgSprite*>	m_List;
	int			m_iKeyCount;

public:
	INT			Add(TCHAR* pszName);
	bgSprite*	GetPtr(INT iKey);
	bgSprite*	GetPtr(TCHAR* szName);
	INT			GetKey(TCHAR* szName);
	bool		Release();

private:
	bgSpriteMgr();
public:
	virtual ~bgSpriteMgr();
};
