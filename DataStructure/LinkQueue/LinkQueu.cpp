#include <iostream>
#include "LinkQueue.h"
using namespace std;

int main()
{
	int x;
	LinkQueue<int> s;
	s.EnQueue(5);
	s.EnQueue(3);
	s.EnQueue(2);
	s.EnQueue(7);
	s.EnQueue(1);
	cout << s;
	s.GetFront(x);
	cout << x << endl;
	return 0;
}