// vector_swap.cpp
// compile with: /EHsc
#include<iostream>
#include <vector>


int main()
{
	using namespace std;
	vector <int> v1, v2;

	v1.push_back(1);
	v1.push_back(2);
	v1.push_back(3);

	v2.push_back(10);
	v2.push_back(20);

	cout << "The number of elements in v1 = " << v1.size() << endl;
	cout << "The number of elements in v2 = " << v2.size() << endl;
	cout << endl;

	v1.swap(v2);

	cout << "The number of elements in v1 = " << v1.size() << endl;
	cout << "The number of elements in v2 = " << v2.size() << endl;

	swap(v1, v2);
	cout << "The number of elements in v1 = " << v1.size() << endl;
	cout << "The number of elements in v2 = " << v2.size() << endl;
}