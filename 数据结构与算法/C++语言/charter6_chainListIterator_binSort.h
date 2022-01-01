#pragma once
#include "myExceptions.h"
#include "charter5_linearList.h"
#include "charter6_chainNode.h"
#include <ostream>
#include <sstream>
/*
   chainNode<T> **bottom, **top;
   bottom = new chainNode<T>* [range + 1];
   top = new chainNode<T>* [range + 1];
   for (int b = 0; b <= range; b++)
      bottom[b] = NULL;
   for (; firstNode != NULL; firstNode = firstNode->next)
   {
      int theBin = firstNode->element; 
      if (bottom[theBin] == NULL) 
        bottom[theBin] = top[theBin] = firstNode;
      else
      {
        top[theBin]->next = firstNode;
        top[theBin] = firstNode;
      }
   }
   chainNode<T> *y = NULL;
   for (int theBin = 0; theBin <= range; theBin++)
      if (bottom[theBin] != NULL)
      {
            if (y == NULL)
                firstNode = bottom[theBin];
            else 
                y->next = bottom[theBin];
            y = top[theBin];
      }
   if (y != NULL)
      y->next = NULL;
   delete [] bottom;
   delete [] top;
这里来分析为什么这么写？思路是什么，和普通的箱子排序有什么区别？
(1) 普通的箱子排序：需要new一个临时箱子数组(用指向这个数组的指针p表示)
    1)  把不同分数段的学生分别放入1个箱子(链表类型)
          ① 预定义1个指向箱子数组的指针p(链表数组类型的指针)
              箱子数组整合了这些箱子的首地址
              指针的遍历操作比直接数组遍历更快,改变指针的解引用就是改变数组元素
          ② 对要排序的学生链条遍历
               每次总是获取链条首个学生插入对应箱子p[bin],然后学生链条删去这个学生
               运行结果：学生链表成了空链，元素都存在箱子数组中
     2)  把箱子数组从低分箱子到高分箱子依次重新尾插到学生链表中就实现了排序
          ① 遍历每个箱子,每个箱子也是总获取首个学生,插入到学生链表
          ② 在遍历的过程中总是删除箱子的首个学生是必要的
          <因为箱子数组是new出来的,临时变量要清空含有的元素再delete析构掉>
          临时数组指针开辟的内存增加了空间复杂度，插入删除操作增加了时间复杂度
          所以后面升级后的箱子排序最大的不同在于无需临时数组和这些操作,运行速度更快
 (2)  更快的箱子排序：把排序函数作为链表类的成员函数
                                       就可以借助链表类的私有属性头节点firstNode实现排序
        1) 定义2个指向节点数组的指针bottom和top(**chainNode类型指针)
            不借助临时数组的话,直接排序需要先知道每个分数段第1个学生和最后1个学生的位置
            学生是chainNode类型,同时存放多个分数段的第1个学生(地址)就是chainNode*[]数组
            指向指针数组类型的指针自然是**chainNode类型指针
            例如: int a[3] ={1,2,3} ; int *pa = a ; // *类型
                      int b1 =4; int b2 =5; int b3 =6; int *b[3] = {&b1,&b2,&b3}; int **pb = b;
                      注意b和a的区别,b是存放地址的数组,a是存放元素的数组
                      所以b数组的指针pb是int**类型,a数组的指针是int*类型
            ① bottom用于存放每个箱子首节点的地址(首节点在栈底),
                 即bottom[bin]是第bin个箱子的首个学生地址
            ② top用于存放每个箱子尾节点的地址(尾节点在栈首)
                 即top[bin]是第bin个箱子的最后1个学生地址
            说白了,每个箱子都是同分段的学生,这部分是不用进行排序的
            后续只需要把top[bin]和bottom[bin+1]连起来就实现了排序,也就是y指针的作用
        2) 找到每个分数段开始的第1个学生和最后1个学生地址将其存入bottom[bin]和top[bin]
            ① 遍历学生链表(firstNode为当前遍历的学生),首先获取当前学生的分数段bin
            ② bin分数如果是第一次出现,就存入bottom[bin],也存入top[bin]
            ③ bin分数第2次出现,就让top[bin]->next(此时top[bin]还是该分段第1个学生地址)
                 指向firstNode(作为该分段第2个学生),这就实现了同一箱子的第1和2个学生的链接
                 然后更新top[bin]为当前第2个学生的地址,即top[bin]=firstNode;(此时top[bin]是该分段第2个学生地址)
                 假使后面bin分数多次出现<核心代码>：
                 top[bin]->next = firstNode ; // 总是让上1个学生地址指向当前新增的学生(链接操作)
                 top[bin] = firstNode; // 保证下次链接操作的上1个学生地址是当前的学生    
            ④ 运行结果：top[bin]总是指向bin分数段的最后1个学生,bottom[bin]为第1个学生,目的实现
                 同时 firstNode=NULL是遍历学生链表结束循环的条件,因为单向链表的性质尾节点的next指向NULL
        3) 从低分箱子到高分箱子遍历取出学生赋值给学生链表,但是单向链表要保证连续性
             即上1个箱子的尾节点(top[bin])和下1个箱子的头节点(bottom[bin])在 1)和2)中并没有链接
             2)中的③操作只是链接了同一个分数箱子的学生,所以需要1个指针y用来做这件事
             ① 初始化1个chainNode的指针y指向NULL,y是粘合2个节点,所以是chainNode类型的指针
             ② 先判断bottom[bin]是否为NULL,是的话说明这个分数段没有学生
             ③ 如果分数段有学生,就可以继续判断y是否为NULL
                   这时可以解释为何一开始要初始化y指向NULL
                   初始化为NULL是为了当找到第1个有学生的最低分数段(因为分数箱子是从低分到高分遍历)
                           立刻使firstNode = bottom[bin], 即让头节点指向最低分的第1个学生(准备升序)
             ④ 第1次y=NULL成功后执行的是if内的语句(即③只会执行1次,就是为了让firstNode指向最低分的第1个学生)
                   然后y = top[bin],让y等于最低分数段的最后1个学生(先执行),当前遍历结束
                            之所以用"=",因为y是指针,改变y->next就等于改变学生链条top[bin]的next
                   第2次y=NULL不成立(y总是已指向上1个分数段的top[bin]),以后也永远不会成立
                   所以总会执行else语句的y->next = bottom[bin](当前分数段的bottom[bin])(后执行)
                   说白了就是y总是临时记录上个分数段的top,当前遍历时让它指向这个分数段的bottom
                            所以要注意y=top[bin]和y->next=bottom[bin]先后执行的顺序,相当于链接好top[bin]和bottom[bin+1]
                 y粘合工作做完后必然会等于最高分数段的top[bin]
            ⑤ 此时y也已经没什么用,因为相等关系 delete top[bin] 就相当于delete y了
                而delete y之前先将y->next指向NULL,其实就是把top[bin]->next指向NULL
                因为此时学生链表有序,最高分数段的最后1个学生(尾节点)的next应当指向NULL(单向链表的性质决定)
            ⑥ delete bottom 和 top, 整个过程只有临时指针,与普通的箱子排序需要临时数组占据的空间更小
                且临时指针无需insert/erase(时间复杂度O(n))
*/
template<class T>
class _charter6_chainBinSort : public _charter5_linearList<T>
{
public:
    _charter6_chainBinSort(int initialCapacity = 10);
    _charter6_chainBinSort(const _charter6_chainBinSort<T>&);
    ~_charter6_chainBinSort();

