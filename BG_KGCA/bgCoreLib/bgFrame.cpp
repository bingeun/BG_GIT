#include "bgFrame.h"



void bgFrame::Set(wstring szName, int iTotalLoop)
{
	m_szName = szName;
	m_iTotalLoop = iTotalLoop;
}

void bgFrame::Add(FRAME & frame)
{
	m_vecFrame.push_back(frame);
}

bgFrame::bgFrame()
{
}


bgFrame::~bgFrame()
{
}
