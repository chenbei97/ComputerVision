#%%1、元素赋给向量数组
import numpy as np
#1.1、行操作
a=np.array(['1','2','3'])#字符型数组
b=np.array([1,2,3])
a[2]=4#单个字符赋给行数组
b[2]=4
print(a,b)
print(len(a))#3
print(len(b))#3

for i in range(len(a)):
    print(a[i])
    print(b[i])#循环输出向量数组元素是可以的

for i in range(len(a)):
    a[i]=1
    b[i]=1
print(a,b)#单个元素循环更新行向量数组元素是可以的
#%%
#1.2、列操作
import numpy as np
a=np.array([1,2,3,4])#是1行，但属性显示4，表示元素个数
print(len(a))#4

#c=np.transpose (a)#只有这一句没反应
a.shape=(1,-1)#原数组是1行，但属性变为1，表示行个数，可以理解为不塑形时数组是不知道自己形状的
print(len(a))#1,因为shape命令变成1理解为塑形后返回行个数为1
c=np.transpose(a)#方法1：transpose是基于shape的，现在有反应

#c=a.T#没反应
a.shape=(-1,1)#，方法2：将原来的a更改为列数组，是对原的修改，属性变回4，但格式为列
c[2]=10#单个字符赋值给列数组可行
print(len(a))#4,塑形后返回行个数4，后边在多维数组中输出的也是行个数

c=a.reshape(-1,1)#方法3：有反应，只用这一句替代也可以
d=np.array([5,6,7,8]).reshape(-1,1)#直接定义列向量

print(len(c))#4
print(len(d))#4

for j in range(len(c)):#len(c)=4，循环输出列数组元素是可以的
    print(c[j])#输出结果是加了中括号的，代表按行输出的

for j in range(len(d)):
    c[j]=d[j]#单个元素循环替代列向量数组元素是可以的
print(c)
#综上，无论行列，只要循环次数正确，都是直接索引单个序号，不用加逗号区分行列
#%%2、元素赋给多维数组
import numpy as np
import copy
c=np.array([[1,2,3,4],[5,6,7,8]])
#d=np.array([[1,2],[3,4],[5,6]])
#c[1,2]=5#单个元素赋给多维数组
#print(c)，元素改变了
#print(np.size(c))#8，多少个元素
#print(len(c))#2,不是4，行个数是长度
#print(len(d))#3,证明len是行个数
hang=c.shape[0]
lie=c.shape[1]

for i in range(hang):#先行后列循环,按行依次输出多维数组的元素1,2,3,4,5,6,7,8
    for j in range(lie):
        print(c[i,j])

for i in range(lie):#先列后行循环,按列依次输出多维数组的元素1,5,2,6,3,7,4,8
    for j in range(hang):
        print(c[j,i])

tem=np.array([[10,11,12,13],[14,15,16,17]])#用同型的元素替换c
for i in range(hang):#c发生变化
    for j in range(lie):
        c[i,j]=tem[i,j]#循环以后c=tem
c[1]=tem[0]#对整行赋值可行
c[1,2]=10#对特定元素赋值可行,c=[10,11,12,13;10,11,10,13]

tem1=np.array([1,2,3,4,5,6])#不同型用切片，数量正确即可
c[1]=tem1[2:6]#把3，4，5，6给了c第2行
tem1.reshape(-1,1)#列向量也可以直接赋值给多维数组的行向量
c[0]=tem1[0:4]#将1，2，3，4给了c第1行
#%%循环把一个多维数组赋给空数组
import numpy as np
import copy
a=np.array([[1,2,3,4],[5,6,7,8],[9,10,11,12]])
hang=a.shape[0]
lie=a.shape[1]
b=np.zeros(shape=(hang,lie))#如果不事先定义好b的大小，也就是没有塑形，b[i]=a[i]不再是每行依次赋值，而是替换，可能第一次赋值时自动塑形好了，下一次就不能成功，出现超过范围的错误
for i in range(len(a)):
    b[i]=a[i]
