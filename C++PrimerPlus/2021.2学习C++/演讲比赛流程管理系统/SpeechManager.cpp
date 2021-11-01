#include "SpeechManager.h"
SpeechManager::SpeechManager()
{
	this->initSpeech(); // 初始化属性
	this->createSpeaker(); // 初始化选手
	this->loadSpeaker(); // 加载往届记录
	
}
SpeechManager:: ~SpeechManager()
{

}
void SpeechManager::show_Menu()
{
	cout << "*************************************************" << endl;
	cout << "***********   欢迎参加演讲比赛!    **********" << endl;
	cout << "***********      1. 开始演讲比赛       **********" << endl;
	cout << "***********      2. 查看往届记录       **********" << endl;
	cout << "***********      3. 清空比赛记录       **********" << endl;
	cout << "***********      4. 退出比赛程序       **********" << endl;
	cout << "*************************************************" << endl;
	cout << endl;
}
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear(); // map容器也清空
	this->m_Index = 1; // 默认第一轮比赛
	this->m_Score.clear(); // 重制比赛时调用，把记录分数的也清空
}
void SpeechManager::createSpeaker()
{
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name = "选手";
		name += nameseed[i];
		// 调用选手类创建选手
		Speaker sp;
		// 初始化姓名
		sp._name = name;
		// 初始化分数
		for (int j  = 0; j< 2; j++)
		{
			sp._score[j] = 0;
		}
	    // 初始化选手编号 放入第一轮的容器v1
		this->v1.push_back(i + 10001);
		// 初始化map容器 存放编号和选手本身(姓名+分数)
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
void SpeechManager::chooseSpeech()
{
	cout << "第 <<  " << this->m_Index << "  >>轮比赛正在抽签" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "抽签后演讲顺序如下：" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(),v1.end());
		for (vector<int> ::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " "; // 输出第一轮演讲的选手编号顺序
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int> ::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " "; // 输出第一轮演讲的选手编号顺序
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------" << endl;
}
void SpeechManager::startContest() // 比赛函数
{
	cout << "--------------------第" << this->m_Index << "轮比赛正式开始--------------------" << endl;
	multimap<double, int, greater<double>> groupScore;
	// 临时容器 存放分数、编号(且按降序)  size=6 or 12
	int num = 0; // 记录人员数 6个一组
	vector<int> v_temp ; // 比赛的人员容器
	if (this->m_Index == 1)
	{
		v_temp = v1;
	}
	else 
	{
		v_temp = v2;
	}
	// 遍历某一轮的所有参赛选手v1或v2初始化分数
	for (vector<int> ::iterator it = v_temp.begin(); it != v_temp.end(); it++)
	{
		num++; // 用来计数
		//1. 评委打分
		deque<double> d; //分数的队列容器
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; //600~100
			d.push_back(score);
		}
		// 2.分数处理
		sort(d.begin(), d.end(), greater<double>()); // 降序
		d.pop_back();
		d.pop_front();//去掉最高最低分 也是为何选择deque容器的原因
		double sum = accumulate(d.begin(), d.end(), 0.0f);//起始值0,调用内置算法计算和
		double avarage = sum / (double)d.size(); // 都转化为double类型
	     
		// 3.每一轮得到的分数放入当初定义的选手属性score对应轮的位置
		this->m_Speaker[(*it)]._score[this->m_Index - 1] = avarage;

		// 4.  上方num计数 最大为6或者12 所以6人一组
		// 分数不仅要放入原有属性 也要放入临时容器(同时已经排好序)
		groupScore.insert(make_pair(avarage, *it)); // 对应上述的定义 存放的是分数和编号
		// 开始分组输出信息(按顺序即可)
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次为：" << endl;
			// 输出6人的信息
			for (multimap<double, int, greater<double>>::iterator it1 = groupScore.begin();
				it1 != groupScore.end(); it1++)
			{
				// multimap没有存放姓名 所以需要根据编号找到姓名
				// 分数也从从m_Speaker找 ，找到对应编号和对应轮数即可
				//  从multimap的first找也是可以的 it1->first
				cout << "编号：" << it1->second << "  姓名：" << this->m_Speaker[it1->second]._name
					<< "  分数：" <<this->m_Speaker[it1->second]._score[this->m_Index-1]<< endl;
			}
			// 取前3名放入 系统的固有属性v2或者vVictory 这里只有3人 不同于multimap全部存放
			int count = 0; // 用于取前3名的计数
			for (multimap<double, int, greater<double>>::iterator it1 = groupScore.begin();
				it1 != groupScore.end() && count <3 ; count++, it1++)
			{
				if (this->m_Index == 1)//淘汰赛的前3名编号存放于v2 6ren
				{
					this->v2.push_back((*it1).second);
				}
				else // 决赛的3名选手编号存放
				{
					this->vVictory.push_back((*it1).second);
				}
			}
			groupScore.clear(); // 分小组用的临时容器不需要了 防止第二小组在第一小组上追加
			cout << endl;
		}
	}
	cout << "--------------------第" << this->m_Index << "轮比赛结束--------------------" << endl;
}
void SpeechManager::saveScore()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//追加写入文件
	{
		for (vector<int> ::iterator it = vVictory.begin(); it != vVictory.end(); it++)
		{
			ofs << *it << "," << m_Speaker[*it]._score[1]<<",";
		}
		ofs << endl;
	   
	}
	ofs.close();
	cout << "选手信息已经成功保存！" << endl;
	cout << "本届比赛比赛完毕！" << endl;
	this->fiileIsEmpty = false;
	system("pause");
    system("cls");
	//this->show_Menu();
}
void SpeechManager::startSpeech()
{
	// 第一轮比赛
	// 1.抽签 -----> 抽签函数 void chooseSpeech();
	this->chooseSpeech();
	// 2.比赛
	this->startContest();
	// 3.显示晋级信息
	this->showSpeaker();
	// 第二轮比赛
	this->m_Index++;
	// 1.抽签
	this->chooseSpeech();
	// 2.比赛
	this->startContest();
	// 3.显示最终结果
	this->showSpeaker();
	// 4.保存分数
	this->saveScore();

	// 然后重置比赛 否则会继续到第3轮、第4轮
	this->initSpeech();
	this->createSpeaker();
	this->loadSpeaker();
}
void SpeechManager::showSpeaker()
{
	cout << "--------------------第" << this->m_Index << "轮晋级选手信息如下--------------------" << endl;
	vector<int> v;
	if (this->m_Index == 1)
	{
		v = v2;
	}
	else
	{
		v = vVictory;
	}
	for (vector<int> ::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号：" << (*it) << "  姓名：" << this->m_Speaker[*it]._name
			<< "  得分：" << this->m_Speaker[*it]._score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");//可以暂停观看下信息
	system("cls"); // 第一轮或者第二轮已经结束了 就清屏
	
	this->show_Menu(); // 重新显示菜单

}
void SpeechManager::loadSpeaker()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fiileIsEmpty = true;
		cout << "文件不存在！" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "文件为空！" << endl;
		this->fiileIsEmpty = true;
		ifs.close();
		return;
	}

	// 文件不为空
	cout << "历史记录文件打开成功！" << endl;
	this->fiileIsEmpty = false;
	ifs.putback(ch); // 读取的单个字符放回去
	string data;
	int index = 0; // 第几届
	while (ifs >> data)
	{
		// cout << data << endl; //测试用的如果不显示则注释掉
		vector<string> v;
		int pos = -1; // 记录逗号","的位置
		int start = 0; // 读取的文字起始位置
		
		// 先根据逗号得到分开的信息
		while (true)
		{
			pos = data.find(",", start);// 从0开始查找逗号","
			if (pos == -1)
			{
				break; //没找到分隔符
			}
			string tmp = data.substr(start, pos - start); // 得到起始位置到第一个逗号之间的文字
			v.push_back(tmp);  // v[0] = 编号 v[1] =分数
			start = pos + 1; // 起始位置改为逗号的下一个 准备截取下一段信息
		}
		// 这一行文字就被解析为三部分，每部分=编号+分数
		this->m_Score.insert(make_pair(index, v));// map<int, vector<string>> m_Score; /
		index++;  // 第几届
	}
	ifs.close();
	// 查看输出的信息
	for (map<int, vector<string>> ::iterator it = this->m_Score.begin(); it != this->m_Score.end(); it++)
	{
		cout << "第" << it->first + 1 << "届选手信息如下：" << endl;
		cout<< "\t冠军选手的编号为：" << it->second[0] <<
			"  分数为：" << it->second[1] << endl;
		cout << "\t亚军选手的编号为：" << it->second[2] <<
			"  分数为：" << it->second[3] << endl;
		cout  << "\t季军选手的编号为：" << it->second[4] <<
			"  分数为：" << it->second[5] << endl;
	}
	system("pause");
	system("cls");
}
void SpeechManager ::viewTop3Speaker()
{
	if (this->fiileIsEmpty)
	{
		cout << "文件不存在或者文件为空！" << endl;
	}
	else
	{
		cout << "历史记录文件打开成功！" << endl;
		for (int i = 0; i < this->m_Score.size(); i++) // 即上述的index=1~3
		{
			cout << "第" << i + 1 << "届选手信息如下：" << endl;
			cout << "\t冠军选手的编号为：" << this->m_Score[i][0] <<
				"  分数为：" << this->m_Score[i][1] << endl;
			cout << "\t亚军选手的编号为：" << this->m_Score[i][2] <<
				"  分数为：" << this->m_Score[i][3] << endl;
			cout << "\t季军选手的编号为：" << this->m_Score[i][4] <<
				"  分数为：" << this->m_Score[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearSpeaker()
{
	cout << "确认清空？" << endl;
	cout << "1. 确认" << endl;
	cout << "2. 返回" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc); //如果存在则删除后在创建
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadSpeaker();
		cout << "文件清空成功！" << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::exitSystem()
{
	cout << "欢迎下次使用！" << endl;
	//system("pause");
	exit(0);
}