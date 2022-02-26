#pragma once
#include <iostream>
#include <cmath> // or #include <math.h>
#include <stdlib.h>
#include <cstring>
#include <vector> // 动态数组不固定长度
#include <deque>
#include <algorithm>
#include <array> // 动态数组固定长度
#include <ctime>
#include <fstream>
#include <cctype>
//include <string.h>
using namespace std;
void Study_cout_and_cin();
void Study_struct();
void Study_union();
void Study_enum();
void Study_pointer();
char* Study_pointer_getname(void);
void Study_compare_arr_vector_array();
void Study_Text_IO();
void Study_Func_Arr();
void Study_Const_Pointer();
void Study_Func_Pointer();
void Study_Quote();
void Study_Func_Template();
void Study_Class_inheritance();
void Study_STL();
void Compare_array_pointer();
void Study_allocate_release_arr2D();
void Study_Exception_Handle();
void recursion_accumulation_of_summationFunction();
void local_static_variable();
void function_pointer_use();
const int knn = 6; // 不会多重定义
// int knm = 6; // 会多重定义
extern int knm; // 需要在外部初始化他
const int vec[3] = { 1,2,3 };
const int knp = 1;
//extern int kpp = 6; // 也不允许