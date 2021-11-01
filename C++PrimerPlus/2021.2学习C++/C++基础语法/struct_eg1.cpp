#include <iostream>
#include <string> //2019不会报错 c++20
#include <ctime> // 时间头文件
using namespace std;
/*
每名老师带5个学生,共8名老师,设计老师和学生的结构体
其中老师结构体有老师姓名和存放5名学生的数组作为成员
学生的成员有姓名、考试分数
创建数组存放8名老师，通过函数给每个老师和所带的学生赋值
*/
struct student {
	string name;
	int score;
};
struct teacher {
	string name ;
	struct student arr_students[5]; // 结构体嵌套结构体数组
	//不再单独赋予初值
};
string * generate_teacher_student_name(string   teacher_student_name[5] ,int teacher_id) {
	//C语言返回值不支持返回数组，不过可以通过返回指针类型
	//不能够返回在函数部定义的局部变量数组，因为一旦函数退出，局部变量就会被释放，导致数组指针无效
	// 故只能定义一个返回字符串指针类型的函数 string * ，同时需要外部传递字符串数组而不能内部定义
	// 返回的也是外部传递的字符串数组 首地址 ,需要使用字符串指针接收,通过偏移指针可以访问创建好的数组
	// 同时外部数组经过该函数也被改变了,采用的为地址传递
 // 参数 :  单行的字符串数组 , 老师的编号id 1,2,3...,8  
	string tch_id = to_string(teacher_id); 
	string str1 = "teacher"; 
	string str2 = "student";
	
	//string teacher_student_name[5];
	for (int i = 0; i < 5; i++) {
		 teacher_student_name[i] = str1+tch_id +"_"+str2 +to_string(i+1);
	}
	
	return teacher_student_name ; //返回的是输入字符串数组 的首地址,属于地址传递
								  //改变了输入的字符串值需要用字符串指针string *定义函数
}

// 视频的方案
void allocateSpace(struct teacher tarray[], int len) {
	// 开辟内存空间
	//输入参数 : 一个不定长度的结构体数组 , len是确定这个结构体数据的长度 ，用于动态分配内存
	string nameseed = "ABCDE";
	for (int i = 0; i < len; i++) { //每个老师外层循环
		tarray[i].name = "Teacher_";
		tarray[i].name += nameseed[i];

      //每个老师的学生 内层循环
		for (int j = 0; j < 5; j++) {
			tarray[i].arr_students[j].name = "Student_";
			tarray[i].arr_students[j].name += nameseed[j]; // 老师A的学生A

			int random = rand() %  61 + 40;//0~60分 + 40 
			tarray[i].arr_students[j].score = random;
		}
	}
}
void printInfo(struct teacher tarray[], int len)
{
	for (int i = 0; i < len; i++) {
		cout << "老师姓名 : " << tarray[i].name << endl;
		for (int j = 0; j < 5; j++) {
			cout << "\t学生姓名 : " << tarray[i].arr_students[j].name << endl;
			cout << "\t学生分数 : " << tarray[i].arr_students[j].score << endl;
		}
	}
}
int main(int argc , char ** argv)
 {
	//struct_func();
	string teacher_name[8] = {"teacher1","teacher2", "teacher3", "teacher4",
		"teacher5", "teacher6", "teacher7", "teacher8"}; // 定义老师姓名字符串数组

	 //函数调试 : 可以得到一个老师的5个学生
	string teacher1_student_name[5];
    string * s = generate_teacher_student_name(teacher1_student_name,1);
	//cout <<* (s+1) << endl; // s指向了字符串的首地址
	//cout << teacher1_student_name[4] << endl;//证明定义的数组确实发生了改变


	// 创建二维数组得到所有老师的所有学生,用于给结构体赋值
	string teacher_student_name[8][5];  
	for (int i = 0; i < 8; i++) {
		string* tem = generate_teacher_student_name(teacher_student_name[i], i + 1); //第i+1个老师得到的学生 用字符串指针接收字符串数组
		for (int j = 0; j < 5; j++) {
			teacher_student_name[i][j] = * tem ; //tem是某个老师的学生首地址,解引用
			tem++; //偏移到该老师的不同个学生地址
			//cout << teacher_student_name[i][j] <<endl; //输出检验是否创建成功
		}
	}
	//cout << typeid(teacher_student_name[0][0]).name() << endl; //此语句可以返回变量类型
	//string a = teacher_student_name[0][0]; //可以用字符串类型对接
	//cout << a << endl;
	
	// 结构体数组
	teacher  tch[8];  // 循环赋值
	teacher  stru0 = tch[0];  // 用结构体接收
	tch[0].arr_students[0].name = "cb";  
	cout << "我自己写的程序运行结果为 : " << endl;
	for (int i = 0; i < 8; i++) {
		tch[i].name = "teacher" + to_string(i + 1); // teacher1
		for (int j = 0; j < 5; j++) {
			tch[i].arr_students[j].name = teacher_student_name[i][j];//这里会提示不能将string赋给char类型的实体
			tch[i].arr_students[j].score = rand() % 61 + 40;
			cout << " 学生编号为 : "<< tch[i].arr_students[j].name << endl;
			cout <<"\t学生的分数为 : " << tch[i].arr_students[j].score<< endl;
		}
	}


	// 视频的方案
	srand((unsigned int)time(NULL));
	struct teacher tArray[3]; // 3个老师
	int len = sizeof(tArray) / sizeof(tArray[0]);  // 动态分配内存 len =5
	allocateSpace(tArray, len);
	cout << "视频写的程序运行结果为 : " << endl;
	printInfo(tArray, len);
	system("pause");
	return 0;
}