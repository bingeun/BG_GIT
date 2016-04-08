#include "bgManager.h"

void main()
{
	bgManager mgr;

	// 데이터 파일이 없을 경우 랜덤 데이터로 파일생성
	if (!mgr.ReadFile("student.txt"))
	{
		mgr.RandomData(10);
		mgr.WriteFile("student.txt");
	}

	int iMenu = 0;
	do
	{
		system("cls");
		cout << "=================== 성적관리 프로그램 ===================" << endl;
		cout
			<< setw(6) << "번호"
			<< setw(8) << "이름"
			<< setw(6) << "국어"
			<< setw(6) << "영어"
			<< setw(6) << "수학"
			<< setw(6) << "총점"
			<< setw(10) << "평균"
			<< setw(6) << "Hash"
			<< endl;

		mgr.Sort(false);
		mgr.ShowData();

		//cout << "------------------------------------------------------------" << endl;
		//char str[] = "CYSYY";
		//cout << "Find(" << str << ") : ";
		//mgr.ShowData(mgr.Find(str));
		//cout << "Find(  3  ) : ";
		//mgr.ShowData(mgr.Find(3));
		//cout << "Find( 999 ) : ";
		//mgr.ShowData(mgr.Find(999));
		cout << "============================================================" << endl;

		cout << " 1-추가 2-수정 3-삭제 0-종료 : ";
		cin >> iMenu;

		switch (iMenu)
		{
		case 1: // 추가
		{
			int iIndex, iKor, iEng, iMat;
			char szName[10];
			cout << "------------------------------------------------------------" << endl;
			cout << "번호 : ";
			cin >> iIndex;
			cout << "이름 : ";
			cin >> szName;
			cout << "국어 : ";
			cin >> iKor;
			cout << "영어 : ";
			cin >> iEng;
			cout << "수학 : ";
			cin >> iMat;
			
			bgStudent* tempStudent = new bgStudent;
			tempStudent->SetIndex(iIndex);
			tempStudent->SetName(szName);
			tempStudent->SetSubject(iKor, iEng, iMat);

			mgr.m_List.AddLink(tempStudent);
			mgr.Sort();
		}
			break;
		case 2: // 수정
		{
			int iIndex, iKor, iEng, iMat;
			char szName[10];
			cout << "------------------------------------------------------------" << endl;
			cout << "수정하려는 학생의 번호 : ";
			cin >> iIndex;

			if(mgr.Find(iIndex))
			{
				cout << "이름 : ";
				cin >> szName;
				cout << "국어 : ";
				cin >> iKor;
				cout << "영어 : ";
				cin >> iEng;
				cout << "수학 : ";
				cin >> iMat;

				mgr.Del(iIndex);

				bgStudent* tempStudent = new bgStudent;
				tempStudent->SetIndex(iIndex);
				tempStudent->SetName(szName);
				tempStudent->SetSubject(iKor, iEng, iMat);

				mgr.m_List.AddLink(tempStudent);
				mgr.Sort();
			}
			//else
			//{
			//	cout << "해당 번호의 학생정보가 존재하지 않습니다." << endl;
			//	cin >> iIndex;
			//}
		}
			break;
		case 3: // 삭제
		{
			int iIndex;
			cout << "------------------------------------------------------------" << endl;
			cout << "삭제하려는 학생의 번호 : ";
			cin >> iIndex;

			bgStudent* pFind;
			if (pFind = mgr.Find(iIndex))
			{
				mgr.Del(iIndex);
			}
			//else
			//{
			//	cout << "해당 번호의 학생정보가 존재하지 않습니다." << endl;
			//	cin >> iIndex;
			//}
		}
			break;
		default:
			break;
		}
	} while (iMenu);

	mgr.WriteFile("student.txt");

	return;
}
