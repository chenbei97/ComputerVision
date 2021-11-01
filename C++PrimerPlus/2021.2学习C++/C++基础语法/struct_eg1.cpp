#include <iostream>
#include <string> //2019���ᱨ�� c++20
#include <ctime> // ʱ��ͷ�ļ�
using namespace std;
/*
ÿ����ʦ��5��ѧ��,��8����ʦ,�����ʦ��ѧ���Ľṹ��
������ʦ�ṹ������ʦ�����ʹ��5��ѧ����������Ϊ��Ա
ѧ���ĳ�Ա�����������Է���
����������8����ʦ��ͨ��������ÿ����ʦ��������ѧ����ֵ
*/
struct student {
	string name;
	int score;
};
struct teacher {
	string name ;
	struct student arr_students[5]; // �ṹ��Ƕ�׽ṹ������
	//���ٵ��������ֵ
};
string * generate_teacher_student_name(string   teacher_student_name[5] ,int teacher_id) {
	//C���Է���ֵ��֧�ַ������飬��������ͨ������ָ������
	//���ܹ������ں���������ľֲ��������飬��Ϊһ�������˳����ֲ������ͻᱻ�ͷţ���������ָ����Ч
	// ��ֻ�ܶ���һ�������ַ���ָ�����͵ĺ��� string * ��ͬʱ��Ҫ�ⲿ�����ַ�������������ڲ�����
	// ���ص�Ҳ���ⲿ���ݵ��ַ������� �׵�ַ ,��Ҫʹ���ַ���ָ�����,ͨ��ƫ��ָ����Է��ʴ����õ�����
	// ͬʱ�ⲿ���龭���ú���Ҳ���ı���,���õ�Ϊ��ַ����
 // ���� :  ���е��ַ������� , ��ʦ�ı��id 1,2,3...,8  
	string tch_id = to_string(teacher_id); 
	string str1 = "teacher"; 
	string str2 = "student";
	
	//string teacher_student_name[5];
	for (int i = 0; i < 5; i++) {
		 teacher_student_name[i] = str1+tch_id +"_"+str2 +to_string(i+1);
	}
	
	return teacher_student_name ; //���ص��������ַ������� ���׵�ַ,���ڵ�ַ����
								  //�ı���������ַ���ֵ��Ҫ���ַ���ָ��string *���庯��
}

// ��Ƶ�ķ���
void allocateSpace(struct teacher tarray[], int len) {
	// �����ڴ�ռ�
	//������� : һ���������ȵĽṹ������ , len��ȷ������ṹ�����ݵĳ��� �����ڶ�̬�����ڴ�
	string nameseed = "ABCDE";
	for (int i = 0; i < len; i++) { //ÿ����ʦ���ѭ��
		tarray[i].name = "Teacher_";
		tarray[i].name += nameseed[i];

      //ÿ����ʦ��ѧ�� �ڲ�ѭ��
		for (int j = 0; j < 5; j++) {
			tarray[i].arr_students[j].name = "Student_";
			tarray[i].arr_students[j].name += nameseed[j]; // ��ʦA��ѧ��A

			int random = rand() %  61 + 40;//0~60�� + 40 
			tarray[i].arr_students[j].score = random;
		}
	}
}
void printInfo(struct teacher tarray[], int len)
{
	for (int i = 0; i < len; i++) {
		cout << "��ʦ���� : " << tarray[i].name << endl;
		for (int j = 0; j < 5; j++) {
			cout << "\tѧ������ : " << tarray[i].arr_students[j].name << endl;
			cout << "\tѧ������ : " << tarray[i].arr_students[j].score << endl;
		}
	}
}
int main(int argc , char ** argv)
 {
	//struct_func();
	string teacher_name[8] = {"teacher1","teacher2", "teacher3", "teacher4",
		"teacher5", "teacher6", "teacher7", "teacher8"}; // ������ʦ�����ַ�������

	 //�������� : ���Եõ�һ����ʦ��5��ѧ��
	string teacher1_student_name[5];
    string * s = generate_teacher_student_name(teacher1_student_name,1);
	//cout <<* (s+1) << endl; // sָ�����ַ������׵�ַ
	//cout << teacher1_student_name[4] << endl;//֤�����������ȷʵ�����˸ı�


	// ������ά����õ�������ʦ������ѧ��,���ڸ��ṹ�帳ֵ
	string teacher_student_name[8][5];  
	for (int i = 0; i < 8; i++) {
		string* tem = generate_teacher_student_name(teacher_student_name[i], i + 1); //��i+1����ʦ�õ���ѧ�� ���ַ���ָ������ַ�������
		for (int j = 0; j < 5; j++) {
			teacher_student_name[i][j] = * tem ; //tem��ĳ����ʦ��ѧ���׵�ַ,������
			tem++; //ƫ�Ƶ�����ʦ�Ĳ�ͬ��ѧ����ַ
			//cout << teacher_student_name[i][j] <<endl; //��������Ƿ񴴽��ɹ�
		}
	}
	//cout << typeid(teacher_student_name[0][0]).name() << endl; //�������Է��ر�������
	//string a = teacher_student_name[0][0]; //�������ַ������ͶԽ�
	//cout << a << endl;
	
	// �ṹ������
	teacher  tch[8];  // ѭ����ֵ
	teacher  stru0 = tch[0];  // �ýṹ�����
	tch[0].arr_students[0].name = "cb";  
	cout << "���Լ�д�ĳ������н��Ϊ : " << endl;
	for (int i = 0; i < 8; i++) {
		tch[i].name = "teacher" + to_string(i + 1); // teacher1
		for (int j = 0; j < 5; j++) {
			tch[i].arr_students[j].name = teacher_student_name[i][j];//�������ʾ���ܽ�string����char���͵�ʵ��
			tch[i].arr_students[j].score = rand() % 61 + 40;
			cout << " ѧ�����Ϊ : "<< tch[i].arr_students[j].name << endl;
			cout <<"\tѧ���ķ���Ϊ : " << tch[i].arr_students[j].score<< endl;
		}
	}


	// ��Ƶ�ķ���
	srand((unsigned int)time(NULL));
	struct teacher tArray[3]; // 3����ʦ
	int len = sizeof(tArray) / sizeof(tArray[0]);  // ��̬�����ڴ� len =5
	allocateSpace(tArray, len);
	cout << "��Ƶд�ĳ������н��Ϊ : " << endl;
	printInfo(tArray, len);
	system("pause");
	return 0;
}