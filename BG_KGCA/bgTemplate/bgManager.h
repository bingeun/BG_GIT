#pragma once
#include <fstream>
#include "bgStudent.h"
#include "bgHashTable.h"
#include "bgLinkedList.h"

class bgManager
{
public:
	bgLinkedList<bgStudent> m_List;
	bgHashTable<bgStudent> m_Hash;

public:
	bgNode<bgStudent>*	Swap(bgNode<bgStudent>** pA, bgNode<bgStudent>** pB);
	void		Sort(bool bUp = true);
	bgStudent*	Find(int iIndex);
	bgStudent*	Find(char* szName);
	void		Del(int iIndex);
	void		Del(char* szName);

	void		RandomData(int iLength);
	void		ShowData();
	void		ShowData(bgStudent* pStudent);

	void		WriteFile(char* szFileName);
	bool		ReadFile(char* szFileName);

	void		Release();

public:
	bgManager();
	virtual ~bgManager();
};

//template <typename T>
//void SwapPoint(T* a, T* b)
//{
//	a->m_pNext = b;
//	b->m_pPrev = a;
//}
