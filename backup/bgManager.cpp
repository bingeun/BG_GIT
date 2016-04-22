#include "bgManager.h"

bgNode<bgStudent> * bgManager::Swap(bgNode<bgStudent>** pA, bgNode<bgStudent>** pB)
{
	// 교환할 포인터 변수들 (인자로 넘어온 pA, pB 포함)
	bgNode<bgStudent>* pAPrev = (*pA)->m_pPrev;
	bgNode<bgStudent>* pANext = (*pA)->m_pNext;
	bgNode<bgStudent>* pBPrev = (*pB)->m_pPrev;
	bgNode<bgStudent>* pBNext = (*pB)->m_pNext;

	// 원래의 주소값들을 보존(Keep)할 포인터변수들
	bgNode<bgStudent>* pKeepA = (*pA);
	bgNode<bgStudent>* pKeepB = (*pB);
	bgNode<bgStudent>* pKeepAPrev = pAPrev;
	bgNode<bgStudent>* pKeepANext = pANext;
	bgNode<bgStudent>* pKeepBPrev = pBPrev;
	bgNode<bgStudent>* pKeepBNext = pBNext;

	// A와 B가 붙어 있다면...
	if (pKeepA == pKeepBPrev || pKeepB == pKeepANext)
	{
		// A의 이전 노드 존재 여부에 따른 처리
		if (pKeepAPrev)
			pAPrev->m_pNext = pKeepB;
		else
			m_List.m_pHead = pKeepB;

		// B의 다음 노드 존재 여부에 따른 처리
		if (pKeepBNext)
			pBNext->m_pPrev = pKeepA;
		else
			m_List.m_pTail = pKeepA;

		// A, B 노드 각각의 이전과 다음 노드 포인터값 지정
		(*pA)->m_pPrev = pKeepB;
		(*pA)->m_pNext = pKeepBNext;
		(*pB)->m_pPrev = pKeepAPrev;
		(*pB)->m_pNext = pKeepA;
		(*pA) = pKeepB;
		(*pB) = pKeepA;
	}
	// 한 칸이상 건너띄워져 있다면...
	else
	{
		// A의 이전 노드 존재 여부에 따른 처리
		if (pKeepAPrev)
			pAPrev->m_pNext = pKeepB;
		else
			m_List.m_pHead = pKeepB;

		// B의 다음 노드 존재 여부에 따른 처리
		if (pKeepBNext)
			pBNext->m_pPrev = pKeepA;
		else
			m_List.m_pTail = pKeepA;

		// A, B 사이에 있는 노드 처리
		pANext->m_pPrev = pKeepB;
		pBPrev->m_pNext = pKeepA;

		// A, B 노드 각각의 이전과 다음 노드 포인터값 지정
		(*pA)->m_pPrev = pKeepBPrev;
		(*pA)->m_pNext = pKeepBNext;
		(*pB)->m_pPrev = pKeepAPrev;
		(*pB)->m_pNext = pKeepANext;
		(*pA) = pKeepB;
		(*pB) = pKeepA;
	}

	return pKeepBNext;
}

void bgManager::Sort(bool bUp) //= true)
{
	// pNodeA = 비교기준노드, pNodeB = 비교대상노드
	bgNode<bgStudent>* pNodeA = m_List.GetHead();
	bgNode<bgStudent>* pNodeB = NULL;

	// 노드가 2개 이상이면 노드B 셋팅
	if (pNodeA && pNodeA->m_pNext)
		pNodeB = pNodeA->m_pNext;
	else
		return;

	// 비교기준노드(pNodeA) 루프
	do
	{
		// 비교대상노드(pNodeB) 루프
		do
		{
			// 총점 비교(오름차순) 후 노드 교환
			if (bUp)
			{
				if (pNodeA->m_pData->GetTotal() > pNodeB->m_pData->GetTotal())
					pNodeB = Swap(&pNodeA, &pNodeB);
				else if (pNodeB->m_pNext)
					pNodeB = pNodeB->m_pNext;
				else
					break;
			}
			// 총점 비교(내림차순) 후 노드 교환
			else
			{
				if (pNodeA->m_pData->GetTotal() < pNodeB->m_pData->GetTotal())
					pNodeB = Swap(&pNodeA, &pNodeB);
				else if (pNodeB->m_pNext)
					pNodeB = pNodeB->m_pNext;
				else
					break;
			}

		} while (pNodeB);

		// A노드 이동(A+1), B노드를 A노드의 다음노드(A+2)로 셋팅
		pNodeA = pNodeA->m_pNext;
		pNodeB = pNodeA->m_pNext;

	} while (pNodeB);
}

void bgManager::RandomData(int iLength)
{
	for (int iCount = 0; iCount < iLength; iCount++)
	{
		char szName[10];
		bgStudent* pStudent = new bgStudent;

		for (int iName = 0; iName < 5; iName++)
		{
			char cWord = 65 + rand() % 26;
			szName[iName] = cWord;
		}
		szName[5] = 0;
		pStudent->SetName(szName);
		pStudent->SetIndex(iCount);
		pStudent->SetSubject(rand() % 101, rand() % 101, rand() % 101);

		m_List.AddLink(pStudent);
		m_Hash.Insert(pStudent);
	}
}

bgStudent * bgManager::Find(int iIndex)
{
	bgNode<bgStudent>* pFind = m_List.m_pHead;
	while(pFind)
	{
		if (pFind->m_pData->GetIndex() == iIndex)
			return pFind->m_pData;
		pFind = pFind->m_pNext;
	}
	return NULL;
}

