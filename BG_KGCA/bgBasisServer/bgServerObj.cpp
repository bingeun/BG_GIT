#include "bgServerObj.h"


bgServerObj::bgServerObj(void)
{
	InitializeCriticalSection(&m_cs);
}


bgServerObj::~bgServerObj(void)
{
	DeleteCriticalSection(&m_cs);
}
