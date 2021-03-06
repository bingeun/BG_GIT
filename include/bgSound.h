#pragma once
#include "bgStd.h"
#include "fmod.hpp"
#include "fmod_errors.h"

#pragma comment(lib, "fmodex_vc.lib")
using namespace FMOD;

const int g_iMaxSound = 34;

class bgSound
{
public:
	int m_iSoundList;
	FMOD::System* m_pSystem;
	FMOD::Sound* m_pSound[g_iMaxSound];

	FMOD::Channel* m_pChannel[g_iMaxSound];
	TCHAR m_szBuffer[MAX_PATH];

public:
	bool Init();
	bool Frame();
	int Load(char* pLoadName, bool bPlay);
	void Play(int iIndex, bool bPlay);
	void Stop(int iIndex);
	void Stop();
	void Pause(int iIndex);
	void Volume(int iIndex, float fVolume, bool bUp);
	void SetLoop(int iIndex);
	void Release();
public:
	bgSound();
	virtual ~bgSound();
};

