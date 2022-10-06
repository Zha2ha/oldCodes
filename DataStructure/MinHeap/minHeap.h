#ifndef MINHEAP_H
#define MINHEAP_H

#include "minHeap.h"
#include <iostream>
#include <cassert>
using namespace std;
const int DEFAULT_SIZE = 10;

template<class E>
class MinHeap
{
public:
    MinHeap(int sz = DEFAULT_SIZE);
    MinHeap(E arr[], int n);
    ~MinHeap() {delete []heap;}
    bool Insert(const E &x);
    bool RemoveMin(E &x);
    bool IsEmpty()const
    {
        return (currentSize == 0)? true : false;
    }
    bool IsFull()const
    {
        return (currentSize == maxSize) ? true : false;
    }
    void makeEmpty() {currentSize = 0;}
private:
    E *heap;
    int currentSize;
    int maxSize;
    void siftDown(int start, int end);
    void siftUp(int start);
};

template<class E>
MinHeap<E>::MinHeap(int sz)
{
    maxSize = (sz > DEFAULT_SIZE) ? sz : DEFAULT_SIZE;
    heap = new E[maxSize];
    assert(heap != NULL);
    currentSize = 0;
}

template<class E>
MinHeap<E>::MinHeap(E arr[], int n)
{
    maxSize = (n > DEFAULT_SIZE) ? n: DEFAULT_SIZE;
    heap = new E[maxSize];
    assert(heap != NULL);
    for (int i = 0; i < n; ++i)
    {
        heap[i] = arr[i];
    }
    currentSize = n;
    int curPos = currentSize / 2 - 1;
    while (curPos >= 0)
    {
        siftDown(curPos, currentSize - 1);
        --curPos;
    }
}

template<class E>
void MinHeap<E>::siftDown(const int start, const int end)
{
    int i = start, j = 2 * i + 1;
    E temp = heap[i];
    while (j <= end)
    {
        if (j < end && heap[j + 1] < heap[j])
            ++j;
        if (heap[j] < temp)//假设 < 已经在E中定义
        {
            heap[i] = heap[j];
            i = j;
            j = 2 * i + 1;
        }
        else
        {
            break;
        }
        
    }
    heap[i] = temp;
}

template<class E>
bool MinHeap<E>::Insert(const E &x)
{
    if (currentSize == maxSize)
    {
        cout << "HEAP IS FULL!";
        return false;
    }
    heap[currentSize] = x;
    siftUp(currentSize);
    ++currentSize;
    return true;
}

template<class E>
void MinHeap<E>::siftUp(int start)
{
    int j = start, i = (j - 1) / 2;
    E temp = heap[j];
    while (j > 0)
    {
        if (temp < heap[i])
        {
            heap[j] = heap[i];
            j = i;
            i = (j - 1) / 2;
        }
        else
            break;
    }
    heap[j] = temp;
}

template<class E>
bool MinHeap<E>::RemoveMin(E &x)
{
    if (!currentSize)
    {
        cout << "HEAP IS EMPTY";
        return false;
    }
    x = heap[0];
    heap[0] = heap[currentSize - 1];
    --currentSize;
    siftDown(0, currentSize - 1);
    return true;
}
#endif