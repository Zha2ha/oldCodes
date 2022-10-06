#include <iostream>
using namespace std;

/*******************************************************************************
*[name]    LinkNode（Struct）
*[members]    T data, LinkNode<T> *link
*[description]	链表节点结构体
*******************************************************************************/
template <typename T>
struct LinkNode
{
    T data;
    LinkNode<T> *link;
    LinkNode(LinkNode<T> *ptr = nullptr)
    {
        link = ptr;
    }
    LinkNode(const T &item, LinkNode<T> *ptr = nullptr)
    {
        data = item;
        link = ptr;
    }
};

/*******************************************************************************
*[name]    List
*[members]    LinkNode<T> *first, last
*[description]	附加头节点的链表类，first指针指向的节点没有内容，如果使用自定义的数据
类型，要保证该数据类型有<<, >>, <, >, + 和 = 的运算符重载
*******************************************************************************/
template <typename T>
class List
{
private:
	LinkNode<T>* first;
	LinkNode<T>* last;
public:
    List()
    {
        first = new LinkNode<T>;
		last = first;
    }
    List(const T &x)
    {
        last = first = new LinkNode<T>(x);
    }
    //copy constructor
    List(List<T> &L);
    //deconstructor
	~List() { makeEmpty(); delete first; }
    void makeEmpty();
    int length() const;
    LinkNode<T> *getHead() const
    {
        return first;
    }
    LinkNode<T> *Search(T x);
    LinkNode<T> *Locate(int i);
    bool getData(int i, T &x) const;
	bool setData(int i, T &x);
    bool Insert(int i, T x);
    bool Remove(int i, T &x);
    bool IsEmpty() const
    {
        return first->link == nullptr ? true : false;
    }
	void CreateListF(T endTag);
	void CreateListR(T endTag);
    // void Sort();
    void input();
    void output();
    List<T> &operator=(List<T> &L);
};

//copy constructor
template<typename T>
inline List<T>::List(List<T> &L)
{
	T value;
	LinkNode<T>* srcptr = L.getHead();
	LinkNode<T>* destptr = first = new LinkNode<T>;
	while (srcptr->link != nullptr)
	{
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = nullptr;
	last = destptr;
}

/*make the list empty*/
template<typename T>
inline void List<T>::makeEmpty()
{
	LinkNode<T>* q;
	while (first->link != nullptr)
	{
		q = first->link;
		first->link = q->link;
		delete q;
	}
	last = first;
}

/*return the list's length*/
template<typename T>
inline int List<T>::length() const
{
	LinkNode<T>* p = first->link;
	int count = 0;
	while (p != nullptr)
	{
		p = p->link;
		++count;
	}
	return count;
}

/*search the node that contains data x, return the address of the node, else return NULL*/
template<typename T>
inline LinkNode<T>* List<T>::Search(T x)
{
	LinkNode<T>* current = first->link;
	while (current != nullptr)
	{
		if (current->data == x)
			break;
		else
			current = current->link;
	}
	return current;
}

/*return the address of the number i member, else return NULL*/
template<typename T>
inline LinkNode<T>* List<T>::Locate(int i)
{
	if (i < 0)
		return NULL;
	LinkNode<T>* current = first->link;
	int k = 0;
	while (current != nullptr && k < i)
	{
		current = current->link;
		++k;
	}
	return current;
}

/**/
template<typename T>
inline bool List<T>::getData(int i, T& x) const
{
	LinkNode<T>* p = Locate(i);
	if (p == nullptr)
		return false;
	else
	{
		x = p->data;
		return true;
	}
}

template<typename T>
inline bool List<T>::setData(int i, T& x)
{
	LinkNode<T>* p = Locate(i);
	if (p == nullptr)
		return false;
	else
	{
		p->data = x;
		return true;
	}
}

template<typename T>
inline bool List<T>::Insert(int i, T x)
{
	LinkNode<T>* p = Locate(i - 1);
	if (p == nullptr)
		return false;
	LinkNode<T>* newNoed = new LinkNode<T>(x);
	if (newNoed == nullptr)
	{
		cerr << "memory allocate error!(in function Insert)";
		exit(1);
	}
	if (p->link == nullptr)
		last = newNoed;
	p->link = newNoed;
	return true;
}

template<typename T>
inline bool List<T>::Remove(int i, T& x)
{
	LinkNode<T>* p = Locate(i - 1);
	if (p == 0 || p->link == nullptr)
		return false;
	LinkNode<T>* q = p->link;
	p->link = q->link;
	x = q->data;
	if (q == last)
		last = p;
	delete q;
	return true;
}

/*******************************************************************************
*[name]    CreateListF
*[description]    前插法建立单链表
*[parmaters]	T endTag(结束标志)
*[return]	void
*******************************************************************************/
template<typename T>
inline void List<T>::CreateListF(T endTag)
{
	T val;
	LinkNode<T>* s;
	makeEmpty();
	cin >> val;
	while (val != endTag)
	{
		s = new LinkNode<T>(val);
		if (!s)
		{
			cerr << "memory allocate error!(in CreateListF)";
			exit(1);
		}
		if (first->link == nullptr)
			last = s;
		s->link = first->link;
		first->link = s;
		cin >> val;
	}
}

/***********************************************
*[name]    CreateListR
*[description]    后插法建立单链表
*[parmaters]	T endTag
*[return]	void
************************************************/
template<typename T>
inline void List<T>::CreateListR(T endTag)
{
	makeEmpty();
	T val;
	LinkNode<T>* s, * r = first;
	cin >> val;//如果不是基本数据类型，要确保该数据类型有相应的 >> 重载
	while (val != endTag)
	{
		s = new LinkNode<T>(val);
		if (!s)
		{
			cerr << "memory allocate error!(in CreateListR)";
			exit(1);
		}
		r->link = s;
		r = s;
		cin >> val;
	}
	r->link = nullptr;
	last = r;
}

// template<typename T>
// inline void List<T>::Sort()
// {
// }

template<typename T>
inline void List<T>::input()
{
	T endTag;
	cout << "choose a end tag:";
	cin >> endTag;
	cout << "input objects:" << endl;
	CreateListR(endTag);
	
}

template<typename T>
inline void List<T>::output()
{
	LinkNode<T>* p = first->link;
	while (p != nullptr)
	{
		cout << p->data << "  ";
		p = p->link;
	}
	cout << endl;
}

template<typename T>
inline List<T>& List<T>::operator=(List<T>& L)
{
	makeEmpty();
	LinkNode<T>* destptr = first;
	LinkNode<T>* srcptr = L.getHead();
	while (srcptr->link != nullptr)
	{
		destptr->link = new LinkNode<T>(srcptr->link->data);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = nullptr;
	last = destptr;
	return *this;
}
