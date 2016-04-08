#include "bgStudent.h"

void bgStudent::SetName(char* szName)
{
	strcpy(m_szName, szName);
}

void bgStudent::SetSubject(int iKor, int iEng, int iMat)
{
	m_Subject.Set(iKor, iEng, iMat);
	m_iTotal = m_Subject.GetKor() + m_Subject.GetEng() + m_Subject.GetMat();
	m_fAverage = m_iTotal / 3.0f;
}

bgStudent::bgStudent()
{
	m_iIndex = -1;
	m_iTotal = 0;
	m_fAverage = 0.0f;
}

bgStudent::~bgStudent()
{
}
