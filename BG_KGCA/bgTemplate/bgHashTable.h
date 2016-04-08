#pragma once
#include "bgLinkedList.h"

template<class T>
class bgHashTable
{
public:
	bgLinkedList<T>*	m_pArray;
	int		m_iLength;

public:
	int		Hash(char* szName);
	void	Insert(T* newData);

public:
	bgHashTable(int iLength = 5);
	~bgHashTable();
};

template<class T>
int bgHashTable<T>::Hash(char * szName)
{
	int iValue = 0;
	int iLength = strlen(szName);
	for (int i = 0; i < iLength; i++)
	{
		iValue += szName[i];
	}
	int iKey = iValue % m_iLength;
	return iKey;
}

template<class T>
void bgHashTable<T>::Insert(T * newData)
{
	int iIndex = Hash(newData->GetName());
	m_pArray[iIndex].AddLink(newData);
}

template<class T>
bgHashTable<T>::bgHashTable(int iLength = 5)
{
	m_pArray = new bgLinkedList<T>[iLength];
	m_iLength = iLength;
}

template<class T>
bgHashTable<T>::~bgHashTable()
{
	delete[] m_pArray;
}
