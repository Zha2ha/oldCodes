#include <iostream>
#include "SeqQueue.h"
using namespace std;

int main()
{
	int x;
	SeqQueue<int> s(4);
	s.EnQueue(5);
	s.EnQueue(3);
	s.EnQueue(2);
	//s.EnQueue(7);
	//s.EnQueue(1);
	cout << s;
	s.GetFront(x);
	cout << x << endl;
	return 0;
}