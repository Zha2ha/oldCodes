#include <iostream>
#include "stack.cpp"

using namespace std;
int main()
{
	Stack<int> s1;
	s1.Push(3);
	for (int i = 0; i < 10; ++i)
	{
		s1.Push(i);
	}
	s1.Push(45);
	cout << s1.getSize() << endl;
	cout << s1.getTop() << endl;
	cout << s1.Pop() << endl;
	cout << s1.getSize() << endl;
	cout << s1.getTop() << endl;

	Stack<int> s2(s1);
	cout << s2.getSize() << endl;
	cout << s2.getTop() << endl;
	cout << s2.Pop() << endl;
	cout << s2.getSize() << endl;
	Stack<int> s3 = s2;
	cout << s3.getSize() << endl;
	cout << s3.getTop() << endl;
	cout << s3.Pop() << endl;
	cout << s3.getSize() << endl;
	return 0;
}