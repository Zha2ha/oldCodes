//基于数组的顺序栈的实现
#include <iostream>
#include <assert.h>

using namespace std;

const int stackIncreament = 5;
template<typename T>
class Stack
{
public:
	Stack(int sz = 10);
	Stack(Stack<T>& s);
	~Stack() { delete[]elements; }
	void Push(const T& x);
	T Pop();
	T& getTop();
	bool IsEmpty()const { return (top == -1) ? true : false; }
	bool IsFull()const { return (top == maxSize - 1) ? true : false; }
	int getSize()const { return top + 1; }
	void MakeEmpty() { top = -1; }
	Stack<T>& operator=(Stack<T>& s);
	
private:
	T* elements;
	int top;
	int maxSize;
	void overflowProcess();
};

template<typename T>
inline Stack<T>::Stack(int sz):top(-1), maxSize(sz)
{
	elements = new T[maxSize];//基于数组的栈结构
	assert(elements != nullptr);
}
template<typename T>
Stack<T>::Stack(Stack<T>& s):top(s.top), maxSize(s.maxSize)
{
	elements = new T[maxSize];
	assert(elements != nullptr);
	int i = 0;

	while (i <= top)
	{
		*(elements + i) = *(s.elements + i);
		++i;
	}
}
template<typename T>
inline void Stack<T>::Push(const T& x)
{
	if (IsFull() == true)
		overflowProcess();
	elements[++top] = x;
}

template<typename T>
inline T Stack<T>::Pop()
{
	T ret;
	if (top >= 0)
		ret = elements[top--];
	else
		throw "Stack is empty!";
	return ret;
}

template<typename T>
inline T& Stack<T>::getTop()
{
	if (top >= 0)
		return elements[top];
	else
	{
		throw "Stack is Empty!";
		T rubbish;
		return rubbish;
	}
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>& s)
{
	maxSize = s.maxSize;
	elements = new T[maxSize];
	assert(elements != nullptr);
	top = s.top;
	int i = 0;
	while (i <= top)
	{
		*(elements + i) = *(s.elements + i);
		++i;
	}
	return *this;
}

template<typename T>
inline void Stack<T>::overflowProcess()
{
	T* newArrary = new T[maxSize + stackIncreament];
	if (newArrary == nullptr)
	{
		cerr << "MEM Distribute error!" << endl;
		exit(1);
	}
	for (int i = 0; i <= top; ++i)
	{
		newArrary[i] = elements[i];
	}
	maxSize = maxSize + stackIncreament;
	delete[]elements;
	elements = newArrary;
}

//template<typename T>
//ostream& operator<<(ostream& os, Stack<T>& s)

