#include "bgFrameMgr.h"


INT bgFrameMgr::Add(TCHAR * pszName)
{
	FILE* fp;
	_wfopen_s(&fp, pszName, _T("rt"));
	if (fp == NULL)
		return false;

	TCHAR pBuffer[MAX_PATH] = { 0, };
	TCHAR szString[MAX_PATH] = { 0, };
	TCHAR szFileName[MAX_PATH] = { 0, };
	TCHAR szFileNameMask[MAX_PATH] = { 0, };
	int iTotalSprite = 0;
	int iTotalFrame = 0;
	int iTotalLoop = 0;

	// 한 줄 읽고(_fgetts), 구문 분석하여 변수에 저장(_stscanf_s)
	// #SPRITE(szString) 스프라이트수(iTotalSprite), 그림파일(szFileName), 마스크파일(szFileNameMask)
	_fgetts(pBuffer, _countof(pBuffer), fp);
	_stscanf_s(pBuffer, _T("%s%d%s%s"), szString, _countof(szString), &iTotalSprite, szFileName, _countof(szFileName), szFileNameMask, _countof(szFileNameMask));

	for (int iSprite = 0; iSprite < iTotalSprite; iSprite++)
	{
		// 스프라이트이름(szString), 프레임수(iTotalFrame), 반복횟수(-x무한, 0반복없음, +x회반복)
		_fgetts(pBuffer, _countof(pBuffer), fp);
		_stscanf_s(pBuffer, _T("%s%d%d"), szString, _countof(szString), &iTotalFrame, &iTotalLoop);

		bgBitmap* pBitmap = I_BitmapMgr.GetPtr(szFileName);

		// 같은 이름의 스프라이트가 존재한다면 해당 갯수만큼 건너띄기
		if (pBitmap)
		{
			for (int iFrame = 0; iFrame < iTotalFrame; iFrame++)
			{
				_fgetts(pBuffer, _countof(pBuffer), fp);
				// 존재하는 이름이므로 값저장 생략
				//_stscanf_s(pBuffer, _T("%d%f%d%d%d%d%d%d"), &iCount, &frame.fLifeTime, &frame.posDest.x, &frame.posDest.y,
				//	&frame.rectSrc.left, &frame.rectSrc.top, &frame.rectSrc.right, &frame.rectSrc.bottom);
			}
		}
		// 같은 이름의 스프라이트가 없으면 m_List 에 추가
		else
		{
			// 지정한 그림파일 로드하기
			INT iKey = I_BitmapMgr.Add(szFileName, szFileNameMask);
			pBitmap = I_BitmapMgr.GetPtr(iKey);

			bgFrame* data = new bgFrame;
			data->m_szName = szString;
			data->m_iTotalLoop = iTotalLoop;
			for (int iFrame = 0; iFrame < iTotalFrame; iFrame++)
			{
				int iCount;
				FRAME frame;

				// 프레임 카운트(iCount), 프레임 지속시간(fLifeTime), 출력시 중심점(x,y) BMP에서의 RECT(x,y,w,h)
				_fgetts(pBuffer, _countof(pBuffer), fp);
				_stscanf_s(pBuffer, _T("%d%f%d%d%d%d%d%d"), &iCount, &frame.fLifeTime, &frame.posDest.x, &frame.posDest.y,
					&frame.rectSrc.left, &frame.rectSrc.top, &frame.rectSrc.right, &frame.rectSrc.bottom);
				frame.pBitmap = pBitmap;

				data->m_vecFrame.push_back(frame);
			}
			m_List.insert(make_pair(m_iKeyCount++, data));
		}
	}
	fclose(fp);
	return m_iKeyCount - 1;
}

bgFrame * bgFrameMgr::GetPtr(INT iKey)
{
	map<INT, bgFrame*>::iterator itor;

	itor = m_List.find(iKey);
	if (itor == m_List.end())
		return NULL;

	return (*itor).second;
}

bgFrame * bgFrameMgr::GetPtr(TCHAR * szName)
{
	map<INT, bgFrame*>::iterator itor;

	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		if (szName == (*itor).second->m_szName)
		{
			return (*itor).second;
		}
	}
	return NULL;
}

INT bgFrameMgr::GetKey(TCHAR * szName)
{
	map<INT, bgFrame*>::iterator itor;

	for (itor = m_List.begin(); itor != m_List.end(); itor++)
	{
		if (szName == (*itor).second->m_szName)
		{
			return (*itor).first;
		}
	}
	return NULL;
}

bool bgFrameMgr::Release()
{
	return true;
}

bgFrameMgr::bgFrameMgr()
{
	m_iKeyCount = 0;
	m_List.clear();
}


bgFrameMgr::~bgFrameMgr()
{
	Release();
}

