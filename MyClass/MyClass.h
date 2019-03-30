#pragma once
#ifndef MYCLASS
#define MYCLASS

#include<iostream>
using namespace std;
class MyClass
{
public:
	MyClass(int a = 1, int b = 2);
	void Print();
private:
	int x, y;
};
#endif // !MYCLASS
