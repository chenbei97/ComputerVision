#include <iostream>
#include <vector>
int knm = 4;
int abc = 10;
using namespace std;
vector<int> fibon_seq1(int loc);
const vector<int> * fibon_seq2(int loc);
void local_static_variable() {
    auto ans1 = fibon_seq1(20);
    for (int i = 0; i < ans1.size(); i++) {
        cout << ans1[i] << " ";
        if ((i + 1) % 5 == 0)
            cout << "\n";
    }
    const vector<int>* ans2 = fibon_seq2(20);
    for (int i = 0; i < ans2->size(); i++) {
        cout << (*ans2)[i] << " ";
        if ((i + 1) % 5 == 0)
            cout << "\n";
    }
    cout << "ans2 addr is " << ans2 << endl;
    ans2 = fibon_seq2(10);
    for (int i = 0; i < ans2->size(); i++) {
        cout << (*ans2)[i] << " ";
        if ((i + 1) % 5 == 0)
            cout << "\n"; //��ӡ�Ļ���Ȼ��20��
    }
    cout << "ans2 addr is " << ans2 << endl;
    ans2 = fibon_seq2(40);
    for (int i = 0; i < ans2->size(); i++) {
        cout << (*ans2)[i] << " ";
        if ((i + 1) % 5 == 0)
            cout << "\n"; //���40��
    }
    cout << "ans2 addr is " << ans2 << endl; // ��ַû��
}
vector<int> fibon_seq1(int loc) {
    const int maxLoc = 1024; // ���еĵ�10024��Ԫ�ش�С������int���ܱ�ʾ�����ֵ
    if (loc <= 0 || loc >= maxLoc)
    {
        cerr << "the loc > 1024 or < 0 is not supported -- resetting to 8\n";
        loc = 8;
    }
    vector<int> ans(loc); // ���ȷ��������
    for (int i = 0; i < loc; i++) {
        if (i == 0 || i == 1)
            ans[i] = 1;
        else ans[i] = ans[i - 1] + ans[i - 2]; //ֱ�Ӹ�ֵ
    }
    return ans; // �ֲ�����ֻ��ֵ���ݿ���,���ܴ��ݵ�ַ
}
const vector<int>* fibon_seq2(int loc) {
    const int maxLoc = 1024;
    static vector<int> ans; // ֻ�����״ε��ó�ʼ��,֮�󲻻�
    cout << "ans addr is " << &ans << endl;
    if (loc <= 0 || loc >= maxLoc)
    {
        cerr << "the loc > 1024 or <0 is not supported -- resetting to 8\n";
        return nullptr;
    }
    for (int i = ans.size(); i < loc; i++) { //���������loc<an.size()�Ͳ����ټ���
        if (i == 0 || i == 1)
            ans.push_back(1);
        else ans.push_back(ans[i - 1] + ans[i - 2]);
    }
    return &ans;
}