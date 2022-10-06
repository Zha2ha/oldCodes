#pragma once//链式队列实现，使用LinkNode结构做结点
#include <iostream>
using namespace std;

template <typename T>
struct LinkNode
{
	T data;
	LinkNode<T>* link;
	LinkNode(LinkNode<T>* ptr = nullptr)
	{
		link = ptr;
	}
	LinkNode(const T& item, LinkNode<T>* ptr = nullptr)
	{
		data = item;
		link = ptr;
	}
};

template <typename T>
class LinkQueue
{
public:
	LinkQueue():front(0), rear(0){}
	~LinkQueue() { MakeEmpty(); }
	bool EnQueue(const T& x);
	bool DeQueue(T& x);
	bool GetFront(T& x);
	void MakeEmpty();
	bool IsEmpty()const
	{
		return front == 0 ? true : false;
	}
	int GetSize();
	friend ostream& operator<<(ostream& os, LinkQueue<T>& q)
	{
		os << "队列中元素数量为：" << q.GetSize() << endl;
		LinkNode<T>* p = q.front;
		int i = 0;
		while (p)
		{
			os << ++i << ":" << p->data << endl;
			p = p->link;
		}
		return os;
	}
private:
	LinkNode<T>* front, * rear;//队头队尾指针
};

template<typename T>
inline bool LinkQueue<T>::EnQueue(const T& x)
{
	if (front == NULL)
	{
		front = rear = new LinkNode<T>(x);
		if (!front)
			return false;
	}
	else
	{
		rear->link = new LinkNode<T>(x);
		if (!rear->link)
			return false;
		rear = rear->link;
	}
	return true;
}

template<typename T>
inline bool LinkQueue<T>::DeQueue(T& x)
{
	if (IsEmpty())
		return false;
	LinkNode<T>* p = front;
	x = front->data;
	front = front->link;
	delete p;
	return true;
}

template<typename T>
inline bool LinkQueue<T>::GetFront(T& x)
{
	if (IsEmpty())
		return false;
	x = front->data;
	return true;
}

template<typename T>
inline void LinkQueue<T>::MakeEmpty()
{
	LinkNode<T>* p;
	while (front != NULL)
	{
		p = front;
		front = front->link;
		delete p;
	}
	rear = 0;
}

template<typename T>
inline int LinkQueue<T>::GetSize()
{
	LinkNode<T>* p = front;
	int count = 0;
	while (p)
	{
		p = p->link;
		++count;
	}
	return count;
}