    bool empty() const { return listSize == 0; }
    int size() const { return listSize; }
    T& get(int theIndex) const;
    int indexOf(const T& theElement) const;
    void erase(int theIndex);
    void insert(int theIndex, const T& theElement);
    void output(ostream& out) const;
    void binSort(int range,bool log =false);
    void binSort(int range, int(*value)(T& x));
protected:
    void checkIndex(int theIndex) const;
    _charter6_chainNode<T>* firstNode;
    int listSize;        
};
template<class T>

_charter6_chainBinSort<T>::_charter6_chainBinSort(int initialCapacity)
{
    if (initialCapacity < 1)
    {
        ostringstream s;
        s << "Initial capacity = " << initialCapacity << " Must be > 0";
        throw illegalParameterValue(s.str());
    }
    firstNode = NULL;
    listSize = 0;
}

template<class T>
_charter6_chainBinSort<T>::_charter6_chainBinSort(const _charter6_chainBinSort<T>& theList)
{
    listSize = theList.listSize;
    if (listSize == 0)
    {
        firstNode = NULL;
        return;
    }
   
    _charter6_chainNode<T>* sourceNode = theList.firstNode;
    firstNode = new _charter6_chainNode<T>(sourceNode->element);
    sourceNode = sourceNode->next;
    _charter6_chainNode<T>* targetNode = firstNode;
    while (sourceNode != NULL)
    {
        targetNode->next = new _charter6_chainNode<T>(sourceNode->element);
        targetNode = targetNode->next;
        sourceNode = sourceNode->next;
    }
    targetNode->next = NULL; 
}

