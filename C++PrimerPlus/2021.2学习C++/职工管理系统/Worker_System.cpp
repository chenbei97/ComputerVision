#include "Worker_System.h"
#include "Worker_Individual.h"
#include <string>
#include <stdlib.h>
// �������ʵ��
// ͷ�ļ�д�������� ���������͹��캯�� �������򼴿�
// �Ժ������Ի���Ҫ��������д��ǰͷ
workerSystem::workerSystem()
{
	// �޸Ĺ��캯�� ���Ǽ򵥵ĳ�ʼ������ �ض��Ǹ����ļ������¹���
	//// ��ʼ������
	//this->_employeeNum = 0;
	//this->_employeeArray = { 0 };

	// �ļ������ڵ���������·�������
	ifstream ifs;
	ifs.open(FileName, ios::in);
	if ( ! ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		this->_employeeNum = 0;
		this->_employeeArray = NULL;
		this->_fileisEmpty = true; // �ļ�Ϊ��
		ifs.close();
		return ;
	}
	
	//�ļ����ڵ�������Ϊ��
	char ch;
	ifs >> ch; // ��һ���ַ�
	if (ifs.eof()) // �������ļ���β��λ��
	{
		cout << "�ļ�Ϊ�գ�"<<endl;
		this->_employeeArray = NULL;
		this->_employeeNum = 0;
		this->_fileisEmpty = true;
		ifs.close();
		return ;
	}
	ifs.close();
	//�ļ�����������ʷ���� ֮ǰ�����ݶ���_employeeArray = NULL;������Ҫ�������ڴ�
	 //ͳ����ʷԱ������ 
	int historynum = this->getHistoryWorkerNum(); // ͬʱ�����ڴ������С
	this->_employeeNum = historynum; 
	cout << "��ʷְ������Ϊ" << historynum << "��" << endl;
	this->_employeeArray = new workerIndividual *[ this->_employeeNum];//�����ڴ��С
	// //�����ʼ������ void initemployeeArray();������ʷְ����Ϣ����_employeeArray;
	this->initemployeeArray(); //_employeeArray�洢�����ʷ��Ϣ
}
workerSystem :: ~workerSystem()
{
		if (this->_employeeArray != NULL)
		{
			delete[]  this->_employeeArray;
			this->_employeeArray = NULL;
		}
}
void workerSystem::Show_Menu() // ��������
{
	cout << "*************************************************" << endl;
	cout << "***********   ��ӭʹ��ְ������ϵͳ!    **********" << endl;
	cout << "***********      0. �˳��������       **********" << endl;
	cout << "***********      1. ����ְ����Ϣ       **********" << endl;
	cout << "***********      2. ��ʾְ����Ϣ       **********" << endl;
	cout << "***********      3. ɾ����ְְ��       **********" << endl;
	cout << "***********      4. �޸�ְ����Ϣ       **********" << endl;
	cout << "***********      5. ����ְ����Ϣ       **********" << endl;
	cout << "***********      6. ���ձ������       **********" << endl;
	cout << "***********      7. ���������Ϣ       **********" << endl;
	cout << endl;
}
void workerSystem::Add_Emp()
/*
��Ҫ��������:
1.ԭ����ϵͳ����һ��Ա��������һ����Ų�ͬԱ��ָ���ָ�� workerIndividual ** _employeeArray
2.�˺����п�����һ���µ�ָ��ϵͳ��Ĵ��Ա��ָ���ָ��  workerIndividual** newspace ���С��ԭ����Ŀ����Ҫ�����Ա������Ŀ
3.�¿ռ�newspace�Ȱ���Ա������(_employeeNum��) �������Ա��(addNum��)
4. �����Ա����ҪһЩ��Ϣ ��  Ա����(��dSelect=1,2,3��ָ)�����������
5. �ر�Ķ���Ա�����ѡ�� ��Ҫһ����ʱ��Ա��������ָ�� workerIndividual* worker = NULL;
	֮���Դ���������û��ʵ������Ȼ�����dSelect��ѡ��Ϳ���ȷ������Ա����������ϰ�(��̬����)
5. ������Щ��Ϣ�����û�����ģ�������Ϻ���Ҫ��ŵ�newspace ��Ա����λ����
6. �������е������ݶ���newspace�����Կ����ͷŵ�������ԭ�е�_employeeArray
	��   delete[] this->_employeeArray;  ɾ����������ָ�� ������delete[]
7. ����newspace��ָ�� , ������������ָ���_employeeArray
	this->_employeeArray = newspace;
*/
{
	cout << "����������ְ�������� : " << endl;
	int addNum = 0;
	cin >> addNum;
	//if   (! isdigit( addNum) )
	//{    //�������ַ���0  ��ô�ж�Ϊ1
	//	cout << "����Ĳ����������֣����������룡" << endl;
	//	cin >> addNum;
	//}
	if (addNum > 0)
	{
		// ������Ӻ��ְ������
		int newsize = this->_employeeNum + addNum;
		// ���ٿռ�
		workerIndividual** newspace = new workerIndividual * [newsize];
		// ��ԭ�ռ�����ݷŵ��¿ռ�
		// ��ԭ������Ա�����ó������¿ռ�
		if (this->_employeeArray != NULL)
		{
			for (int i = 0; i < this->_employeeNum; i++)
			{
				newspace[i] = this->_employeeArray[i];
			}
		}
		// �ͷ�ԭ�б����ռ�
		delete[] this->_employeeArray; 
		// ���������ݷŵ���i+1�Ժ�
		for (int i = 0; i < addNum; i++)
		{
			int id;
			string name;
			int dSelect;
			cout << "�������" << i + 1 << "����Ա�����" << endl;
			cin >> id;
			cout << "�������" << i + 1 << "����Ա������" << endl;
			cin >> name;
			cout << "��ѡ���ְ���ĸ�λ��" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;
			workerIndividual* worker = NULL; // ������������ϣ������dSelect��ѡ��ȥʵ���������Ա����
			switch (dSelect)
			{
			case 1:
				worker = new  worker_Employee(id, name, dSelect);//ʹ��worker�������ȥ��̬���ֳ�����
				//cout << "worker��" << sizeof(worker) << "���ӽ�" << endl;
				break;
			case 2:
				worker = new worker_Manager(id, name, dSelect);
				//cout << "worker��" << sizeof(worker) << "���ӽ�" << endl;
				break;
			case 3:
				worker = new boss(id, name, dSelect);
				//cout << "worker��" << sizeof(worker) << "���ӽ�" << endl;
				break;
			default:
				break;
			}
			newspace[this->_employeeNum + i] = worker; //�����������ݴ�ŵĵط� ��ŵ���Ա�����ָ��(��ַ)
		}

		// ����newspace��ָ�� , ������������ָ���_employeeArray
		this->_employeeArray = newspace;
		//�����µ�ְ������
		this->_employeeNum = newsize;
		// �����ļ�״̬
		this->_fileisEmpty = false; //�ļ���Ϊ��
		// �����ļ� ����������ڵ�������ֻ��������ʱ��ʾһ������Ա��
		// ���ܶ�ȡ��ʷ���ݸ���������ְ������
		// �����Ҫ������ȡ�ļ����йغ������д��� ��ͳ����ʷ��Ա����int getHistoryWorkerNum();
		this->Save();
	}
	else
		{
			cout << "�������Ա����Ŀ�������������룡" << endl;
		}
     	system("cls");
		// ��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����Ա����Ϣ��" << endl;
		cout << "��ǰ��˾һ����" << this->_employeeNum << "����Ա��" << endl;
}
int workerSystem::getHistoryWorkerNum() // ͳ����ʷְ������
{
	ifstream ifs;
	ifs.open(FileName,ios::in);
	string ch;
	int num = 0; // ͳ���ļ�����
	while (getline(ifs,ch,'\n')) //����ȡ���ַ�Ϊ����ʱ
	{
		// �����ո������
		num++;
		//cout << ch << endl; // ����ӡÿ������
	}
	ifs.close();
	return num;
}
void workerSystem::initemployeeArray() //��ʼ����ʷְ����Ϣ
{
	ifstream  ifs;
	ifs.open(FileName, ios::in);
	string str;
	int index = 0; //��¼������ʷ���ݵ�ÿһ�� ���ڿ��ƴ�������λ��
	while (getline(ifs, str, '\n'))
	{
			// str= "ְ�����(�ո�)(��)(4)(tab)ְ���Ը�(�ո�)(��)(ccc)(tab)ְ�����(�ո�)(��)(3)(tab)"" ����2�ӽ�
			int arr1[3];
			int* p1 = arr1;
			int arr2[3];
			int* p2 = arr2;
			for (unsigned int j = 0; j < str.length();j++)
			{
				if (str[j] == ':')
				{
					*p1 = j + 1; //��¼��Ҫ���ַ�����ʼλ��
					//continue; // ������i��ѭ�� ִ�е�i+1��ѭ�� ����ð�žͼ�¼����ѭ��
					p1++; // p��¼��ÿ��λ��
					//cout << j + 1 << endl;//4 ��c��3---->10��22��40   41�ǻ��з�
				}
				if (str[j] == '	')
				{
					*p2 = j;
					p2++; // ��¼��tab��λ�� 11��25��()������û��
					//cout << j << endl;
				}
			}
			string id = str.substr(arr1[0], arr2[0] - arr1[0]); // id���ַ���   substr(��ʼλ�ã���ȡ���ַ�����) =(10,11-10)
			string name = str.substr(arr1[1], arr2[1] - arr1[1]); // (22,25-22)
			string did = str.substr(arr1[2], str.length() - arr1[2]); //(40,41-40)
			int _id = stoi(id);  //�ַ���ת����
			int _did = stoi(did);
			 //�������Ѿ��õ���ĳ��ְ���ı�š����֡����ű��
			workerIndividual* worker = NULL; // ����Ա��������
			if (_did == 1)
			{
			   worker = new worker_Employee(_id, name, _did);
			}
			else if (_did == 2)
			{
				worker = new worker_Manager(_id,name,_did);
			}
			else 
			{
				worker = new boss(_id, name, _did); 
			}
		   // ���ѭ��������������Ϣ������ö�Ӧ��worker
		   this->_employeeArray[index] = worker; // ���ݵ�ǰ�е�λ��
		   //cout << index << endl; // 0~41
		   index++; // ����ÿ��ȡһ�ε���
	}
	ifs.close();
}
void workerSystem :: Save()
{
	// ����д��ÿ��Ա���ı�š������Ͳ��Ŵ���
	ofstream ofs;
	ofs.open(FileName, ios::out); // ����д��  
	// ׷��д���������� �� ������ʷ����֮����׷������ʷ����Ȼ�������Ա����Ϣ
	// Ϊʲôָ������_employeeNum�Ѿ��ͷ��ڴ��ٴ���newspaceҲû�ã� 
	//  ��Ϊ�ͷŵ����ڴ��������ʷ���ݶ������ı��ĵ�����ʷ����
	//  ���ڴ������������Ȼ��׷�ӵ��ı��ĵ�����ʷ����
	// ����Ϊ��ÿ�μ�������û����ʷ�ı����ݣ���Ҫ����д�� ��ʷ�ı��������ǵ�ǰ���ڴ���ʷ���ݾ�����
	//ofs.open(FileName , ios::out | ios::app); // ׷��д��
	//ofs << "\n"; // ����׷��д��
	for (int i = 0; i < this->_employeeNum; i++)
	{
		ofs << "ְ����� :"<<this->_employeeArray[i]->_Id 
			<< "\tְ������ :" << this->_employeeArray[i]->_Name
			<< "\tְ�����ű�� :" << this->_employeeArray[i]->_DepartId << endl;
	}
	ofs.close();
	if (this->_employeeNum == 0)
	{
		this->_fileisEmpty = true;
	}
}
void workerSystem::Show_Employee()
{
	if (this->_fileisEmpty) 
	{
		cout<< "�ļ������ڻ��߼�¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < this->_employeeNum; i++ )
		{
			this->_employeeArray[i]->showInfo();// ְ��������ʾ��Ϣ�ķ��� ֱ�ӵ��ü���
		}
	}
	system("pause");
	system("cls");
	
}
int workerSystem::IsExist_Employee(int id)// �ж�ĳ��Ա���Ƿ����
{
	int index = -1;
	for (int i = 0; i < this->_employeeNum; i++)
	{
		if (this->_employeeArray[i]->_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}
void workerSystem::Del_Employee()
{
	if ( this->_fileisEmpty)
	{
		cout << "�ļ������ڻ���ְ����ϢΪ�գ�" << endl;
	}
	else 
	{
		cout << "������������ҵ�Ա����� : " << endl;
		int  Id;
		cin >> Id;
		int index= this->IsExist_Employee(Id);
		if (index != -1)
		{
			//cout << "��ְ������" << endl;
			//this->_employeeArray[0]->showInfo();
			for (int i = index; i < this->_employeeNum -1; i++)
			{
				// ����ǰ�Ʋ���
				this->_employeeArray[i] = this->_employeeArray[i + 1];
			}
			this->_employeeNum--; // ������������Ա�ĸ���
			this->Save(); // �����ļ�
			cout << "ɾ���ɹ���" << endl;
		}
		else
		{
			cout << "��ְ��������!" << endl;
		}
	}
	
	system("pause");
	system("cls");
}
void workerSystem::Change_EmployeeInfo() // ����Ա����Ϣ
{
	if (this->_fileisEmpty)
	{
		cout << "�ļ������ڻ���ְ����ϢΪ��" << endl;
	}
	else
	{
		cout << "�������޸ĵ�ְ����� : " << endl;
		int id;
		cin >> id;
		int ret = this->IsExist_Employee(id); // �ж�һ���Ƿ�������Ա��
		if (ret != -1)
		{
			delete this->_employeeArray[ret];
			int newid = 0;
			string newname = "";
			int dSelect = 0;
			cout << "�Ѿ��鵽��" <<id <<"��ְ�����������µ�ְ�����" <<endl;
			cin >> newid;
			cout << "��������������" << endl;
			cin >> newname;
			cout << "��������ְ��" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dSelect;
			workerIndividual * worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new  worker_Employee(newid, newname, dSelect);//ʹ��worker�������ȥ��̬���ֳ�����
				break;
			case 2:
				worker = new worker_Manager(newid, newname, dSelect);
				break;
			case 3:
				worker = new boss(newid, newname, dSelect);
				break;
			default:
				break;
			}
			// �����޸ĵ�Ա����Ϣ����λ�õ�����
			this->_employeeArray[ret] = worker;
			cout << "�޸�Ա����Ϣ�ɹ�����ְλ���ű��Ϊ��" <<this->_employeeArray[ret]->_DepartId<<endl;
			this->Save();
		}
		else
		{
			cout << "û�д��ˣ��޸�Ա����Ϣʧ��" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workerSystem::Find_Employee() //����Ա��
{
	if (this->_fileisEmpty)
	{
		cout << "�ļ������ڻ���ְ����ϢΪ��" << endl;
	}
	else
	{
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1����ְ����Ų���" << endl;
		cout << "2����ְ����������" << endl;
		int select = 0;
		cin >> select;
		if (select == 1)
		{
			int id;
			cout << "��������ҵ�ְ����ţ�" << endl;
			cin >>id;
			int ret = IsExist_Employee(id);
			if (ret != -1)
			{
				cout << "�ҵ����ˣ���Ա����Ϣ���£�" << endl;
				this->_employeeArray[ret]->showInfo();
			}
			else
			{
				cout << "û�д��ˣ�" << endl;
			}
		}
		else if( select == 2)
		{
			string name;
			cout << "��������ҵ�ְ��������" << endl;
			cin >> name;
			bool flag = false; // ���ҵ��ı�־
			for (int i = 0; i < this->_employeeNum; i++)
			{
				if (this->_employeeArray[i]->_Name == name) 
				{
					cout << "���ҳɹ�����ְ�����Ϊ��" << this->_employeeArray[i]->_Id << endl;
					cout << "��Ա���ľ�����Ϣ���£�" << endl;
					this->_employeeArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false)
			{
				cout << "û�д��ˣ�" << endl;
			}
		}
		else
		{
			cout << "����ѡ������" << endl;
		}
	}
	system("pause");
	system("cls");
}
void workerSystem::Sort_Employee()// Ա���������
{
	if (this->_fileisEmpty)
	{
		cout << "�ļ������ڻ���ְ����ϢΪ��" << endl;
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ķ�ʽ��" << endl;
		cout << "1����ְ���������" << endl;
		cout << "2����ְ����Ž���" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->_employeeNum; i++)
		{
			int minOrmax = i; //������Сֵ�����ֵ�±�
			for (int j = i + 1; j < this->_employeeNum; j++)
			{
				if (select == 1) //����
				{
					if (this->_employeeArray[minOrmax]->_Id > this->_employeeArray[j]->_Id)
					{
						minOrmax = j;
					}
				}
				else // ����
				{
					if (this->_employeeArray[minOrmax]->_Id < this->_employeeArray[j]->_Id)
					{
						minOrmax = j;
					}
				}
			}
			if (i != minOrmax)
			{
				workerIndividual* temp = this->_employeeArray[i];
				this->_employeeArray[i] = this->_employeeArray[minOrmax];
				this->_employeeArray[minOrmax] = temp; 
			}
		}
		cout << "����ɹ����������Ϊ��" << endl;
		this->Save();
		this->Show_Employee();
	
	}
}
void workerSystem::Clean_File() // ����ļ�
{
	cout << "ȷ����գ�" << endl;
	cout << "1. ȷ��" << endl;
	cout << "2. ����" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		ofstream ofs(FileName, ios::trunc); //���������ɾ�����ڴ���
		ofs.close();
		if (this->_employeeArray != NULL) // �������鲻Ϊ��
		{
			for (int i = 0; i < this->_employeeNum; i++)
			{
				if (this->_employeeArray[i] != NULL)
				{
					delete this->_employeeArray[i];//ɾ��ÿ������������
				}
			}
			this->_employeeNum = 0; // ������������
			delete[] this->_employeeArray; // ָ�뱾��Ҳɾ��
			this->_employeeArray = NULL;
			this->_fileisEmpty = true; // ����״̬
		}
		cout << "��ճɹ���"<<endl;
	}
	system("pause");
	system("cls");
}
void workerSystem::ExitSystem() // �˳�ϵͳ
{
	cout << "��ӭ�´�ʹ�ã�" << endl;
	//system("pause");
	exit(0); 
}