#pragma once

class bgTimer
{
public:
	bool Init();
	bool Frame();
	bool Render();
	bool Release();
public:
	bgTimer();
	virtual ~bgTimer();
};

