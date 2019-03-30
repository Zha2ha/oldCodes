#include<iostream>
#include"MyClass.h"
using namespace std;
int main()
{
	MyClass obj1(1, 3), obj2(5, 8), a;
	obj1.Print();
	obj2.Print();
	a.Print();
	return 0;
}
