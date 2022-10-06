#include <iostream>
#include "minHeap.h"

using namespace std;
int main()
{
    int x;
    int a[] = {12, 23, 34, 33, 22, 56, 9, 78};
    MinHeap<int> h(a, 8);
    h.Insert(6);
    h.RemoveMin(x);
    cout << x << endl;
    return 0;
}