bgStudent * bgManager::Find(char* szName)
{
	bgNode<bgStudent>* pFind = m_List.m_pHead;
	while (pFind)
	{
		if (strcmp(szName, pFind->m_pData->GetName()) == 0)
			return pFind->m_pData;
		pFind = pFind->m_pNext;
	}
	return NULL;
}

void bgManager::Del(int iIndex)
{
	bgNode<bgStudent>* pFind = m_List.m_pHead;
	bgNode<bgStudent>* pFindPrev;
	bgNode<bgStudent>* pFindNext;
	while (pFind)
	{
		if (pFind->m_pData->GetIndex() == iIndex)
		{
			pFindPrev = pFind->m_pPrev;
			pFindNext = pFind->m_pNext;
			
			if (pFindPrev)
				pFindPrev->m_pNext = pFindNext;
			else
				m_List.m_pHead = pFindNext;

			if (pFindNext)
				pFindNext->m_pPrev = pFindPrev;
			else
				m_List.m_pTail = pFindPrev;

			delete pFind;
			return;
		}
		pFind = pFind->m_pNext;
	}
}

void bgManager::Del(char * szName)
{
	bgNode<bgStudent>* pFind = m_List.m_pHead;
	bgNode<bgStudent>* pFindPrev;
	bgNode<bgStudent>* pFindNext;
	while (pFind)
	{
		if (strcmp(szName, pFind->m_pData->GetName()) == 0)
		{
			pFindPrev = pFind->m_pPrev;
			pFindNext = pFind->m_pNext;

			if (pFindPrev)
				pFindPrev->m_pNext = pFindNext;
			if (pFindNext)
				pFindNext->m_pPrev = pFindPrev;

			delete pFind;
			return;
		}
		pFind = pFind->m_pNext;
	}
}

void bgManager::ShowData()
{
	for (bgNode<bgStudent>* pLink = m_List.m_pHead; pLink != NULL; pLink = pLink->m_pNext)
	{
		ShowData(pLink->m_pData);
	}
}

void bgManager::ShowData(bgStudent * pStudent)
{
	if (pStudent)
	{
		char* pszName = pStudent->GetName();
		wcout
			<< setw(6) << pStudent->GetIndex()
			<< setw(8) << pStudent->GetName()
			<< setw(6) << pStudent->GetSubject().GetKor()
			<< setw(6) << pStudent->GetSubject().GetEng()
			<< setw(6) << pStudent->GetSubject().GetMat()
			<< setw(6) << pStudent->GetTotal()
			<< setw(10) << pStudent->GetAverage()
			<< setw(6) << m_Hash.Hash(pszName)
			<< endl;
	}
	else
	{
		wcout << "＃＃＃ 해당하는 정보를 찾을 수 없습니다. ＃＃＃" << endl;
	}
}

void bgManager::WriteFile(char* szFileName)
{
	ofstream outFile;
	outFile.open(szFileName);

	outFile << "=================== 성적관리 프로그램 ===================" << endl;
	outFile
		<< setw(6) << "번호"
		<< setw(8) << "이름"
		<< setw(6) << "국어"
		<< setw(6) << "영어"
		<< setw(6) << "수학"
		<< setw(6) << "총점"
		<< setw(10) << "평균"
		<< endl;
	for (bgNode<bgStudent>* pLink = m_List.m_pHead; pLink != NULL; pLink = pLink->m_pNext)
	{
		outFile
			<< setw(6) << pLink->m_pData->GetIndex()
			<< setw(8) << pLink->m_pData->GetName()
			<< setw(6) << pLink->m_pData->GetSubject().GetKor()
			<< setw(6) << pLink->m_pData->GetSubject().GetEng()
			<< setw(6) << pLink->m_pData->GetSubject().GetMat()
			<< setw(6) << pLink->m_pData->GetTotal()
			<< setw(10) << pLink->m_pData->GetAverage()
			<< endl;
	}
	outFile.close();
}

bool bgManager::ReadFile(char* szFileName)
{
	ifstream inFile;

	// 지정한 이름의 파일 열기
	inFile.open(szFileName);
	if (inFile.fail())
		return false;

	char tempBuffer[100];
	inFile.getline(tempBuffer, sizeof(tempBuffer)); // ======= 성적관리 프로그램 =======
	inFile.getline(tempBuffer, sizeof(tempBuffer)); // 번호 이름 국어 영어 수학 총점 평균



	// 임시로 학생 한 명의 데이터를 보관할 변수들
	int		iIndex;
	int		iKor;
	int		iEng;
	int		iMat;
	int		iTotal;
	float	fAverage;
	char	szName[10];

	while (inFile >> iIndex >> szName >> iKor >> iEng >> iMat >> iTotal >> fAverage)
	{
		if (inFile.eof())
			break;

		bgStudent* tempStudent = new bgStudent;
		tempStudent->SetIndex(iIndex);
		tempStudent->SetName(szName);
		tempStudent->SetSubject(iKor, iEng, iMat);

		m_List.AddLink(tempStudent);
		m_Hash.Insert(tempStudent);
	}
	inFile.close();

	return true;
}

void bgManager::Release()
{
	bgNode<bgStudent>* pDel = 0;
	bgNode<bgStudent>* pLink = m_List.m_pHead;
	while (pLink != NULL)
	{
		pDel = pLink;
		pLink = pLink->m_pNext;
		delete pDel->m_pData;
		delete pDel;
	}
}

bgManager::bgManager()
{
}

bgManager::~bgManager()
{
	//Release();
}
