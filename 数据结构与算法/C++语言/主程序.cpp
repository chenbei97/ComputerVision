#include "charter2.h"
#include "sort_method.h"
#include <iostream>
using namespace std;
int main()
{
	//_charter2_test_and_debug();
	//_charter2_spatial_complexity();
	//_charter2_time_complexity();

	const int n = 10;
	int a[n] = { 6,5,8,4,3,1,13,0,66 ,-2};
	//array_sorting_method(a, n ,countSort);
	array_sorting_method(a, n, selectSort);
	return 0;
}