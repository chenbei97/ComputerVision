#include <iostream>
#include <string>
#include "all.h"
using namespace std;
//int knm = -1;
void print_message(const string&, void (*getPrintMessageMethod) (const string&));
void display_with_hello(const string&);
void display_with_world(const string&);
//void display_with_hello_world(const string&);
void function_pointer_use() {
	extern void display_with_hello_world(const string&);
	void (*funcs[]) (const string&) = { display_with_hello,
	display_with_world,display_with_hello_world };

	for (int i = 0; i < 3; ++i) {
		print_message("chenbei", funcs[i]);
	}

	enum PrintMessageMethod{hello,world,hello_world};
	print_message("chenbei", funcs[hello_world]);

	cout << vec[1] << endl; // 常量数组/值可以用
	extern int knm; // 另1个文件已经定义为4
	cout << knm << endl;
	extern int abc;
	cout << abc << endl;

	extern int def; // 本文件定义了,优先本文件寻找
	cout << def << endl; 
}
int def = 20; // 作用域从定义开始到文件末尾
//int knm = 3; // 先从本文件找如果有的话,没有找其它1个文件,本文件不能再次定义
void print_message(const string& msg, void (*getPrintMessageMethod) (const string&)) {
	getPrintMessageMethod(msg);
}
void display_with_hello(const string& msg) {
	cout << "hello :  msg => " << msg << endl;
}
void display_with_world(const string& msg) {
	cout << "world :  msg => " << msg << endl;
}
void display_with_hello_world(const string& msg) {
	cout << "hello world :  msg => " << msg << endl;
}