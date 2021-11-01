#pragma once
#include "Speaker.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <deque>
#include <algorithm>
#include <numeric>
#include <ctime>
#include <string>
#include <functional> 
using namespace std;
class SpeechManager
{
public:
	// vector只放选手编号
	vector<int> v1; // 淘汰赛选手容器 =12
	vector<int> v2; // 决赛选手容器 = 6
	vector<int> vVictory; // 前3名容器 = 3
	
	// map放选手的编号和这个选手本身(姓名、分数)
	// 编号不会重复 可以使用map键值对
	map<int, Speaker> m_Speaker; // 存放编号 以及具体选手的容器
	int m_Index;  // 比赛轮数

	// 用于显示历史记录需要的属性(loadSpeaker()中调用)
	bool fiileIsEmpty; // 读取文件是否为空
	map<int, vector<string>> m_Score;// 存放往届记录的容器
	// int 表示第几届 vector<string>为选手该届前3的编号和分数
	// 因为读取文件是字符串,所以编号和分数都是字符串形式
	
	SpeechManager();
	~SpeechManager();
	

	// SpeechManager构造函数调用的函数
	void initSpeech(); // 初始化属性，选手容器、比赛轮数等
	void createSpeaker(); // 初始化选手
	void chooseSpeech(); // 抽签函数
	void startContest(); // 比赛函数
	void showSpeaker(); // 显示某一轮晋级选手信息
	void saveScore(); // 保存分数函数
	void loadSpeaker(); // 加载历史记录

	// 主程序main调用的函数
	void show_Menu();
	void startSpeech();  // -开始演讲-->调用了抽签函数、比赛函数、保存分数函数
	
	void clearSpeaker(); // 清空比赛记录
	void viewTop3Speaker(); // 查看真正的选手信息 加载历史记录那里只是数据
	void exitSystem(); // 退出

};
