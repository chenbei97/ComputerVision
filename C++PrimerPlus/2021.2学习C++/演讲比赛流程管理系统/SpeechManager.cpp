#include "SpeechManager.h"
SpeechManager::SpeechManager()
{
	this->initSpeech(); // ��ʼ������
	this->createSpeaker(); // ��ʼ��ѡ��
	this->loadSpeaker(); // ���������¼
	
}
SpeechManager:: ~SpeechManager()
{

}
void SpeechManager::show_Menu()
{
	cout << "*************************************************" << endl;
	cout << "***********   ��ӭ�μ��ݽ�����!    **********" << endl;
	cout << "***********      1. ��ʼ�ݽ�����       **********" << endl;
	cout << "***********      2. �鿴�����¼       **********" << endl;
	cout << "***********      3. ��ձ�����¼       **********" << endl;
	cout << "***********      4. �˳���������       **********" << endl;
	cout << "*************************************************" << endl;
	cout << endl;
}
void SpeechManager::initSpeech()
{
	this->v1.clear();
	this->v2.clear();
	this->vVictory.clear();
	this->m_Speaker.clear(); // map����Ҳ���
	this->m_Index = 1; // Ĭ�ϵ�һ�ֱ���
	this->m_Score.clear(); // ���Ʊ���ʱ���ã��Ѽ�¼������Ҳ���
}
void SpeechManager::createSpeaker()
{
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name = "ѡ��";
		name += nameseed[i];
		// ����ѡ���ഴ��ѡ��
		Speaker sp;
		// ��ʼ������
		sp._name = name;
		// ��ʼ������
		for (int j  = 0; j< 2; j++)
		{
			sp._score[j] = 0;
		}
	    // ��ʼ��ѡ�ֱ�� �����һ�ֵ�����v1
		this->v1.push_back(i + 10001);
		// ��ʼ��map���� ��ű�ź�ѡ�ֱ���(����+����)
		this->m_Speaker.insert(make_pair(i + 10001, sp));
	}
}
void SpeechManager::chooseSpeech()
{
	cout << "�� <<  " << this->m_Index << "  >>�ֱ������ڳ�ǩ" << endl;
	cout << "-------------------------------------------------------------" << endl;
	cout << "��ǩ���ݽ�˳�����£�" << endl;
	if (this->m_Index == 1)
	{
		random_shuffle(v1.begin(),v1.end());
		for (vector<int> ::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " "; // �����һ���ݽ���ѡ�ֱ��˳��
		}
		cout << endl;
	}
	else
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int> ::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " "; // �����һ���ݽ���ѡ�ֱ��˳��
		}
		cout << endl;
	}
	cout << "-------------------------------------------------------------" << endl;
}
void SpeechManager::startContest() // ��������
{
	cout << "--------------------��" << this->m_Index << "�ֱ�����ʽ��ʼ--------------------" << endl;
	multimap<double, int, greater<double>> groupScore;
	// ��ʱ���� ��ŷ��������(�Ұ�����)  size=6 or 12
	int num = 0; // ��¼��Ա�� 6��һ��
	vector<int> v_temp ; // ��������Ա����
	if (this->m_Index == 1)
	{
		v_temp = v1;
	}
	else 
	{
		v_temp = v2;
	}
	// ����ĳһ�ֵ����в���ѡ��v1��v2��ʼ������
	for (vector<int> ::iterator it = v_temp.begin(); it != v_temp.end(); it++)
	{
		num++; // ��������
		//1. ��ί���
		deque<double> d; //�����Ķ�������
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f; //600~100
			d.push_back(score);
		}
		// 2.��������
		sort(d.begin(), d.end(), greater<double>()); // ����
		d.pop_back();
		d.pop_front();//ȥ�������ͷ� Ҳ��Ϊ��ѡ��deque������ԭ��
		double sum = accumulate(d.begin(), d.end(), 0.0f);//��ʼֵ0,���������㷨�����
		double avarage = sum / (double)d.size(); // ��ת��Ϊdouble����
	     
		// 3.ÿһ�ֵõ��ķ������뵱�������ѡ������score��Ӧ�ֵ�λ��
		this->m_Speaker[(*it)]._score[this->m_Index - 1] = avarage;

		// 4.  �Ϸ�num���� ���Ϊ6����12 ����6��һ��
		// ��������Ҫ����ԭ������ ҲҪ������ʱ����(ͬʱ�Ѿ��ź���)
		groupScore.insert(make_pair(avarage, *it)); // ��Ӧ�����Ķ��� ��ŵ��Ƿ����ͱ��
		// ��ʼ���������Ϣ(��˳�򼴿�)
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������Ϊ��" << endl;
			// ���6�˵���Ϣ
			for (multimap<double, int, greater<double>>::iterator it1 = groupScore.begin();
				it1 != groupScore.end(); it1++)
			{
				// multimapû�д������ ������Ҫ���ݱ���ҵ�����
				// ����Ҳ�Ӵ�m_Speaker�� ���ҵ���Ӧ��źͶ�Ӧ��������
				//  ��multimap��first��Ҳ�ǿ��Ե� it1->first
				cout << "��ţ�" << it1->second << "  ������" << this->m_Speaker[it1->second]._name
					<< "  ������" <<this->m_Speaker[it1->second]._score[this->m_Index-1]<< endl;
			}
			// ȡǰ3������ ϵͳ�Ĺ�������v2����vVictory ����ֻ��3�� ��ͬ��multimapȫ�����
			int count = 0; // ����ȡǰ3���ļ���
			for (multimap<double, int, greater<double>>::iterator it1 = groupScore.begin();
				it1 != groupScore.end() && count <3 ; count++, it1++)
			{
				if (this->m_Index == 1)//��̭����ǰ3����Ŵ����v2 6ren
				{
					this->v2.push_back((*it1).second);
				}
				else // ������3��ѡ�ֱ�Ŵ��
				{
					this->vVictory.push_back((*it1).second);
				}
			}
			groupScore.clear(); // ��С���õ���ʱ��������Ҫ�� ��ֹ�ڶ�С���ڵ�һС����׷��
			cout << endl;
		}
	}
	cout << "--------------------��" << this->m_Index << "�ֱ�������--------------------" << endl;
}
void SpeechManager::saveScore()
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);//׷��д���ļ�
	{
		for (vector<int> ::iterator it = vVictory.begin(); it != vVictory.end(); it++)
		{
			ofs << *it << "," << m_Speaker[*it]._score[1]<<",";
		}
		ofs << endl;
	   
	}
	ofs.close();
	cout << "ѡ����Ϣ�Ѿ��ɹ����棡" << endl;
	cout << "�������������ϣ�" << endl;
	this->fiileIsEmpty = false;
	system("pause");
    system("cls");
	//this->show_Menu();
}
void SpeechManager::startSpeech()
{
	// ��һ�ֱ���
	// 1.��ǩ -----> ��ǩ���� void chooseSpeech();
	this->chooseSpeech();
	// 2.����
	this->startContest();
	// 3.��ʾ������Ϣ
	this->showSpeaker();
	// �ڶ��ֱ���
	this->m_Index++;
	// 1.��ǩ
	this->chooseSpeech();
	// 2.����
	this->startContest();
	// 3.��ʾ���ս��
	this->showSpeaker();
	// 4.�������
	this->saveScore();

	// Ȼ�����ñ��� ������������3�֡���4��
	this->initSpeech();
	this->createSpeaker();
	this->loadSpeaker();
}
void SpeechManager::showSpeaker()
{
	cout << "--------------------��" << this->m_Index << "�ֽ���ѡ����Ϣ����--------------------" << endl;
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
		cout << "ѡ�ֱ�ţ�" << (*it) << "  ������" << this->m_Speaker[*it]._name
			<< "  �÷֣�" << this->m_Speaker[*it]._score[this->m_Index - 1] << endl;
	}
	cout << endl;
	system("pause");//������ͣ�ۿ�����Ϣ
	system("cls"); // ��һ�ֻ��ߵڶ����Ѿ������� ������
	
	this->show_Menu(); // ������ʾ�˵�

}
void SpeechManager::loadSpeaker()
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fiileIsEmpty = true;
		cout << "�ļ������ڣ�" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		cout << "�ļ�Ϊ�գ�" << endl;
		this->fiileIsEmpty = true;
		ifs.close();
		return;
	}

	// �ļ���Ϊ��
	cout << "��ʷ��¼�ļ��򿪳ɹ���" << endl;
	this->fiileIsEmpty = false;
	ifs.putback(ch); // ��ȡ�ĵ����ַ��Ż�ȥ
	string data;
	int index = 0; // �ڼ���
	while (ifs >> data)
	{
		// cout << data << endl; //�����õ��������ʾ��ע�͵�
		vector<string> v;
		int pos = -1; // ��¼����","��λ��
		int start = 0; // ��ȡ��������ʼλ��
		
		// �ȸ��ݶ��ŵõ��ֿ�����Ϣ
		while (true)
		{
			pos = data.find(",", start);// ��0��ʼ���Ҷ���","
			if (pos == -1)
			{
				break; //û�ҵ��ָ���
			}
			string tmp = data.substr(start, pos - start); // �õ���ʼλ�õ���һ������֮�������
			v.push_back(tmp);  // v[0] = ��� v[1] =����
			start = pos + 1; // ��ʼλ�ø�Ϊ���ŵ���һ�� ׼����ȡ��һ����Ϣ
		}
		// ��һ�����־ͱ�����Ϊ�����֣�ÿ����=���+����
		this->m_Score.insert(make_pair(index, v));// map<int, vector<string>> m_Score; /
		index++;  // �ڼ���
	}
	ifs.close();
	// �鿴�������Ϣ
	for (map<int, vector<string>> ::iterator it = this->m_Score.begin(); it != this->m_Score.end(); it++)
	{
		cout << "��" << it->first + 1 << "��ѡ����Ϣ���£�" << endl;
		cout<< "\t�ھ�ѡ�ֵı��Ϊ��" << it->second[0] <<
			"  ����Ϊ��" << it->second[1] << endl;
		cout << "\t�Ǿ�ѡ�ֵı��Ϊ��" << it->second[2] <<
			"  ����Ϊ��" << it->second[3] << endl;
		cout  << "\t����ѡ�ֵı��Ϊ��" << it->second[4] <<
			"  ����Ϊ��" << it->second[5] << endl;
	}
	system("pause");
	system("cls");
}
void SpeechManager ::viewTop3Speaker()
{
	if (this->fiileIsEmpty)
	{
		cout << "�ļ������ڻ����ļ�Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��ʷ��¼�ļ��򿪳ɹ���" << endl;
		for (int i = 0; i < this->m_Score.size(); i++) // ��������index=1~3
		{
			cout << "��" << i + 1 << "��ѡ����Ϣ���£�" << endl;
			cout << "\t�ھ�ѡ�ֵı��Ϊ��" << this->m_Score[i][0] <<
				"  ����Ϊ��" << this->m_Score[i][1] << endl;
			cout << "\t�Ǿ�ѡ�ֵı��Ϊ��" << this->m_Score[i][2] <<
				"  ����Ϊ��" << this->m_Score[i][3] << endl;
			cout << "\t����ѡ�ֵı��Ϊ��" << this->m_Score[i][4] <<
				"  ����Ϊ��" << this->m_Score[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearSpeaker()
{
	cout << "ȷ����գ�" << endl;
	cout << "1. ȷ��" << endl;
	cout << "2. ����" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs("speech.csv", ios::trunc); //���������ɾ�����ڴ���
		ofs.close();
		this->initSpeech();
		this->createSpeaker();
		this->loadSpeaker();
		cout << "�ļ���ճɹ���" << endl;
	}
	system("pause");
	system("cls");
}

void SpeechManager::exitSystem()
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	//system("pause");
	exit(0);
}