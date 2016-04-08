#include "bgSubject.h"

void bgSubject::Set(int iKor, int iEng, int iMat)
{
	m_iKor = iKor;
	m_iEng = iEng;
	m_iMat = iMat;
}

bgSubject::bgSubject()
{
	m_iKor = 0;
	m_iEng = 0;
	m_iMat = 0;
}

bgSubject::~bgSubject()
{
}
