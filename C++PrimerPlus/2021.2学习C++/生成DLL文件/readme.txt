第一步：在头文件pch.h中声明函数有哪些
extern "C" _declspec(dllexport) int myAdd(int a, int b);
第二步：在源文件的pch.cpp定义函数
第三步：项目-属性-平台选择x64，同时配置管理器中也要选择x64
第四步：链接器-高级-选择目标计算机-选择x64
第五步：菜单栏-生成-生成dll
第六步：python中
from ctypes import *
# 不能使用cdll.LoadLibrary()和windll.LoadLibrary()，使用CDLL函数不会出错
C__ =CDLL('C:\\Users\\chenbei\\Documents\\Visual Studio 2019\\项目文件\\Dll1\\Debug\\Dll1.dll')
C__.add(1,2)
参考方案：
①https://blog.csdn.net/qq_42214953/article/details/105628838?utm_medium=distribute.pc_relevant.none-task-blog-baidujs_title-2&spm=1001.2101.3001.4242
②https://blog.csdn.net/nodely/article/details/107163015?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-7.control&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromBaidu-7.control
