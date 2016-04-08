#include "bgCore.h"


bool bgCore::GameInit()
{
	return true;
}

bool bgCore::GameFrame()
{
	return true;
}

bool bgCore::GameRender()
{
	return true;
}

bool bgCore::GameRelease()
{
	return true;
}

bool bgCore::GameRun()
{
	return true;
}

bool bgCore::Run()
{
	GameInit();

	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	while (msg.message != WM_QUIT)
	{
		// �޼��� ť���� ���� �޼��� 1�� ��������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg); // ���� �޼��� �ؼ�
			DispatchMessage(&msg); // �ؼ��� �޼����� ���ν����� ����
		}
		else
		{
			GameRun();
		}
	}
	GameRelease();

	return true;
}

bgCore::bgCore()
{
}


bgCore::~bgCore()
{
}
