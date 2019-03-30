#pragma once
#ifndef SEQSTACK_H
#define SEQSTACK_H


#include<assert.h>
#include<iostream>
const int INC_SIZE = 20;
template<class T>
class SeqStack {
private:
	T *elements;//栈元素数组
	int top;//栈顶指针
	int maxSize;//栈最大容量
	void OverflowProcess();//自动溢出处理
public:
	SeqStack(int sz = 50);//构造函数
	SeqStack(SeqStack<T> &s);//复制构造函数
	~SeqStack() { delete[]elements; }//析构函数
	void Push(T& x);//进栈
	T Pop();//出栈
	T& Top();//取栈顶元素
	int getSize() { return top + 1; }//取元素数量
	bool IsEmpty()const { return (top == -1) ? true : false; }
	void MakeEmpty() { top = -1; }//清空栈
	SeqStack<T>& operator=(SeqStack<T> &s);
};

template<class T>
SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz) {
	elements = new T[maxSize];
	assert(elements != NULL);//C++断言，若内存分配失败则终止运行
}

template<class T>
SeqStack<T>::SeqStack(SeqStack<T> &s) {//复制构造函数
	maxSize = s.maxSize;
	top = s.getSize() - 1;
	elements = new T[maxSize];
	assert(elements != NULL);
	T *p1=s.elements;
	T *p2=elements;
	while (p1 != s.top) {
		*p2 = *p1;
		p1++;
		p2++;
	}
	top = p2;
}

template<class T>
SeqStack<T>& SeqStack<T>::operator=(SeqStack<T> &s)//赋值构造函数
{
	delete[] elements;
	elements = new T[s.maxSize];
	assert(elements != NULL);
	top = elements;
	maxSize = s.maxSize;
	T *p1 = s.elements;
	T *p2 = elements;
	while (p1 != s.top) {
		*p2 = *p1;
		p1++;
		p2++;
	}
	top = p2;
	return *this;
}

template<class T>
void SeqStack<T>::OverflowProcess() {
	//私有成员函数，栈满时扩容
	T *newArray = new T[maxSize + INC_SIZE];
	assert(newArray != NULL);
	for (int i = 0; i <= top; i++)
		newArray[i] = elements[i];
	maxSize += INC_SIZE;
	delete[] elements;
	elements = newArray;
}

template<class T>
void SeqStack<T>::Push(T &item)//入栈
{//若栈满则自动扩容
	if (top == maxSize - 1)
		OverflowProcess();
	elements[++top] = item;//递增top，再入栈
}

template<class T>
T SeqStack<T>::Pop(){//出栈
	T ret;//自由的垃圾值
	//优先响应正确的调用：
	if (top >= 0)
		ret = elements[top--];//退出栈顶元素
	else throw"Stack is empty!";
	return ret;
}

template<class T>
T &SeqStack<T>::Top() {//取栈顶元素
	//优先响应正确的调用
	T x;
	if (top >= 0)
		return x = elements[top];
	else {
		throw"Stack is empty!";//抛出异常
		T ru;//自由的垃圾值
		return ru;//避免无返回值
	}
}
#endif // !SEQSTACK_H