template<class T>
_charter6_chainBinSort<T>::~_charter6_chainBinSort()
{
    _charter6_chainNode<T>* nextNode;
    while (firstNode != NULL)
    {
        nextNode = firstNode->next;
        delete firstNode;
        firstNode = nextNode;
    }
}

template<class T>
void _charter6_chainBinSort<T>::checkIndex(int theIndex) const
{
    if (theIndex < 0 || theIndex >= listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }

}

template<class T>
T& _charter6_chainBinSort<T>::get(int theIndex) const
{
    checkIndex(theIndex);
    _charter6_chainNode<T>* currentNode = firstNode;
    for (int i = 0; i < theIndex; i++)
        currentNode = currentNode->next;
    return currentNode->element;
}

template<class T>
int _charter6_chainBinSort<T>::indexOf(const T& theElement) const
{
    _charter6_chainNode<T>* currentNode = firstNode;
    int index = 0;  
    while (currentNode != NULL &&
        currentNode->element != theElement)
    {
        currentNode = currentNode->next;
        index++;
    }
    if (currentNode == NULL)
        return -1;
    else
        return index;
}

template<class T>
void _charter6_chainBinSort<T>::erase(int theIndex)
{
    checkIndex(theIndex);
    _charter6_chainNode<T>* deleteNode;
    if (theIndex == 0)
    {
        deleteNode = firstNode;
        firstNode = firstNode->next;
    }
    else
    { 
        _charter6_chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        deleteNode = p->next;
        p->next = p->next->next; 
    }
    listSize--;
    delete deleteNode;
}

template<class T>
void _charter6_chainBinSort<T>::insert(int theIndex, const T& theElement)
{
    if (theIndex < 0 || theIndex > listSize)
    {
        ostringstream s;
        s << "index = " << theIndex << " size = " << listSize;
        throw illegalIndex(s.str());
    }
    // theChain.insert(0, s);  插入的元素s就是stu类型
    if (theIndex == 0) 
    {
        firstNode = new _charter6_chainNode<T>(theElement, firstNode);
        // std::cout << firstNode->element<<std::endl; //打印了插入的信息
        // 不能使用printf,因为T类型是stu类型,定义中已经重载了<<运算符
    }
    else
    {  
        _charter6_chainNode<T>* p = firstNode;
        for (int i = 0; i < theIndex - 1; i++)
            p = p->next;
        p->next = new _charter6_chainNode<T>(theElement, p->next);
    }
    listSize++;
}

template<class T>
void _charter6_chainBinSort<T>::output(ostream& out) const
{
    for (_charter6_chainNode<T>* currentNode = firstNode;
        currentNode != NULL;
        currentNode = currentNode->next)
        out << currentNode->element << "  ";
}

// overload <<
template <class T>
ostream& operator<<(ostream& out, const _charter6_chainBinSort<T>& x)
{
    x.output(out); return out;
}

