#include "contanter.h"
/*
<1>string �ĸ���
     string ��һ���� char*��һ��ָ��
     string�ڲ���װ��char* ��������ַ��� ��һ�� char*������
     string�ڲ���find��copy��delete��replace��insert�ȷ���
<2>string�Ĺ��캯��
     2.1 string(); ---->ʹ��һ���յ��ַ��� �� string str;
     2.2 string(const char* s) ;---->ʹ���ַ���s��ʼ��
     2.3 string(const string & str) ;---->ʹ��һ��string�����ʼ�� ��һ��string����
     2.4 string(int n ,char c) ;----> ʹ��n���ַ�c��ʼ��
<3>string�ĸ�ֵ����(���������)
    3.1 string& operator = (const char *s) ; // ָ��̶��ַ���ָ�� �����ַ���
    3.2 string& operator = (const string &s) ; // ָ��̶��ַ��������� �����ַ���
    3.3 string& operator = ( char c) ; // �ַ�ֵ����  �����ַ���
    3.4 string& assign = (const char *s) ; // ���ַ���s �����ַ���
    3.5 string& assign = (const char *s ,int n) ; // ָ��̶��ַ���ָ�� ǰn���ַ� �����ַ���
    3.6 string& assign = (const  string &s) ; // ָ��̶��ַ��������� �����ַ���
    3.7 string& assign= (int n , char s) ; // �ַ�ֵ����  �����ַ���
<4>string���ַ���ƴ��
    4.1 string& operator += (const char *str) ; // ֱ��ƴ�ӳ����ַ���
    4.2 string& operator += (const char s) ; // ƴ�ӳ����ַ�(ֵ����)
    4.3 string& operator += (const string& str) ; // ƴ�ӱ����ַ���(���ô���)
    4.4 string& append (const char *s) ; // ƴ�ӳ����ַ�(��ַ����)
    4.4 string& append (const char *s ,int n) ;// ƴ��ǰn�������ַ�(��ַ����)
    4.5 string& append (const string &s) ;// ƴ�ӱ����ַ���(���ô���)
    4.6 string& append (const string &s , int pos , int n) ;// ƴ�ӱ����ַ�����pos��ʼ��n���ַ�(���ô���)
<5>string�Ĳ��Һ��滻(����������߸���const��ʾ�ú��������޸����Ա���Ի���)
    5.1 int find(const string & str , int pos=0) const ;// ����str��һ�γ���λ�� ��pos����
    5.2 int find(const char * s , int pos=0) const ; // ͬ 5.1
    5.3 int find(const  char * s , int pos=0, int n) const ; ��posλ�ó��ֵ�ǰn���ַ���һ�γ���λ��
    5.4 int find(const  char c , int pos=0) const ; // �����ַ�
    5.5 int rfind(const string &str , int pos=npos ) const ; // ���ұ߿�ʼ����posλ�ò������һ��λ��
    5.6 int rfind(const char *s , int pos=npos ) const ;  //�����ַ���ָ��
    5.7 int rfind(const char c , int pos=npos ) const ; // �����ַ�
    5.8 string& replace(int pos, int n , const string& str) ; //  �滻Ϊ�����ַ���
    5.9 string& replace(int pos , int n , const char *s) ;  //  �滻Ϊ�����ַ���
<6>�ַ����Ƚ� �� ��ASCII������Ƚ�
    6.1 int compare(const string &s) const ; // ������ַ������бȽ�
    6.2 int compare(const  char *s) const ; // �볣���ַ������бȽ�
<7>�ַ���ȡ
    7.1 char & operator[] (int n) ; // ͨ��[]��ʽ��ȡ�ַ�
    7.2 char & at(int n) ; // ͨ��at ������ȡ
<8>�ַ��������ɾ��
    8.1 string & insert(int pos , const char *s) // ���볣���ַ���
    8.2 string & insert(int pos , const string & str) // ��������ַ���
    8.3 string & insert(int pos , int n ,char c ) // ָ��λ�ò���n���ַ�
    8.4 string & erase(int pos , int n = npos)  // ɾ����pos��ʼ��n���ַ�
<9>�ִ���ȡ
    9.1 string substr(int pos = 0 , int n = npos) // ��pos��ʼ��ȡn���ַ�
 */
