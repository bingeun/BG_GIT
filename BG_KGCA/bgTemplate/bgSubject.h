#pragma once
#include <iostream>
#include <tchar.h>

using namespace std;

class bgSubject
{
private:
	int		m_iKor;
	int		m_iEng;
	int		m_iMat;

public:
	void	Set(int iKor, int iEng, int iMat);
	int		GetKor() { return m_iKor; }
	int		GetEng() { return m_iEng; }
	int		GetMat() { return m_iMat; }

public:
	bgSubject();
	virtual ~bgSubject();
};
