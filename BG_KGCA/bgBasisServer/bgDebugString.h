#pragma once
#include "bgServerObj.h"

#define I_Debug bgDebugString::GetInstance()

class bgDebugString : public bgSingleton<bgDebugString>, public bgServerObj
{
private:
	friend class bgSingleton<bgDebugString>;

public:
	HWND	  m_hList;

public:
	void		Print(char* fmt, ...);

	bool		Init();
	bool		Release();
	WCHAR*		GetMbToWcs(const char* strMsg);
	char*		GetWcsToMbs(const WCHAR* strMsg);
	HRESULT		ConvertWideStringToAnsiCch(char* msg, const WCHAR* strMsg, int iRen);
	HRESULT		ConverAnsiStringToWideCch(WCHAR* msg, const char* strMsg, int nRen);
	void		T_ERROR(bool bPrint = false);

public:
	bgDebugString(void);
	~bgDebugString(void);
};
