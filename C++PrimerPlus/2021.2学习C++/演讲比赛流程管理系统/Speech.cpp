#include "SpeechManager.h"
#include "Speaker.h"
int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager wm;
	int choice = 0;
	// ���Դ��� ����map�����Ƿ�ɹ��õ���ѡ�ֱ�š�����������
	//for (map<int, Speaker> ::iterator it = wm.m_Speaker.begin(); it != wm.m_Speaker.end(); it++)
	//{
	//	cout << "ѡ�ֱ�ţ�" << it->first << " " <<
	//		"������" << it->second._name << " " <<
	//		"������" << it->second._score[(wm.m_Index - 1)] << endl;
	//}
	while (true)
	{
		wm.show_Menu();// �˵�����
		cout << "����������ѡ��" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: //1. ��ʼ�ݽ�����
			wm.startSpeech();
			break;
		case 2:  // 2. �鿴�����¼
			wm.viewTop3Speaker();
			break;
		case 3: // 3. ��ձ�����¼
			wm.clearSpeaker();
			break;
		case 4: // 4. �˳���������
			wm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}