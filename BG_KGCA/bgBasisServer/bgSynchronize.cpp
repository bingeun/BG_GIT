#include "bgSynchronize.h"


bgSynchronize::bgSynchronize(bgServerObj* pObj) : m_pServerObj(pObj)
{
	if (pObj == NULL) return;
	EnterCriticalSection(&pObj->m_cs);
}


bgSynchronize::~bgSynchronize(void)
{
	if (m_pServerObj == NULL) return;
	LeaveCriticalSection(&m_pServerObj->m_cs);
}
