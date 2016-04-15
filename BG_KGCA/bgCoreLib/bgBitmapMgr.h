#pragma once
#include "bgStd.h"
#include "bgBitmap.h"
#include "bgLinkedList.h"
#include "bgHashTable.h"

#define I_BitmapMgr bgBitmapMgr::GetInstance()

class bgBitmapMgr : public bgSingleton<bgBitmapMgr>
{
private:
	friend class bgSingleton<bgBitmapMgr>;

public:
	bgLinkedList<bgBitmap>	m_List;
	bgHashTable<bgBitmap>	m_Hash;
	int			m_iCounter;

public:
	int			Add(TCHAR* pszName);
	bgBitmap*	GetBitmap(int iIndex);
	bool		Release();

private:
	bgBitmapMgr();

public:
	virtual ~bgBitmapMgr();
};