void test_0025()
{
    // 6.1 int compare(const string & s) const; // ������ַ������бȽ�

    string str1 = "hello";
    string str2 = "hello";
    string str3 = "xello";
    cout << str2.compare(str1) << endl;
    cout << str2.compare(str3)<<endl;
    if (str1.compare(str2) == 0)
    {cout << "���" << endl;}else { cout << "�����" << endl; }
    //6.2 int compare(const  char* s) const; // �볣���ַ������бȽ�
    // 7.1 char& operator[] (int n); // ͨ��[]��ʽ��ȡ�ַ�
    cout <<str2[2]<< endl;
    // 7.2 char& at(int n); // ͨ��at ������ȡ
    cout << str3.at(2) << endl;
    // 8.1 string & insert(int pos , const char *s) // ���볣���ַ���
    str1.insert(3,"chenbei");
    cout << str1 << endl;
    // 8.4 string & erase(int pos , int n = npos)  // ɾ����pos��ʼ��n���ַ�
    str1.erase(3, 7);
    cout << str1 << endl;
    // 9.1 string substr(int pos = 0, int n = npos) // ��pos��ʼ��ȡn���ַ�
    cout << str1.substr(3, 2) << endl;
}
void test_0024()
{
    //5.1 int find(const string & str, int pos = 0) const;// ����str��һ�γ���λ�� ��pos����
    string str1 = "0123456789";
    int pos = str1.find("h", 0);// -1
    cout <<pos <<endl; //d��λ�ô�0��Ϊ3
    //5.5 int rfind(const string & str, int pos = npos) const; // ��posλ�ò������һ��λ��
    int pos1 = str1.rfind("8", 8);
    cout << pos1  << endl; // 8 ��Ȼ���������� ���Ƿ��ص�λ�û��Ǵ������ҵ�˳��
    //5.9 string & replace(int pos, int n, const char* s);  //  �滻Ϊ�����ַ���
    str1.replace(2, 4, "chen"); // 2345���滻chen ��01chen6789
    cout << str1 << endl;
    str1 = "0123456789"; // 234���滻Ϊchen �� 01chen56789
    str1.replace(2, 3, "chen");
    cout << str1 << endl;

}
void test_0023()
{
    //4.1 string & operator += (const char* str); 
    string str1 = "playing ";
    str1 += "game ";
    //4.2 string & operator += (const char s); 
    str1 += '!';
    //4.3 string & operator += (const string & str); 
    string str2 = "I am ";
    str2 += str1;
    //4.4 string & append(const char* s);
    string str3 = "I love ";
    str3.append("basketball");
    //4.4 string & append(const char* s, int n);
    string str4;
    str4.append("I love basketball" , 6);
    //4.5 string & append(const string & s);
    string str5;
    str5.append(str3, 6);
    //4.6 string & append(const string & s, int pos, int n);
    string str6;
    str6.append(str3, 6, 7);
    cout << str1 << endl;
    cout << str2 << endl;
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;
    cout << str6 << endl;

}
void test_0021()
{
    // 2.1 Ĭ�Ϲ���
    string s1;
    // 2.2 ʹ���ַ�������
    const char *  str = "chenbei"; // pointer to const char  һ��ָ�����ַ���ַstr��ָ��
    string s2(str);
    cout << s2 << endl;
    // 2.3 ʹ��һ���ַ�����������(�ַ����ĳ�������)
    string s3(s2);
    // 2.4 ��ʼ��n���ַ�
    string s4(10, 'a');
    cout << s4 << endl; 
}
void test_0022()
{
    //3.1 string & operator = (const char* s); 
    string str1;
    // �� "hello world"����char�ĳ�������,Ҳ������ָ��ָ��char�����ַ
    str1 = "hello world"; 
    //3.2 string & operator = (const string & s); 
    // ��str1����������ַ��� ���ô���
    string str2 = str1;
    //3.3 string & operator = (char c); 
    string str3 ; // ֱ�� string str3 = 'a' ;�ǲ��е� ���캯��û��char��string������ʽת��
    str3 = 'a';
    //3.4 string & assign = (const char* s); 
    string str4;
    str4.assign("hello c++"); // ��3.1��ûʲô����� ���Ǻ���ֱ�ӹ�����
    //3.5 string & assign = (const char* s, int n); 
    string str5;
    str5.assign("hello c++", 5);
    //3.6 string & assign = (const  string & s); 
    string str6;
    str6.assign(str4, 5); // ��3.5������ֻ���ڶ������ַ������ַ�������
    //3.7 string & assign = (int n, char s); 
    string str7;
    str7.assign(5, 'a'); 
    cout << str1<< endl;
    cout << str2 << endl;
    cout << str3 << endl;
    cout << str4 << endl;
    cout << str5 << endl;
    cout << str6 << endl;
    cout << str7 << endl;
}
int string_containter()
//int main()
{
    //vector_containter();
    test_0021();
    test_0022();
    test_0023();
    test_0024();
    test_0025();
    return 0;
}