#include <iostream>
using namespace std;
/*
1.public ����Ȩ�� : ��Ա����Է��� , ����Ҳ���Է���
2.pretected ����Ȩ��  : ���ڿ��Է��� ���ⲻ�ܷ��� ������Է��ʸ���
3.private ˽��Ȩ�� : ���ڿ��Է��� ���ⲻ�ܷ��� ���಻�ܷ��ʸ���
����˵���׵��ֻ��������˿��Է��ʣ�����Ҳ���Է���
���׵ĳ� �����˲��ܷ��ʣ����ӿ��Է���
���׵����п��� ����Ҳ���ܷ���
*/
/* struct �� class ������
structĬ��Ȩ��Ϊ����  classĬ��Ȩ��Ϊ˽��
*/
class  Person
{
    string  _id = "cb"; // �ڲ�����ؼ���ʱ������Ĭ��˽�� person1_id���ܷ���
public: 
    //�ⲿ���Է��ʹ���Ȩ������
    string _PhoneNumer = "13651116327";  
protected :
    // �ⲿ���ܷ��ʱ���Ȩ������
    string  _Car = "benchi";  
private  :
    // �ⲿ���ܷ���˽��Ȩ������
    int _Password = 123;
/*<------------------------------------------------------------------------------------------->*/
public :
     // �ⲿ�ӿ�����
    // �����дȨ��
    void setAge(int  age) 
    {
        _age = age;  //�ṩ���ⲿ���������ڲ���˽������_age
    }
    // ����Ķ�Ȩ��
    int getAge()
    {
        return  _age;//�ṩ���ⲿ������ȡ�ڲ���˽������_age
    }
    // ���˵�ֻ��Ȩ��
    string getLover()
    {
        return _lover;
    }
    // Ʒ�Ƶ�ֻдȨ��
    void setBrand(string brand)
    {
        _brand = brand;
    }
private :
    // ����ⲿ��Ҫ����˽�����Կ����ⲿ�ṩ�ӿ��趨��ͬ��Ȩ��ȥ����
    // ��python��������Ĭ���ǿɶ���д��,����ͨ��_numer�����ò��ɶ����ɷ���,ֻ��ͨ���෽���ṩ�ӿ�
    // �ɶ���д
    int _age = 10;
    // ֻ��
    string _lover = "xishi";
    // ֻд
    string _brand = "huawei";
/*<------------------------------------------------------------------------------------------->*/
public :
    void  func1()
    {
        //�ڲ�Ҳ���Է��ʹ���Ȩ������
        _PhoneNumer = "19801279791"; 
        cout << "�ڲ����Է��ʹ���Ȩ������_PhoneNumer(�ֻ���) : " << _PhoneNumer <<endl;
        // �ڲ�Ҳ���Է��ʱ���Ȩ������
        _Car = "baoma"; 
        cout << "�ڲ����Է��ʱ���Ȩ������_Car(��) : " << _Car << endl;
        // �ڲ�Ҳ���Է���˽��Ȩ������
        _Password = 456;
        cout << "�ڲ����Է���˽��Ȩ������_Password(����) : " << _Password << endl;
    }
};
int Access_Right()
//int main() 
{
    Person  person1;
    cout << "�ⲿ���Է��ʹ���Ȩ������person1._PhoneNumer(�ֻ���) : " <<person1._PhoneNumer << endl;
    cout << "�ⲿ�����Է��ʱ���Ȩ������person1._Car(��)" << endl;
    cout << "�ⲿ�����Է���˽��Ȩ������person1._Password(����)" << endl;
    person1.func1();
    
    // ���Ի�ȡ����Ķ�дȨ��
    // ����Ķ�Ȩ��
    int age = person1.getAge();
    cout << "���Ի�ȡ����Ķ�Ȩ��, age = " << age <<endl;
    // �����дȨ��
    person1.setAge(20);
    cout << "���Ի�ȡ�����дȨ��, age = " << person1.getAge() << endl;
    // ���˵�ֻ��Ȩ��
    string lover = person1.getLover();
    cout << "���Ի�ȡ���˵�ֻ��Ȩ��, age = " << lover << endl;
    // Ʒ�Ƶ�ֻдȨ��
    person1.setBrand("oppo");
    system("pause");
    return 0;
}