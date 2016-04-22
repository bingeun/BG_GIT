#include "bgBitmapMgr.h"


INT bgBitmapMgr::Add(TCHAR* pszName, TCHAR* pszNameMask)
{
	map<INT, bgBitmap*>::iterator itor;

	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		bgBitmap* data = (*itor).second;
		if (!_tcsicmp(pszName, data->m_szName.c_str()))
		{
			return (*itor).first;
		}
	}

	bgBitmap* data = new bgBitmap;
	data->Init();
	if (data->Load(pszName, pszNameMask))
	{
		m_List.insert(make_pair(m_iKeyCount++, data));
	}

	return m_iKeyCount - 1;
}

bgBitmap * bgBitmapMgr::GetPtr(INT iKey)
{
	map<INT, bgBitmap*>::iterator itor;

	itor = m_List.find(iKey);
	if (itor == m_List.end())
		return NULL;

	return (*itor).second;
}

bgBitmap * bgBitmapMgr::GetPtr(TCHAR * szName)
{
	map<INT, bgBitmap*>::iterator itor;

	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		if (szName == (*itor).second->m_szName)
		{
			return (*itor).second;
		}
	}
	return NULL;
}

INT bgBitmapMgr::GetKey(TCHAR * szName)
{
	map<INT, bgBitmap*>::iterator itor;

	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		if (szName == (*itor).second->m_szName)
		{
			return (*itor).first;
		}
	}
	return NULL;
}

bool bgBitmapMgr::Release()
{
	map<INT, bgBitmap*>::iterator itor;
	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		bgBitmap* data = (*itor).second;
		delete data;
	}
	m_List.clear();
	return true;
}

bgBitmapMgr::bgBitmapMgr()
{
	m_iKeyCount = 0;
	m_List.clear();
}


bgBitmapMgr::~bgBitmapMgr()
{
	Release();
}
