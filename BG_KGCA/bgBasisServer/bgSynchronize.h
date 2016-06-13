#pragma once
#include "bgServerObj.h"

class bgSynchronize
{
public:
	bgServerObj* m_pServerObj;

public:
	bgSynchronize(bgServerObj* pObj);
	virtual ~bgSynchronize(void);
};
