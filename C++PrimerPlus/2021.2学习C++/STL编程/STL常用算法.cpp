#include "contanter.h"
/*
<1>STL常用头文件
		<algorithm> 涉及比较、交换、查找、遍历、复制和修改等
		<numeric>主要是简单数学运算的模板函数
		<functional> 内建函数
<2>STL常用算法
		2.1 遍历算法(可以自己写即printvector()也可以使用内置的算法)
				2.1.1 for_each(iterator beg , iterator end , func) ; // 遍历容器
				2.1.2 transform(iterator beg1 , iterator end1 , iterator beg2, func) ; // 搬运容器到另一个容器
				2.1.4 func可以是普通函数也可以是仿函数实现
		2.2 查找算法
				2.2.1 find(beg,end,elem) // 查找 返回指定元素迭代器或者结束迭代器
				2.2.2 findif(beg,end,func) // 按条件查找 func为bool类型的仿函数或者谓词
				2.2.3 adjacent_find(beg,end) // 查找相邻重复元素
				2.2.4 binary_search(beg, end,value) // 二分查找法 查到返回true 不可以用于无序序列
				2.2.5 count(beg,end,value)  // 统计个数
				2,2,6 count_if(beg,end,func) // 按条件统计个数
		2.3 排序算法
				2.3.1 sort(beg,end,func)  // 排序
				2.3.2 random_shuffe(beg,end) // 随即洗牌
				2.3.3 merge(beg1,end1,beg2,end2,target.begin()) // 两个必须有序的容器1、2元素合并 存储到另一个容器target
				2.3.4 reverse(beg,end,func) // 反转元素 func可以是类构造仿函数也可以是普通函数
		2.4 拷贝和替换算法
				2.4.1 copy(beg,end, target.begin()) // 拷贝
				2.4.2 replace(beg,end,oldvalue,newvalue) // 替换
				2.4.3 replace_if(beg,end,func,newvalue) //指定范围内满足条件的元素替换为新元素
				2.4.4 swap(containter1 containter2) // 互换2个同类型容器元素
		2.5 算术生成算法
				2.5.1 accumulate(beg,end,起始累加值) // 计算容器内元素累加和
				2.5.2 fill(beg,end,value)  // 容器添加元素
		2.6 集合算法
				2.6.1 set_intersection(beg1,end1,beg2,end2,target,begin()) // 交集
				2.6.2 set_union(beg1,end1,beg2,end2,target,begin()) // 并集
				2.6.3 set_difference(beg1,end1,beg2,end2,target,begin()) // 差集
				*/
// 普通函数实现
void print01(int val)
{
	cout << val <<" ";
}
// 类构造函数作为仿函数实现
class print02
{
public :
	void operator()(int val)
	{
		cout << val << " ";
	}
};
class Transformfunc // 重载()
{
public:
	int operator ()(int v)
	{
		return v;
	}

};
void test_0039()
{
	//2.1.1 for_each(iterator beg, iterator end, func); // 遍历容器
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	//直接函数输出实现
	cout <<"直接函数输出实现："<< endl;
	printvector(v);
	//spilit_line();
	// 普通函数作为迭代方法
	cout << "普通函数作为迭代方法实现：" << endl;
	for_each(v.begin(),v.end(),print01);
	// 类构造函数作为仿函数
	cout << "\n类构造函数作为迭代方法实现：" << endl;
	for_each(v.begin(), v.end(), print02());

	//2.1.2 transform(iterator beg1, iterator end1, iterator beg2, func); // 搬运容器到另一个容器
	vector<int> v1;
	v1.resize(v.size());
	// 仿函数
	transform(v.begin(), v.end(), v1.begin(), Transformfunc());
	cout << "\ntransform的类构造函数作为迭代方法实现：" << endl;
	for_each(v1.begin(), v1.end(), print02());
}
class Car
{
public:
	string _name;
	int _age;
	Car(int age, string name)
	{
		this->_age = age;
		this->_name = name;
	}
	bool operator == (const Car& p)
	{
		if (this->_age == p._age  && this->_name == p._name)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};
// count _if的重载
class greater2
{
public:
	bool operator ()(int val)
	{
		return val > 2;
	}
};
class agegreater18
{
public:
	bool operator()(const Car& p)
	{
		return p._age > 18;
	}

};
void test_0040()
{
	//2.2.1 find() // 查找 返回指定元素迭代器或者结束迭代器
	// 查找内置数据类型
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(i);
	}
	vector<int> :: iterator pos =find(v.begin(), v.end(), 5);
	// 查找自定义数据类型
	vector<Car> v1;
	Car p1(18, "a");
	Car p2(20, "b");
	v1.push_back(p1);
	v1.push_back(p2);
	vector<Car> ::iterator  it = find(v1.begin(), v1.end(), p2);
	if (it == v1.end()) // 这里比较时必须重载比较运算符
	{
		cout << "没找到" << endl;
	}
	else
	{
		cout << "姓名为：" << (*it)._name << endl;
	}
	//	2.2.3 adjacent_find // 查找相邻重复元素
	vector<int> v3;
	v3.push_back(0);
	v3.push_back(1);
	v3.push_back(1);
	v3.push_back(2);
	vector<int> ::iterator PP = adjacent_find(v3.begin(), v3.end());
	if (PP == v3.end())
	{
		cout << "未找到" << endl;
	}
	else
	{
		cout << "找到相邻重复元素：" <<*PP<< endl;
	}
	//	2.2.4 binary_search // 二分查找法 查到返回true 不可以用于无序序列
	if (binary_search(v.begin(), v.end(), 4))
	{
		cout << "找到元素" << endl;
	}
	else
	{
		cout << "没找到元素" << endl;
	}
	//	2.2.5 count  // 统计个数
	cout <<"v3元素1的个数为"<< count(v3.begin(),v3.end(),1) << endl;
	Car c1(18, "chen");
	Car c2(20, "ccc");
	Car c3(20, "ccc");
	Car cc(20, "ccc");
	vector<Car> CV;
	CV.push_back(c1);
	CV.push_back(c2);
	CV.push_back(c3);
	// 比较之前必须重载==
	cout << "和cc相同年龄的有多少人：" << count(CV.begin(), CV.end(), cc);
	//	2, 2, 6 count_if // 按条件统计个数
	cout << endl;
	cout<<"v中元素大于2的个数为："<<count_if(v.begin(),v.end(),greater2())<<endl;
	cout << "CV中年龄大于18的个数为：" << count_if(CV.begin(), CV.end(), agegreater18()) << endl;

}
// 排序算法

