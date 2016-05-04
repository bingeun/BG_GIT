#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

#define SCORE_X (775)
#define SCORE_Y (550)

class objFont : public bgObject
{
public:
	void	PrintNumber(int iNumber, int pX, int pY);

public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objFont();
	virtual ~objFont();
};

