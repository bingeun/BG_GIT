#pragma once
#include "bgServerStd.h"

class bgServerObj
{
public:
	CRITICAL_SECTION  m_cs;

public:
	bgServerObj(void);
	virtual ~bgServerObj(void);
};
