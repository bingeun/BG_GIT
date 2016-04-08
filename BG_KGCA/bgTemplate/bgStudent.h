#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "bgSubject.h"

class bgStudent
{
private:
	int			m_iIndex;
	int			m_iTotal;
	float		m_fAverage;
	char		m_szName[10];
	bgSubject	m_Subject;

public:
	void		SetIndex(int iIndex) { m_iIndex = iIndex; }
	void		SetName(char* szName);
	void		SetSubject(int iKor, int iEng, int iMat);

	int			GetIndex() { return m_iIndex; }
	char*		GetName() { return m_szName; }
	bgSubject	GetSubject() { return m_Subject; }

	int			GetTotal() { return m_iTotal; }
	float		GetAverage() { return m_fAverage = m_iTotal / 3.0f; }

public:
	bgStudent();
	~bgStudent();
};
