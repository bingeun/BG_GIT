#pragma once
#include <iostream>
#include <iomanip>

template<class T>
class bgNode
{
public:
	T*		m_pData;
	bgNode*	m_pPrev;
	bgNode*	m_pNext;

public:
	void	Delete();

public:
	bgNode();
	~bgNode();
};

template <class T>
void bgNode<T>::Delete()
{
	if (m_pData)
		delete m_pData;
}

template <class T>
bgNode<T>::bgNode()
{
	m_pData = NULL;
	m_pNext = m_pPrev = NULL;
}

template <class T>
bgNode<T>::~bgNode()
{
	//Delete();
}
