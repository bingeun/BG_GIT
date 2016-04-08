#include "bgManager.h"

void main()
{
	bgManager mgr;

	// ������ ������ ���� ��� ���� �����ͷ� ���ϻ���
	if (!mgr.ReadFile("student.txt"))
	{
		mgr.RandomData(10);
		mgr.WriteFile("student.txt");
	}

	int iMenu = 0;
	do
	{
		system("cls");
		cout << "=================== �������� ���α׷� ===================" << endl;
		cout
			<< setw(6) << "��ȣ"
			<< setw(8) << "�̸�"
			<< setw(6) << "����"
			<< setw(6) << "����"
			<< setw(6) << "����"
			<< setw(6) << "����"
			<< setw(10) << "���"
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

		cout << " 1-�߰� 2-���� 3-���� 0-���� : ";
		cin >> iMenu;

		switch (iMenu)
		{
		case 1: // �߰�
		{
			int iIndex, iKor, iEng, iMat;
			char szName[10];
			cout << "------------------------------------------------------------" << endl;
			cout << "��ȣ : ";
			cin >> iIndex;
			cout << "�̸� : ";
			cin >> szName;
			cout << "���� : ";
			cin >> iKor;
			cout << "���� : ";
			cin >> iEng;
			cout << "���� : ";
			cin >> iMat;
			
			bgStudent* tempStudent = new bgStudent;
			tempStudent->SetIndex(iIndex);
			tempStudent->SetName(szName);
			tempStudent->SetSubject(iKor, iEng, iMat);

			mgr.m_List.AddLink(tempStudent);
			mgr.Sort();
		}
			break;
		case 2: // ����
		{
			int iIndex, iKor, iEng, iMat;
			char szName[10];
			cout << "------------------------------------------------------------" << endl;
			cout << "�����Ϸ��� �л��� ��ȣ : ";
			cin >> iIndex;

			if(mgr.Find(iIndex))
			{
				cout << "�̸� : ";
				cin >> szName;
				cout << "���� : ";
				cin >> iKor;
				cout << "���� : ";
				cin >> iEng;
				cout << "���� : ";
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
			//	cout << "�ش� ��ȣ�� �л������� �������� �ʽ��ϴ�." << endl;
			//	cin >> iIndex;
			//}
		}
			break;
		case 3: // ����
		{
			int iIndex;
			cout << "------------------------------------------------------------" << endl;
			cout << "�����Ϸ��� �л��� ��ȣ : ";
			cin >> iIndex;

			bgStudent* pFind;
			if (pFind = mgr.Find(iIndex))
			{
				mgr.Del(iIndex);
			}
			//else
			//{
			//	cout << "�ش� ��ȣ�� �л������� �������� �ʽ��ϴ�." << endl;
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
