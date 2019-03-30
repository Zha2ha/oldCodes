#pragma once
#ifndef SEQSTACK_H
#define SEQSTACK_H


#include<assert.h>
#include<iostream>
const int INC_SIZE = 20;
template<class T>
class SeqStack {
private:
	T *elements;//ջԪ������
	int top;//ջ��ָ��
	int maxSize;//ջ�������
	void OverflowProcess();//�Զ��������
public:
	SeqStack(int sz = 50);//���캯��
	SeqStack(SeqStack<T> &s);//���ƹ��캯��
	~SeqStack() { delete[]elements; }//��������
	void Push(T& x);//��ջ
	T Pop();//��ջ
	T& Top();//ȡջ��Ԫ��
	int getSize() { return top + 1; }//ȡԪ������
	bool IsEmpty()const { return (top == -1) ? true : false; }
	void MakeEmpty() { top = -1; }//���ջ
	SeqStack<T>& operator=(SeqStack<T> &s);
};

template<class T>
SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz) {
	elements = new T[maxSize];
	assert(elements != NULL);//C++���ԣ����ڴ����ʧ������ֹ����
}

template<class T>
SeqStack<T>::SeqStack(SeqStack<T> &s) {//���ƹ��캯��
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
SeqStack<T>& SeqStack<T>::operator=(SeqStack<T> &s)//��ֵ���캯��
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
	//˽�г�Ա������ջ��ʱ����
	T *newArray = new T[maxSize + INC_SIZE];
	assert(newArray != NULL);
	for (int i = 0; i <= top; i++)
		newArray[i] = elements[i];
	maxSize += INC_SIZE;
	delete[] elements;
	elements = newArray;
}

template<class T>
void SeqStack<T>::Push(T &item)//��ջ
{//��ջ�����Զ�����
	if (top == maxSize - 1)
		OverflowProcess();
	elements[++top] = item;//����top������ջ
}

template<class T>
T SeqStack<T>::Pop(){//��ջ
	T ret;//���ɵ�����ֵ
	//������Ӧ��ȷ�ĵ��ã�
	if (top >= 0)
		ret = elements[top--];//�˳�ջ��Ԫ��
	else throw"Stack is empty!";
	return ret;
}

template<class T>
T &SeqStack<T>::Top() {//ȡջ��Ԫ��
	//������Ӧ��ȷ�ĵ���
	T x;
	if (top >= 0)
		return x = elements[top];
	else {
		throw"Stack is empty!";//�׳��쳣
		T ru;//���ɵ�����ֵ
		return ru;//�����޷���ֵ
	}
}
#endif // !SEQSTACK_H