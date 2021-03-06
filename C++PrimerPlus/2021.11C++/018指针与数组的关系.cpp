#include "all.h"
void Compare_array_pointer()
{
	//<1>一维普通数组 int []
	cout << "1--------->" << endl;
	int c[5] = { 0,1,2,3,4 };
	cout << c[1] << endl; // c看成数组,可以使用[]访问
	cout << c << "   " << c[0] << "   " << &c[0] << "   " << &c << endl;
	// c的含义等价于&c[0]也就是首元素的地址,也是c本身的地址&c
	cout << *c << endl; // 对a解引用就是对&c[0]解引用也就是c[0]也就是首元素0
	// c++; c是数组,数组名是个地址,数组不能等价于指针,c++是非法的，相当于&c[0]++

	// <2>指向一维普通数组的int*指针
	// 指向一维普通数组变量本身
	cout << "\n2--------->" << endl;
	int* pc = c; // pc和c完全是1个东西,区别在于pc可以++
	cout << pc << "   " << c << "   " << *pc << endl;
	pc++;
	cout << pc << "   " << &c[1] << "   " << c[1] << endl; //pc移动指针到c的第1个元素的地址&c[1]

	// <3>指向一维普通数组的int (*)指针
	// 指向一维普通数组变量本身的地址
	cout << "\n3--------->" << endl;
	int(*pb2)[5] = { NULL }; // 不显示初始化只能使用0或者NULL,且不能多于1个元素
	int arr[5] = { 0,1,2,3,4 };
	int(*pb3)[5] = &arr; // (*)[]可以指向一维普通数组的地址也可以指向二维数组
	cout << pb3 << "   " << *pb3 << endl; // pb3是&arr,8pb3也就是arr,数组名和数组地址值上相等
	pb3++; // 移动到一个新的一维普通数组的地址
	cout << pb3 << "   "  << *pb3 <<"   "<< &arr[1] << "   " <<**pb3<<endl; // 从pb3和*pb3的结果不等于&arr[1]来看说明并没有移动到下一个元素的地址


	// <4>指针数组 int *[]
	cout << "\n4--------->" << endl;
	int a1 = 1, a2 = 2, a3 = 3, a4 = 4, a5 = 5;
	int* a[5] = { &a1,&a2,&a3,&a4,&a5 };// 指针数组,先和[]结合,强调是一个数组
	cout << a << "   " << &a << "   " << *a << "   " << a[0] << "   " << *(a[0]) << endl; // a[0]是1个地址和*a相同,但不是a[0]自身的地址,a[0]自身的地址是a或者&a
	int** t1 = a; // a是一个数组,也是1个地址,故其实也可以看成1个指针,如果再有一个指针指向它就是**类型
	int* (*t2)[5] = { &a }; // 对a取地址,说明没把a看成指针,更倾向看成数组,这个数组是具有5个地址元素的,t2再指向它,所以t2是*(*)[5]类型

	// <5>指向一维指针数组的int **指针 
	cout << "\n5--------->" << endl;
	// a++;  a是1个地址,这个地址是一个数组的首地址,不是指针,所以不能++
	//(&a)++; 非法
	//&a++; 非法
	int** pa1 = a; // pa1是指针,值是地址,pa1和a完全相同,*pa1也与*a和a[0]相同,**pa1是对a[0]解引用和*(a[0])相同
	cout << pa1 << "   " << a << "   " << *pa1 << "   " << **pa1 << "   " << endl;
	// 但是pa是可以++ 的,a不能++
	pa1++;
	cout << *(pa1) << "   " << a[1] << "   " << **pa1 << endl; // 对pa1++就是移动指针到指针数组的第2个元素2的地址

	// <6>指向一维指针数组的int *(*)[n]指针
	cout << "\n6--------->" << endl;
	int* (*pa2)[5] = &a; // pa2是指针,这个指针类型指向具有5个元素数组a的地址而不是a,故对pa2解引用*pa2=a,**pa2是a[0],***pa2才是值
	cout << pa2 << "   " << a << "   " << *pa2 << "   " << **pa2 << "   " << "   " << ***pa2 << endl;
	pa2++; // 指针移动到下一块内存,但是这个内存跟a其实没有任何关系,也不与a的任何元素有关系
	cout << *pa2 << "   " << **pa2 << endl; // 此时的*pa2解引用应当是另一个具有5个元素数组的地址,只是还没赋值,**pa2继续解引用没有意义

	// <7>二维指针数组int *( *[])[n]
	cout << "\n7--------->" << endl;
	int* k[5] = { &a5,&a4,&a3,&a2,&a1 };
	int* (*pa3[])[5] = { &a,&k }; // pa3是一个二维指针数组,不可以++
	cout << pa3 << "   " << &pa3 << "   " << &pa3[0] << endl; // pa3反正是个数组,数组取地址和输出的数组名以及数组首元素地址在值上是相等的,只是类型不同
	cout << pa3[1] << "   " << &k << "   " << k << endl; // 结果是这3个值完全相同,二维指针数组的第2个元素就是第2个指针数组的地址

	// <8>指向二维指针数组的int *(**)[n]指针
	cout << "\n8--------->" << endl;
	// 把二维数组看成一个变量，这个指针指向的是变量本身(1个地址/指针),所以指针类型是*(**)[]类型
	int* (**pa4)[5] = pa3; // 二维指针数组不能++,那么可以定义这样一个指针就可以++了
	pa4++; // pa4是一个指向pa3的指针,pa4移动到pa3的第2个元素的地址,也就是pa3[1]的地址
	cout << pa4 << "   " << &pa3[1] << endl; // 所以pa4此时和&pa3[1]相等
	cout << *pa4 << "   " << pa3[1] << endl; // 解引用后就是pa3[1]的元素,是1个地址

	// <9>指向二维指针数组的int  (* (*)[m])[n]类型
	cout << "\n9--------->" << endl;
	int* (*(*pa5)[2])[5] = &pa3; // pa5是一个*(*(*)[2])[5]类型的指针，指向了一个二维指针数组
	cout << pa5 << "   " << pa3 << "   " << &pa3 << endl; // pa5是这个指针的地址,也就是pa3的地址,pa3是个二维指针数组变量本身
	pa5++; //类似于pa2,虽然可以++，单数实际上没有意义，解引用应当是另一个具有2个指针数组的二维指针数组
	cout << *pa5 << "  " << **pa5 << endl;


	// <10> 二维普通数组int [m][n]
	// 普通二维数组和指针数组有些相似,因为这个数组实际存放的是3个具备5个元素的一维数组地址而不是值
	cout << "\n10--------->" << endl;
	int b[3][5] = { {100,1,2,3,4},{5,6,7,8,9},{10,11,12,13,14} };
	// b++; 非法,根据以上的讨论,毫无疑问数组是不能++的
	cout << b[0] << "   " << b[1] << "   " << b[2] << "   " << b[3] << endl; // 虽然b[3]确实有个地址,但是没有意义
	cout << *b[0] << "   " << *b[1] << "   " << *b[2] << "   " << *b[3] << endl; // 0   5   10   -858993460
	cout << &b[0] << "   " << &b[1] << "   " << &b[2] << "   " << &b[3] << endl; // 把b[i]看成一个一维数组,数组名和数组取地址是相同的

	cout << &b[1] << "   " << b[1] << "   " << &b[1][0] << endl;//b[1] <=> &b[1][0] <=> &b[1]  ,可以参考普通一维数组,c和&c[0]和&c是等价的
	cout << b << "   " << &b << "   " << &b[0] << "   " << b[0] << "   " << &b[0][0] << endl;// 特别的如果是第一个行数组的地址，则它们也等于b，b是数组名，是一个地址，同时也等于对b取地址&b
	// 在二维数组的情况下b 和 &b相等，原因是本质上看成是第1个行数组的b和&b相同，和c与&c等价原因相同
	cout << *b << endl; // 因为b可看成存放3个地址的指针数组,对b解引用得到的是第一个地址,地址是第一个行指针的地址
	// 对b解引用其实就是*(&b)=b=&b[0]=b[0]=&b[0][0]
	// int** pb1 = b; 非法

	// <11>指向二维普通数组类型的int (*)[5]指针
	cout << "\n11--------->" << endl;
	// 指向了二维数组变量本身
	// 这个指针类型其实应当和 [ <4>指向一维指针数组的int **指针 或者 指向二维指针数组的int *(**)[n]指针 ]相对应，指向的是二维数组变量变量本身而不是地址
	int(*pb1)[5] = b; // 常说的数组指针,总与 [ <3>指针数组 int *[] ] 进行比较,其实区别很大
	pb1++; // 可以访问二维数组的元素
	cout << pb1 << "   " << b[1] << "   " << &b[1] << "   " << &b[1][0] << endl; // 指针移动到第2个行指针的地址

	// <12>指向二维普通数组类型的int (*)[3][5]指针
	cout << "\n12--------->" << endl;
	// 指向了二维数组变量本身的地址
	int(*pb4)[3][5] = &b; // b是二维数组

	cout << "p4++ before..." << endl;
	// pb4是二维数组b的地址类型,而数组名和数组名的地址是相同的,b=&b
	// 再根据<10二维数组>的内容也等于,二维数组也等于首行数组的数组名b[0]、首行数组名地址&b[0]、首行数组首元素的地址&b[0][0]
	cout << pb4 << "   " << &b << "   " << b << "   " << b[0] << "   " << &b[0] << "   " << &b[0][0] << endl; 
	
	int (*k11)[5] = *pb4; // 从这里可以看出*pb4 是(*)[5]类型,也就是指向一维普通数组的地址
	int(*k12)[5] = b; // b是二维数组,可以看成是存储多个一维普通数组地址的数组,所以也可以指向b,相当于指向b[0]的地址&b[0],但不是b[0]
	int(*k13)[5] = &b[0]; // 不是b[0]，b[0]是一个一维数组变量本身,指向b[0]的类型是int *类型，参考<2>指向一维普通数组的int*指针
	cout << "k11---k12---k13..." << endl;
	cout << k11 << "   " << k12 << "   " << k13 << endl; // k11、k12、k13以及pb4、*pb4、**pb4都是相同的
	cout << *pb4 << "   " <<&b[0]<< endl; // 从以上可以看出 *pb4是和&b[0]或者b等价的,但非首行时使用&b[i]更准确

	int *k21 = **pb4; // 可以看出**pb4本质上是1个一维普通数组本身,所以可以用int*指向这个数组变量
	cout << **pb4 << "   " <<b[0]<< endl; // *pb4对标&b[0],所以pb4对标b[0]也是顺理成章的
	
	int k31 = ***pb4; // 毫无疑问是1个数
	cout << ***pb4 << "   " << *b[0] <<"   "<<b[0] [0] <<endl;// b[0]是一位普通数组,b[0]虽然不能++,但是解引用还是可以的,也就是b[0]的首元素b[0] [0]
	

	pb4++; // 根据pb4对标&b的情况，相当于移动到b到新的b类型的地址
	cout << "p4++ finshed..." << endl;
	int(*k41)[5] = *pb4; 
	int(*k42)[5] = &b[1]; // k42不同说明 pb4++并不是移动到b的第2个行指针,不然应该全部和&b[1]的结果一样
	cout << k41 << "   " << k42 << endl; // 只有k41和pb4、pb4、*pb4、**pb4相同
	cout << pb4 << "   " << *pb4 << "   " << **pb4 << "   " << "    " << ***pb4 << endl;
	system("pause");
}