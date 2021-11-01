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
	// vectorֻ��ѡ�ֱ��
	vector<int> v1; // ��̭��ѡ������ =12
	vector<int> v2; // ����ѡ������ = 6
	vector<int> vVictory; // ǰ3������ = 3
	
	// map��ѡ�ֵı�ź����ѡ�ֱ���(����������)
	// ��Ų����ظ� ����ʹ��map��ֵ��
	map<int, Speaker> m_Speaker; // ��ű�� �Լ�����ѡ�ֵ�����
	int m_Index;  // ��������

	// ������ʾ��ʷ��¼��Ҫ������(loadSpeaker()�е���)
	bool fiileIsEmpty; // ��ȡ�ļ��Ƿ�Ϊ��
	map<int, vector<string>> m_Score;// ��������¼������
	// int ��ʾ�ڼ��� vector<string>Ϊѡ�ָý�ǰ3�ı�źͷ���
	// ��Ϊ��ȡ�ļ����ַ���,���Ա�źͷ��������ַ�����ʽ
	
	SpeechManager();
	~SpeechManager();
	

	// SpeechManager���캯�����õĺ���
	void initSpeech(); // ��ʼ�����ԣ�ѡ������������������
	void createSpeaker(); // ��ʼ��ѡ��
	void chooseSpeech(); // ��ǩ����
	void startContest(); // ��������
	void showSpeaker(); // ��ʾĳһ�ֽ���ѡ����Ϣ
	void saveScore(); // �����������
	void loadSpeaker(); // ������ʷ��¼

	// ������main���õĺ���
	void show_Menu();
	void startSpeech();  // -��ʼ�ݽ�-->�����˳�ǩ���������������������������
	
	void clearSpeaker(); // ��ձ�����¼
	void viewTop3Speaker(); // �鿴������ѡ����Ϣ ������ʷ��¼����ֻ������
	void exitSystem(); // �˳�

};
