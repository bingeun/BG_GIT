#include "bgIocp.h"



bool bgIocp::Init()
{
	m_hIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);
	if()
	return true;
}

bgIocp::bgIocp()
{
}


bgIocp::~bgIocp()
{
}
