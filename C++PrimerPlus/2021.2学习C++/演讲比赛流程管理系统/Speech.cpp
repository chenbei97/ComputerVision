#include "SpeechManager.h"
#include "Speaker.h"
int main()
{
	srand((unsigned int)time(NULL));
	SpeechManager wm;
	int choice = 0;
	// 测试代码 测试map容器是否成功得到了选手编号、分数、姓名
	//for (map<int, Speaker> ::iterator it = wm.m_Speaker.begin(); it != wm.m_Speaker.end(); it++)
	//{
	//	cout << "选手编号：" << it->first << " " <<
	//		"姓名：" << it->second._name << " " <<
	//		"分数：" << it->second._score[(wm.m_Index - 1)] << endl;
	//}
	while (true)
	{
		wm.show_Menu();// 菜单功能
		cout << "请输入您的选择" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1: //1. 开始演讲比赛
			wm.startSpeech();
			break;
		case 2:  // 2. 查看往届记录
			wm.viewTop3Speaker();
			break;
		case 3: // 3. 清空比赛记录
			wm.clearSpeaker();
			break;
		case 4: // 4. 退出比赛程序
			wm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	return 0;
}