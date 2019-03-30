#include<conio.h>  //控制台io头文件  
#include"Polynomal.h"
#include<iostream>
using namespace std;
int main()
{
	Polynomial A;
	cin >> A;
	cout << A;
	Polynomial B;
	cin >> B;
	cout << B;
	cout << A + B;
	cout << A*B;
}