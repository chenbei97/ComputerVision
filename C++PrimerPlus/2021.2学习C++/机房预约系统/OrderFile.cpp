#include "OrderFile.h"
#include "GlobalFile.h"
OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(Order_File, ios::in);
	string dateName;
	string intervalName;
	string studentIdName;
	string studentName;
	string roomName;
	string statusName;
	this->OrderNum = 0; // ԤԼ����0
	while (ifs >> dateName && ifs >> intervalName && ifs >> studentIdName
		&& ifs >> studentName && ifs >> roomName
		&& ifs >> statusName)
	{
		// ���Դ���
		//cout << dateName<< endl;
		//cout << intervalName << endl;
		//cout << studentIdName << endl;
		//cout << studentName << endl;
		//cout << roomName << endl;
		//cout << statusName << endl;
		//cout << endl;
		string key;
		string value;
		map<string, string>  mp;
		
		int pos = dateName.find(":"); //4
		if (pos != -1)
		{
			key = dateName.substr(0, pos); // ð��ǰ����key
			value = dateName.substr(pos + 1, dateName.size() - pos-1);// ������ֵ�Գ��ȼ�ȥð��ǰ�ߵ�key��value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		pos = intervalName.find(":");
		if (pos != -1)
		{
			key = intervalName.substr(0, pos); // ð��ǰ����key
			value = intervalName.substr(pos + 1, intervalName.size() - pos-1);// ������ֵ�Գ��ȼ�ȥð��ǰ�ߵ�key��value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		pos = studentIdName.find(":");
		if (pos != -1)
		{
			key = studentIdName.substr(0, pos); // ð��ǰ����key
			value = studentIdName.substr(pos + 1, studentIdName.size() - pos - 1);// ������ֵ�Գ��ȼ�ȥð��ǰ�ߵ�key��value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		pos = studentName.find(":");
		if (pos != -1)
		{
			key = studentName.substr(0, pos); // ð��ǰ����key
			value = studentName.substr(pos + 1, studentName.size() - pos-1);// ������ֵ�Գ��ȼ�ȥð��ǰ�ߵ�key��value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		pos = roomName.find(":");
		if (pos != -1)
		{
			key = roomName.substr(0, pos); // ð��ǰ����key
			value = roomName.substr(pos + 1, roomName.size() - pos-1);// ������ֵ�Գ��ȼ�ȥð��ǰ�ߵ�key��value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		pos = statusName.find(":");
		if (pos != -1)
		{
			key = statusName.substr(0, pos); // ð��ǰ����key
			value = statusName.substr(pos + 1, statusName.size() - pos-1);// ������ֵ�Գ��ȼ�ȥð��ǰ�ߵ�key��value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		this->mapOrderFile.insert(make_pair(this->OrderNum, mp));
		this->OrderNum++; // ��������
	}
	// ������������
	//for (map<int, map<string, string>> ::iterator it = mapOrderFile.begin(); it != mapOrderFile.end(); it++)
	//{
	//	cout << "key = " << it->first << "  value = " << endl;
	//	for (map<string, string> ::iterator it1 = (*it).second.begin(); it1 != (*it).second.end(); it1++)
	//	{
	//		cout << "key = " << it1->first << "  value = " << it1->second << endl;
	//	}
	//}

}
void OrderFile::updateOrder()
{
	// ����order.txt�ļ� �Ը��Ƿ�ʽ��д
	if (this->OrderNum == 0)
	{
		return;
	}
	ofstream ofs(Order_File, ios::out || ios::trunc);
	for (int i = 0; i < this->OrderNum; i++)
	{
		ofs << "ԤԼ����:" << this->mapOrderFile[i]["ԤԼ����"] << " ";
		ofs << "ԤԼʱ��:" << this->mapOrderFile[i]["ԤԼʱ��"] << " ";
		ofs << "ѧ��ѧ��:" << this->mapOrderFile[i]["ѧ��ѧ��"] << " ";
		ofs << "ѧ������:" << this->mapOrderFile[i]["ѧ������"] << " ";
		ofs << "ԤԼ����:" << this->mapOrderFile[i]["ԤԼ����"] << " ";
		ofs << "ԤԼ״̬:" << this->mapOrderFile[i]["ԤԼ״̬"] << endl;
	}
	ofs.close();
}