template<class T>
void _charter6_chainBinSort<T>::binSort(int range,bool log)
{
    // bottom,top是节点数组类型的指针,每个元素指向不同箱子
    // bottom指向箱子首节点(同分段第1个人),top指向尾节点(同分段最后1个人)
    // 后面的y总是先指向上1分段的bottom,然后让它的next等于下一分段的top,这就相当于把所有箱子串起来了
    // 最后y应当是top[10],就是10分的最后1个学生,y是个粘合剂起到串接作用
    // 由于y最后没有用避免y->next成为野指针还要指向NULL,y本身是top[10],delete top就自然删除了y
    cout << "-------" << endl;
    _charter6_chainNode<T>** bottom, ** top; // 指向指针数组本身的指针
    bottom = new _charter6_chainNode<T>*[range + 1]; // 可以看成_charter6_chainNode<T> *bottom[range+1];
    top = new _charter6_chainNode<T>*[range + 1]; // 为何要new?因为只是临时变量后边会删除
    for (int b = 0; b <= range; b++) // 每个分数挡位的箱子链条都已经初始化为NULL
        bottom[b] = NULL; 
    // 对自己排序,单向链表尾节点指向NULL
    char name[] = { 'a','b','c','d','e',   'f','g','h','i','j',   'k','l','m','n','o',    'p','q','r','s','t',  'u' };
    int idx = 0;
    if (log == true)
        cout << "开始把学生放入不同的箱子分类：" << endl;
    for (; firstNode != NULL; firstNode = firstNode->next) 
    { // 20个学生开始遍历
        // 这里firstNode->element是个stu类型
        int theBin = firstNode->element; // 这里因为重载了int(),可以把stu类型强转为int类型,返回的其实是stu的分数
        // printf("bin = %d", theBin); //10,9,8,...,0  拿到每个学生的分数
        if (bottom[theBin] == NULL) // 如果箱子没被用过(刚进入循环时都执行if的内部语句)
        {
            bottom[theBin] = top[theBin] = firstNode; // 让箱子的开头等于theBin分段出现的第1个学生firstNode
            // 下方输出语句说明bottom[theBin]和firstNode->next此刻就是1个东西
            // bottom[theBin]->next就是指向下1个学生,特别的如果是最低分的指向为NULL,因为外部测试程序中0分学生是最后插入的
            if (log == true)
                cout << "name = "<<name[idx]<<" box["<<theBin<<"] not use  bottom[" << theBin << "][0] = "<<firstNode <<
                "\n\tbottom[" << theBin << "]->next = "<< bottom[theBin]->next<<" firstNode->next = "<<firstNode->next<<endl;
        }
        else
        {
            // firstNode是bin分段的第2个学生(如果有的话),top[theBin]是bin分段的第1个学生
            if (log == true)
                cout << "name = " << name[idx] << " box["<<theBin<<"] is use =  bottm["<<theBin<<"][1] = " << firstNode << endl;
            
            // top[theBin]是上1个学生 cout << top[" << theBin << "] = " << top[theBin] << endl; 
            top[theBin]->next = firstNode; // 第1个学生指向第2个学生,同一分段的学生进行串接
            top[theBin] = firstNode;// 再让top[theBin]从第1个学生改为等于第2个学生
            // 如果这个分段还有很多学生,如此操作top[theBin]总是等于该分段的最后一个学生
        }
        idx++;
    }
    // 上述程序结束箱子数组的每个箱子都串好了每个学生,现在要按分数高低拿出来
    _charter6_chainNode<T>* y = NULL; // 1个指向NULL的指针
    if (log == true)
        cout << "开始把学生从低分到高分箱子依次取出：" << endl;
    int theBin = 0;
    for (theBin = 0; theBin <= range; theBin++) // 按分数从小到大遍历每个分数箱子
        if (bottom[theBin] != NULL) // 如果箱子没被用过就下1个箱子,用过的地址不会是NULL
        { 
            if (y == NULL) // 第1个用过的最低分数箱子会执行if语句,且只会执行1次
            {
                if (log == true)
                {
                    // 下方语句firstNode为NULL,这是因为上述循环firstNode=NULL时结束
                    // bottom[theBin]->next是NULL,这是因为外部测试程序0分学生是尾节点的唯一一个,它下一个就是NULL
                    // 所以为了测试是否bottom[theBin]已经自动串联了下1个学生(如果有的话),外部程序额外插入了1个0分学生u
                    // 此时bottom[theBin]->next不再是空,而是第2个0分学生的地址,如果再下1个就又是NULL了
                    cout  << "\tbottom["<< theBin<<"]->next = " << bottom[theBin]->next
                    << "\n\tbottom["<<theBin<<"]->next->next = " << bottom[theBin]->next->next << endl;
                    cout << "bottom["<< theBin<<"] = " << bottom[theBin] << endl;
                }
                firstNode = bottom[theBin]; // 让首节点等于分数最低的那个箱子的第一个学生地址(尾节点)
                if (log == true)
                    cout << "\tfirstNode = " << firstNode << endl;
            }
            else
            {     
                if (log == true)
                {
                    // 下方bottom[theBin]与上边每个箱子box not use 的地址对应,就是每个分数箱子的第1个学生
                    // 且next是下一个学生的信息,再next不是同分段(因为测试程序中除了10分只有1人其它分数段都是2人)
                    cout <<"\tbottom[" << theBin << "]->next = " << bottom[theBin]->next
                    << "\n\tbottom[" << theBin << "]->next->next = " << bottom[theBin]->next->next << endl;
                }
                y->next = bottom[theBin];// 最低分箱子找到了就不会再执行if,总是让y指向当前箱子的第1个学生
                if (log == true)
                {
                    cout << "top[" << theBin - 1 << "]  = " << y << endl;
                    cout << "top[" << theBin - 1 << "]->next  = " << y->next << " = bottom["<<theBin<<"] = "
                         << bottom[theBin] << endl;//当前分段的第1个元素
                }
            }
            // 注意执行顺序,先执行y->next = bottom[theBin]再执行y=top[theBin](后执行)
            y = top[theBin]; // top[theBin]已经指向同分段的最后1个学生,让y等于它
            /*
                1. theBin=0第1次循环, if中firstNode指向了0分的第1个学生(栈底)
                    然后才让y=top[theBin],y就是0分学生2;结束循环
                2.theBin=1第2次循环, 执行else,让y的next指向1分的第1个学生;然后y=top[theBin],y从0分变成1分学生2;结束循环
                3.以此类推,可以看出bottom和top的用处是用于存储每个箱子的头节点和尾节点的地址,共11个值
                   y就是临时的粘合剂将上分段最后1个和下分段第1个串起来,y=>NULL=>top[0]=>bottom[0]=>top[1]=>bottom[1]=>...=>top[9]
                4.theBin=10第11次循环,y=top[9],执行else,y->next=bottom[10](最后1个分段),然后y=top[10]for循环彻底结束
            */
        }
    theBin = 10; // 恢复到10, 上述程序运行完后theBin = 11了
    if (log == true)
        cout << "top[" << theBin << "] = " << top[theBin] << endl; // 注意到top[10]和bottom[10]相等因为只有1个元素
    // 上述for结束后y = top[10]
    if (y != NULL)
        y->next = NULL; // 置空避免成为野指针

    delete[] bottom;
    delete[] top; // y = top[10] delete top <=> delete y
}