#%%浅拷贝和深拷贝以及直接等号的区别
import copy
a = [1,2,3,"hello",["python","C++"]]
b = a
b.append("ADD")#a=[1, 2, 3, 'hello', ['python', 'C++'], 'ADD']b=[1, 2, 3, 'hello', ['python', 'C++'], 'ADD']
print(a,b)#发现改变b也就改变了a，a、b只是一个名字或者引用，真正的内存地址只有1个，不会给b单独开辟内存，对任何一个改变都会影响另一方
#浅拷贝，切片操作，工厂函数，copy模块中的copy函数，b = a[:]，b = list(a)，b = copy.copy(a)都会创建新对象，改变b不再改变a
c = a[:]
c.append("C")#此时改变c不会改变a
print(a,c)#a=[1, 2, 3, 'hello', ['python', 'C++'], 'ADD']c=[1, 2, 3, 'hello', ['python', 'C++'], 'ADD', 'C']
c[4].append("A")#c嵌套了内层的一个list，即第4个，浅拷贝只复制了1层，对内层添加元素A仍然会改变a,因为a改变，b也改变了，c只多了个第一层添加的C
print(a,b,c)#a=[1, 2, 3, 'hello', ['python', 'C++', 'A'], 'ADD'] b=[1, 2, 3, 'hello', ['python', 'C++', 'A'], 'ADD'] c=[1, 2, 3, 'hello', ['python', 'C++', 'A'], 'ADD', 'C']
#深拷贝
#深拷贝只有一种形式，copy模块中的deepcopy函数
e = copy.deepcopy(c)
e[4].append("B")
print(c,e)#e内层添加B不再影响c
#%%3、多维数组赋给多维数组，除了上述的用同型或不同型的替换多维数组的一部分外，还有多维数组自身的交换操作
import numpy as np
import copy
a=np.array([[1,2,3,4],[5,6,7,8],[11,12,13,14]])
tem=a[0]#这一步temp=1,2,3,4,a没有变化
a[0]=a[2]#用第3行覆盖了第1行，a发生了变化，此时注意：因为tem只是a[0]的别名，它们共同指向一个地址，当a[0]被覆盖以后tem也随之改变为11,12,13,14
a[2]=tem#此时因为tem不再是1,2,3,4所以导致交换失败，第1行和第3行都是11,12,13,14
#解决方法1
a=np.array([[1,2,3,4],[5,6,7,8],[11,12,13,14]])
a[[1,2],:]=a[[2,1],:]#实现了第2,3行的交换
#解决方案2
a=np.array([[1,2,3,4],[5,6,7,8],[11,12,13,14]])
tem=copy.copy(a[0])#浅层复制创建新对象就可以不改变原来的a值
a[0]=a[2]
a[2]=tem
#%%#例子：实现一个任意矩阵的两行交替替换，第2行被第1行替换，第3行被第2行替换，类推置第1行被最后1行替换
import numpy as np
import copy
def change(array):
    hang=array.shape[0]
    lie=array.shape[1]
    if hang <=1:
        return False
    else:
           tem=np.zeros(shape=(hang,lie))#塑形
           for i in range(hang-1):#循环用tem的当前行替换array的下一行，最后只剩第1行没被替换，hang=5,i+1会到5超出范围
               tem[i+1]=array[i]
           tem[0]=array[-1]#替换第一行，不能对array操作，否则运行后原来的就被改变了，相反利用array的信息得到一个新的空文件用来存放交换顺序的结果
    #print(tem)
    return tem
a=np.arange(1,21,1).reshape(5,4)
b=change(a)
print(a,b)
#%%#4、第三方变量接收，不改变原有变量值
import numpy as np
c=np.array([[1,2,3,4],[5,6,7,8]])
temp=c[1]#第2行,整行赋值
print(temp)
temp=c[:,1]#第2列，整列赋值
print(temp)#输出格式行,不过观察temp确实是列，

c=np.array([[1,2,3,4],[5,6,7,8]])
c.reshape(-1,1)#不会改变原来的c的存储形式,c.reshape(1,-1)也不改变
print(c.reshape(-1,1))#输出格式1列
tem=c[:,1]#第2列，c不发生改变,本身是列
print(tem)#输出格式1行
tem.reshape(1,-1)#本身还是列，不改变，但是输出格式会变
print(tem.reshape(-1,1))#输出格式1列，说明reshape可以改变打印格式


c=np.array([[1,2,3,4],[5,6,7,8]])
d1=c.reshape(-1,1)#变成1列
d2=c.reshape(1,-1)#变成1行
print(d1,d2)#输出格式是1列和1行
print(c)#说明reshape语句必须是面向对象的，原本的c不会改变
#综上，结合3的矩阵交换程序，只要不对矩阵本身执行替换，赋值等操作就不会改变自身，而reshape等都是面向复制本的