#include <iostream>
#include "List.h"
using namespace std;

int main()
{
    List<char> L;
    L.input();
    // L.output();
   // L.CreateListR(-1);
    L.output();
    List<char> L1(L);
    cout << "L1 is :";
    L1.output();
    return 0;
}