#pragma once
#include <assert.h>
#include <iostream>
using namespace std;

const int INC_SIZE = 20;
template<typename T>
class SeqQueue//��ѭ��������ɵ�ѭ������
{
public:
	SeqQueue(int sz = 50)
	{
		maxSize = sz;
		front = 0;
		rear = 0;
		elem = new T[maxSize];
		assert(elem != NULL);
	}
	//û�и��ƹ��캯���͸�ֵ���غ���
	~SeqQueue()
	{
		delete[]elem;

	}

	void EnQueue(const T& item);
	bool DeQueue(T& x);
	bool GetFront(T& x);
	void MakeEmpty()
	{
		front = rear = 0;
	}
	int IsEmpty()const
	{
		return (front == rear) ? true : false;
	}
	int GetSize()const
	{
		return (rear - front + maxSize) % maxSize;
	}
	friend ostream& operator<<(ostream& os, SeqQueue<T>& q)//�����ڶ�������õİ취���޷��������������ⶨ��
	{
		os << "front = " << q.front << ", rear = " << q.rear << endl;
		for (int i = q.front; i != q.rear; i = (i + 1) % q.maxSize)
		{
			os << i << ":" << q.elem[i] << endl;
		}
		return os;
	}


private:
	T* elem;
	int front, rear;
	int maxSize;
	void _OverflowProcess();
};

//template<typename T>
//ostream& operator<<(ostream& os, SeqQueue<T> q)//������������
//{
//	os << "front = " << q.front << ", rear = " << q.rear << endl;
//	for (int i = q.front; i != q.rear; i = (i + 1) % q.maxSize)
//	{
//		os << i << ":" << q.elem[i] << endl;
//	}
//	return os;
//}

template<typename T>
inline void SeqQueue<T>::EnQueue(const T& item)//��Ӻ���
{
	if ((rear + 1) % maxSize == front)
		_OverflowProcess();
	elem[rear] = item;
	rear = (rear + 1) % maxSize;
}

template<typename T>
inline bool SeqQueue<T>::DeQueue(T& x)//���Ӻ���
{
	if (IsEmpty())
		return false;
	x = elem[front];
	front = (front + 1) % maxSize;
	return true;
}

template<typename T>
inline bool SeqQueue<T>::GetFront(T& x)//ȡ����
{
	if (IsEmpty())
		return false;
	x = elem[front];
	return true;
}

template<typename T>
inline void SeqQueue<T>::_OverflowProcess()//�������ݺ���
{
	T* tmp = new T[maxSize + INC_SIZE];
	assert(tmp != NULL);
	int top = rear;
	rear = 0;
	for (int i = front; i != top; i = (i + 1)% maxSize, rear ++)
	{
		tmp[rear] = elem[i];
	}
	delete[]elem;
	elem = tmp;
	maxSize += INC_SIZE;
	front = 0;
}
