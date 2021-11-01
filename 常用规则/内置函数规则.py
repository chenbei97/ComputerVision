#%%
'''内置函数共68个，主要分为12类
abs()           dict()        help()         min()         setattr()
all()           dir()         hex()          next()        slice()
any()           divmod()      id()           object()      sorted()
ascii()         enumerate()   input()        oct()         staticmethod()
bin()           eval()        int()          open()        str()
bool()          exec()        isinstance()   ord()         sum()
bytearray()     ﬁlter()       issubclass()   pow()         super()
bytes()         ﬂoat()        iter()         print()       tuple()
callable()      format()      len()          property()    type()
chr()           frozenset()   list()         range()       vars()
classmethod()   getattr()     locals()       repr()        zip()
compile()       globals()     map()          reversed()    __import__()
complex()       hasattr()     max()          round()
delattr()       hash()        memoryview()   set()
'''
'''1、数据类型'''
# 6个函数
# bool 、 int 、 float 、complex
# all() 可迭代对象中全部是True, 结果才是True
# any() 可迭代对象中有一个是True, 结果就是True
bool(1)

'''2、进制转换'''
# 3个函数
# bin 、otc 、 hex 转化为二、八、十进制

'''3、数学运算'''
# 12个函数
# abs 、range、 sum 、min 、max 、len 、sorted(lst,reverse=True,key)是否倒叙、按关键词排序
lst = ['one', 'two', 'three', 'four', 'five', 'six']
def f(s):
    return len(s)
l1 = sorted(lst, key=f, reverse= True) #按照字符串长度给出排序
# round 、 pow(a,b) 、 divmode（返回商和余数）
# enumerate() 获取集合的枚举对象
lst = ['one','two','three','four','five']
for index, el in enumerate(lst,1):    # 把索引和元素一起获取,索引默认从0开始. 可以更改
    print(index) #从1开始 ，1、2、3、4、5
    print(el)

'''4、数据结构'''
# 7个函数
# 4.1、list() 、 tuple() 、dict()、set() 集合
# 4.2、reversed() 翻转序列
List = "你好"
List_reverse =list(reversed(List))
# 4.3、slice(start,stop,step) 切片
ls = [1,2,3,4,5,6,7]
s = slice(1,3,1)
ls[s] # 返回 2,3
# 4.4、format 格式化输出
s = "hello world!"
print(format(s, "^20"))  #剧中
print(format(s, "<20"))  #左对齐
print(format(s, ">20"))  #右对齐
print(format(3, 'b' ))    # 二进制:11
print(format(97, 'c' ))   # 转换成unicode字符:a
print(format(11, 'd' ))   # ⼗进制:11
print(format(11, 'o' ))   # 八进制:13
print(format(11, 'x' ))   # 十六进制(⼩写字母):b
print(format(11, 'X' ))   # 十六进制(大写字母):B
print(format(123456789, 'e' ))      # 科学计数法. 默认保留6位小数:1.234568e+08
print(format(123456789, '0.2e' ))   # 科学计数法. 保留2位小数(小写):1.23e+08
print(format(123456789, '0.2E' ))   # 科学计数法. 保留2位小数(大写):1.23E+08
print(format(1.23456789, 'f' ))     # 小数点计数法. 保留6位小数:1.234568
print(format(1.23456789, '0.2f' ))  # 小数点计数法. 保留2位小数:1.23
print(format(1.23456789, '0.10f'))  # 小数点计数法. 保留10位小数:1.2345678900
print(format(1.23456789e+3, 'F'))   # 小数点计数法. 很大的时候输出INF:1234.567890

'''5、类型转换'''
# 4个函数
# 字符串 str()
# bytes 字符串转bytes类型
bs = bytes("今天吃饭了吗", encoding="utf-8")
# bytearray() 字节数组 、字的元素是可变的, 并且每个元素的值得范围是[0,256)
ret = bytearray("alex" ,encoding ='utf-8')
# repr() 返回一个对象的string形式
s1 = "今天\n吃了%s顿\t饭" % 3
print(s1)#今天# 吃了3顿    饭
print(repr(s1))   # 原样输出,过滤掉转义字符 \n \t \r 不管百分号%
#'今天\n吃了3顿\t饭

'''6、查找元素'''
# 3个函数
#ord() 输入字符找带字符编码的位置
print(ord('a'))  # 字母a在编码表中的码位:97
print(ord('中'))  # '中'字在编码表中的位置:20013
#chr() 输入位置数字找出对应的字符
print(chr(65))  # 已知码位,求字符是什么:A
print(chr(19999))  #丟
#ascii() 是ascii码中的返回该值 不是就返回u
print(ascii("@")) # ’@‘

'''7、压缩处理函数'''
# 3个函数
# 打包函数 zip
lst1 = [1, 2, 3, 4, 5, 6]
lst2 = ['醉乡民谣', '驴得水', '放牛班的春天', '美丽人生', '辩护人', '被嫌弃的松子的一生']
lst3 = ['美国', '中国', '法国', '意大利', '韩国', '日本']
print(zip(lst1, lst1, lst3))  #<zip object at 0x00000256CA6C7A88>
for el in zip(lst1, lst2, lst3):
    print(el)
# fiter(function. Iterable) 过滤函数 function: 用来筛选的函数
def fun(i):
    return i % 2 == 1 #返回奇数
lst = [1,2,3,4,5,6,7,8]
print(list(filter(fun,lst)))
# map(function,iterable)根据提供的函数对指定序列列做映射
def f(i):
    return i*2
lst = [1,2,3,4,5,6,7]
print(list(map(f, lst) )) # 每个元素映射为2倍

'''8、作用域函数'''
# 2个函数
# locals() 返回当前作用域中的名字
# globals() 返回全局作用域中的名字

'''9、迭代函数'''
# 2个函数
# next() 迭代器向下执行一次, 内部实际使⽤用了__ next__()⽅方法返回迭代器的下一个项目
# iter() 获取迭代器, 内部实际使用的是__ iter__()⽅方法来获取迭代器
lst = [1,2,3,4,5]
it = iter(lst)  #  __iter__()获得迭代器
print(it.__next__())  #1
print(next(it)) #2  __next__()
print(next(it))  #3
print(next(it))  #4

'''10、字符串类型代码的执行'''
# 3个函数
# eval() 执行字符串类型的代码. 并返回最终结果
# exec() 执行字符串类型的代码
# compile() 将字符串类型的代码编码. 代码对象能够通过exec语句来执行或者eval()进行求值

'''11、输入输出函数'''
# 3个函数
# print() : 打印输出
# input() : 获取用户输出的内容
# import 加载模块

'''12、其他函数'''
# 5个函数
#12.1、hash() : 获取到对象的哈希值(int, str, bool, tuple). hash算法:(1) 目的是唯一性
#(2) dict 查找效率非常高, hash表.用空间换的时间 比较耗费内存
#12.2、open() : 用于打开一个文件, 创建一个文件句柄
f = open('file',mode='r',encoding='utf-8')
f.read()
f.close()
#12.3、help
#12.4、callable() : 用于检查一个对象是否是可调用的. 如果返回True, object有可能调用失败, 但如果返回False. 那调用绝对不会成功
#dir() : 查看对象的内置属性, 访问的是对象中的__dir__()方法
