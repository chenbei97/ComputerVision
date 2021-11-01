#pragma once
#include"GlobalFile.h"
#include <map>
// 在student的showMyOrder()去调用
class OrderFile
{
public:
	// 构造函数
	OrderFile();

	// 更新预约记录
	void updateOrder();

	// 记录的容器 key --- 记录的条数  value --- 具体记录的键值对信息
	map<int, map<string, string>> mapOrderFile;
	// key 预约日期 value 周一 map<string ,string>
	// 然后嵌套  不同条数的预约信息
	// 预约记录条数
	int OrderNum;
};