void test_0041()
{
	//2.3.1 sort  // 排序
	vector<int> v;
	for (int i = 0; i < 10; i++)
	{
		v.push_back(-i);
	}
	sort(v.begin(), v.end(), greater<int>());//内建函数升序
	//printvector(v);

	//	2.3.2 random_shuffe // 随即洗牌
	random_shuffle(v.begin(), v.end());
	//printvector(v);

	//	2.3.3 merge // 容器元素合并 存储到另一个容器
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i*i);
	}
	vector<int> v2;
	for (int i = 0; i < 10; i++)
	{
		v2.push_back(i );
	}
	vector<int> VV;
	printvector(v1);
	printvector(v2);
	// 开辟内存
	VV.resize(v2.size() + v1.size());
	merge(v1.begin(), v1.end(), v2.begin(), v2.end(), VV.begin());
	printvector(VV);

	//	2.3.4 reverse // 反转元素
	reverse(v.begin(), v.end());
	//printvector(v);
}
// 拷贝和替换算法
void copy_func(int v1)
{
	cout << v1 << " ";
}
class greater45
{
public:
	bool operator() (int v1)
	{
		return v1 > 40;
	}

};
void test_0042()
{
	//2.4.1 copy // 拷贝
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i * i);
	}
	vector<int> v2;
	v2.resize(v1.size());
	copy(v1.begin(),v1.end(),v2.begin());
	for_each(v2.begin(), v2.end(), copy_func);
	cout << endl;
	printvector(v2);
	//2.4.2 replace // 替换
	spilit_line();
	replace(v2.begin(),v2.end(),49,50);
	printvector(v2);
	//2.4.3 replace_if //指定范围内满足条件的元素替换为新元素
	spilit_line();
	// 使用仿函数指定func条件
	replace_if(v2.begin(),v2.end(), greater45(),100);
	printvector(v2);
	//2.4.4 swap // 互换2个容器元素
	spilit_line();
	swap(v1, v2);
	printvector(v2);
	printvector(v1);
}
// 算术生成算法
void test_0043()
{
	//2.5.1 accumulate // 计算容器内元素累加和
	vector<int> v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back(i * i);
	}
	cout<<"累加和为："<<accumulate(v1.begin(), v1.end(),0);
	//	2.5.2 fill  // 容器添加元素
	cout << endl;
	spilit_line();
	fill(v1.begin(), v1.end(),100);
	printvector(v1);
}
// 集合算法
void myprint(int va)
{
	cout << va << " ";
}
void test_0044()
{
	// 2.6.1 set_intersection // 交集
	//	2.6.2 set_union // 并集
	//	2.6.3 set_difference // 差集
	vector<int>v1;
	for (int i = 0; i < 10; i++)
	{
		v1.push_back( i);
	}
	vector<int>v2;
	for (int i = 0; i < 10; i++)
	{
		v2.push_back(i * i);
	}
	vector<int> v; // 目标容器
	v.resize(min(v1.size() , v2.size())); // 交集最大也就其中一个较小容器的大小
	vector<int> :: iterator  itEnd = set_intersection(v1.begin(),v1.end(),v2.begin(),v2.end(),v.begin());
	cout << "容器的交集为" << endl;
	//使用普通函数指定输出规则
	for_each(v.begin(), itEnd, myprint);
	cout << endl;
	// 直接输出
	printvector(v);
	cout << "交集大小为：" << v.size() << endl;


	spilit_line();
	v.resize(v1.size() + v2.size());
	vector<int> ::iterator it1end = set_union(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
	cout << "容器的并集为" << endl;
	for_each(v.begin(), it1end, myprint);
	cout << endl;
	cout << "并集大小为：" << v.size() << endl;

	// 差集 分为谁与谁的差集
	spilit_line();
	v.resize(max(v1.size() , v2.size())); // 取最大的
	vector<int> ::iterator it2end = set_difference(v1.begin(), v1.end(), v2.begin(), v2.end(), v.begin());
	cout << "v1和v2的容器的差集为" << endl;
	for_each(v.begin(), it2end, myprint);
	cout << endl;
	cout << "差集大小为：" << v.size() << endl;
	vector<int> ::iterator it3end = set_difference(v2.begin(), v2.end(), v1.begin(), v1.end(), v.begin());
	cout << "v2和v1的容器的差集为" << endl;
	for_each(v.begin(), it3end, myprint);
	cout << endl;
	cout << "差集大小为：" << v.size() << endl;
}
int common_algorithms()
//int main()
{
	//incline_function();
	// test_0039();
	//test_0040();
	//test_0041();
	//test_0042();
	//test_0043();
	test_0044();
	return 0;
}