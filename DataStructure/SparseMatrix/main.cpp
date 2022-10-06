#include "SparseMatrix.h"
#include <iostream>
using namespace std;

int main()
{
	Trituple<int> t1 = { 0, 3, 22 };
	Trituple<int> t2 = { 0, 6, 15 };
	Trituple<int> t3 = { 1, 1, 11 };
	Trituple<int> t4 = { 1, 5, 17 };
	Trituple<int> t5 = { 2, 3, -6 };
	Trituple<int> t6 = { 3, 5, 39 };
	Trituple<int> t7 = { 4, 0, 91 };
	Trituple<int> t8 = { 5, 2, 28 };
	Trituple<int> t[8] = { t1, t2, t3, t4, t5, t6, t7, t8 };

	return 0;
}