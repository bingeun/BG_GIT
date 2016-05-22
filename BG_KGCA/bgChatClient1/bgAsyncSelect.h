#pragma once
#include "bgNetwork.h"

class bgAsyncSelect : public bgNetwork
{
public:
	bool	Connect(char* ip, int iPort);
	void	MsgEvent(MSG msg);

public:
	bgAsyncSelect();
	virtual ~bgAsyncSelect();
};
