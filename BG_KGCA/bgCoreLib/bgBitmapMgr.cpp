#include "bgBitmapMgr.h"


int bgBitmapMgr::Add(TCHAR * pszName)
{
	bgNode<bgBitmap>* pNode = m_List.m_pHead;
	while (pNode)
	{
		if (!_tcsicmp(pszName, pNode->m_pData->GetName()))
			return pNode->m_pData->GetIndex();
		pNode = pNode->m_pNext;
	}
	bgBitmap* newBitmap = new bgBitmap;
	newBitmap->Init();
	if (newBitmap->Load(pszName))
	{
		m_List.AddLink(newBitmap);
		m_iCounter++;
	}
	return m_iCounter - 1;
}

bgBitmap * bgBitmapMgr::GetBitmap(int iIndex)
{
	bgNode<bgBitmap>* pNode = m_List.m_pHead;
	while (pNode)
	{
		if (pNode->m_pData->GetIndex() == iIndex)
			return pNode->m_pData;
		pNode = pNode->m_pNext;
	}
	return NULL;
}

bool bgBitmapMgr::Release()
{
	bgNode<bgBitmap>* pNode = m_List.m_pHead;
	bgNode<bgBitmap>* pNodeNext;
	while (pNode)
	{
		pNodeNext = pNode->m_pNext;
		delete pNode;
		pNode = pNodeNext;
	}
	return true;
}

bgBitmapMgr::bgBitmapMgr()
{
	m_iCounter = 0;
}


bgBitmapMgr::~bgBitmapMgr()
{
	Release();
}
