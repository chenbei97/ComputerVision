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
            cout << "\n"; //打印的话依然是20个
    }
    cout << "ans2 addr is " << ans2 << endl;
    ans2 = fibon_seq2(40);
    for (int i = 0; i < ans2->size(); i++) {
        cout << (*ans2)[i] << " ";
        if ((i + 1) % 5 == 0)
            cout << "\n"; //变成40个
    }
    cout << "ans2 addr is " << ans2 << endl; // 地址没变
}
vector<int> fibon_seq1(int loc) {
    const int maxLoc = 1024; // 数列的第10024个元素大小超过了int所能表示的最大值
    if (loc <= 0 || loc >= maxLoc)
    {
        cerr << "the loc > 1024 or < 0 is not supported -- resetting to 8\n";
        loc = 8;
    }
    vector<int> ans(loc); // 事先分配好容量
    for (int i = 0; i < loc; i++) {
        if (i == 0 || i == 1)
            ans[i] = 1;
        else ans[i] = ans[i - 1] + ans[i - 2]; //直接赋值
    }
    return ans; // 局部对象只能值传递拷贝,不能传递地址
}
const vector<int>* fibon_seq2(int loc) {
    const int maxLoc = 1024;
    static vector<int> ans; // 只会在首次调用初始化,之后不会
    cout << "ans addr is " << &ans << endl;
    if (loc <= 0 || loc >= maxLoc)
    {
        cerr << "the loc > 1024 or <0 is not supported -- resetting to 8\n";
        return nullptr;
    }
    for (int i = ans.size(); i < loc; i++) { //如果想计算的loc<an.size()就不必再计算
        if (i == 0 || i == 1)
            ans.push_back(1);
        else ans.push_back(ans[i - 1] + ans[i - 2]);
    }
    return &ans;
}