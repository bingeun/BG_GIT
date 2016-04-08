#pragma once
#include "bgNode.h"

template<class T>
class bgLinkedList
{
public:
	int			m_iCount;
	bgNode<T>*	m_pHead;
	bgNode<T>*	m_pTail;

public:
	bgNode<T>*	GetHead() { return m_pHead; }

	bool		AddLink(T* pData);
	void		DelLink(bgNode<T>* pDel);
	void		Release();

public:
	bgLinkedList();
	~bgLinkedList();
};

template <class T>
bool bgLinkedList<T>::AddLink(T * pData)
{
	bgNode<T>* pNode = new bgNode<T>();
	pNode->m_pData = pData;

	if (m_pHead == NULL)
	{
		m_pHead = pNode;
		m_pTail = pNode;
	}
	else
	{
		pNode->m_pPrev = m_pTail;
		m_pTail->m_pNext = pNode;
		m_pTail = pNode;
	}
	m_iCount++;
	return true;
}

template<class T>
void bgLinkedList<T>::DelLink(bgNode<T>* pDel)
{
	bgNode<T>* pDelPrev = pDel->m_pPrev;
	bgNode<T>* pDelNext = pDel->m_pNext;
	pDel->m_pPrev->m_pNext = pDelNext;
	pDel->m_pNext->m_pPrev = pDelPrev;
	delete pDel;
}

template<class T>
void bgLinkedList<T>::Release()
{
	if (m_pHead)
	{
		bgNode<T>* pDel = m_pHead;
		bgNode<T>* pDelNext = m_pHead->m_pNext;
		while (pDel)
		{
			delete pDel;
			pDel = pDelNext;
			if (pDelNext)
				pDelNext = pDelNext->m_pNext;
		}
	}
	m_pHead = m_pTail = NULL;
}

template<class T>
bgLinkedList<T>::bgLinkedList()
{
	m_iCount = 0;
	m_pHead = NULL;
	m_pTail = NULL;
}

template<class T>
bgLinkedList<T>::~bgLinkedList()
{
	//Release();
}
