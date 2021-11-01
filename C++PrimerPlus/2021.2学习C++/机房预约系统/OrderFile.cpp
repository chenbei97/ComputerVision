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
	this->OrderNum = 0; // 预约条数0
	while (ifs >> dateName && ifs >> intervalName && ifs >> studentIdName
		&& ifs >> studentName && ifs >> roomName
		&& ifs >> statusName)
	{
		// 测试代码
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
			key = dateName.substr(0, pos); // 冒号前边是key
			value = dateName.substr(pos + 1, dateName.size() - pos-1);// 整个键值对长度减去冒号前边的key是value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		pos = intervalName.find(":");
		if (pos != -1)
		{
			key = intervalName.substr(0, pos); // 冒号前边是key
			value = intervalName.substr(pos + 1, intervalName.size() - pos-1);// 整个键值对长度减去冒号前边的key是value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		pos = studentIdName.find(":");
		if (pos != -1)
		{
			key = studentIdName.substr(0, pos); // 冒号前边是key
			value = studentIdName.substr(pos + 1, studentIdName.size() - pos - 1);// 整个键值对长度减去冒号前边的key是value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		pos = studentName.find(":");
		if (pos != -1)
		{
			key = studentName.substr(0, pos); // 冒号前边是key
			value = studentName.substr(pos + 1, studentName.size() - pos-1);// 整个键值对长度减去冒号前边的key是value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		pos = roomName.find(":");
		if (pos != -1)
		{
			key = roomName.substr(0, pos); // 冒号前边是key
			value = roomName.substr(pos + 1, roomName.size() - pos-1);// 整个键值对长度减去冒号前边的key是value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		pos = statusName.find(":");
		if (pos != -1)
		{
			key = statusName.substr(0, pos); // 冒号前边是key
			value = statusName.substr(pos + 1, statusName.size() - pos-1);// 整个键值对长度减去冒号前边的key是value
			mp.insert(make_pair(key, value));
			//cout << "key=" << key << endl;
			//cout << "value=" << value << endl;
		}

		this->mapOrderFile.insert(make_pair(this->OrderNum, mp));
		this->OrderNum++; // 更新条数
	}
	// 测试最大的容器
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
	// 更新order.txt文件 以覆盖方式重写
	if (this->OrderNum == 0)
	{
		return;
	}
	ofstream ofs(Order_File, ios::out || ios::trunc);
	for (int i = 0; i < this->OrderNum; i++)
	{
		ofs << "预约日期:" << this->mapOrderFile[i]["预约日期"] << " ";
		ofs << "预约时段:" << this->mapOrderFile[i]["预约时段"] << " ";
		ofs << "学生学号:" << this->mapOrderFile[i]["学生学号"] << " ";
		ofs << "学生姓名:" << this->mapOrderFile[i]["学生姓名"] << " ";
		ofs << "预约房号:" << this->mapOrderFile[i]["预约房号"] << " ";
		ofs << "预约状态:" << this->mapOrderFile[i]["预约状态"] << endl;
	}
	ofs.close();
}