// 唯一的不同是把int theBin = firstNode->element; 变成了int theBin = value(firstNode->element);
template<class T>
void _charter6_chainBinSort<T>::binSort(int range, int(*value)(T& x))
{
    _charter6_chainNode<T>** bottom, ** top;
    bottom = new _charter6_chainNode<T>*[range + 1];
    top = new _charter6_chainNode<T>*[range + 1];
    for (int b = 0; b <= range; b++)
        bottom[b] = NULL;

    for (; firstNode != NULL; firstNode = firstNode->next)
    {
        // 以前: int theBin = firstNode->element; 
        cout << "value = " <<value << endl;
        int theBin = value(firstNode->element); // 唯一的不同点变成value里边的
        if (bottom[theBin] == NULL) 
            bottom[theBin] = top[theBin] = firstNode;
        else
        {
            top[theBin]->next = firstNode;
            top[theBin] = firstNode;
        }
    }

    _charter6_chainNode<T>* y = NULL;
    for (int theBin = 0; theBin <= range; theBin++)
        if (bottom[theBin] != NULL)
        {
            if (y == NULL) 
                firstNode = bottom[theBin];
            else 
                y->next = bottom[theBin];
            y = top[theBin];
        }
    if (y != NULL)
        y->next = NULL;

    delete[] bottom;
    delete[] top;
}
