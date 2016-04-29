#pragma once
#include "bgStd.h"
#include "bgSys.h"
#include "bgObject.h"

#define BOARD_X		(25)
#define BOARD_Y		(25)
#define BOARD_W		(50)
#define BOARD_H		(34)
#define BLOCK_W		(15)
#define BLOCK_H		(15)

class objGround : public bgObject
{
public:
	bool	Init();
	bool	Frame();
	bool	Render();
	bool	Release();

public:
	objGround();
	virtual ~objGround();
};

