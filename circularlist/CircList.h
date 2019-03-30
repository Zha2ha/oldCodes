#include<iostream>

using namespace std;
template <class T>
struct CircLinkNode {
	T data;                        //结点数据
	CircLinkNode<T> *link;               //链接指针
	CircLinkNode(CircLinkNode<T> *next = NULL) :link(next){}
	CircLinkNode(T d, CircLinkNode<T> *next = NULL) :data(d),link(next){}
};

template <class T>
class CircList {
public:
	CircList();      //构造函数
	CircList(CircList<T>& L);    //复制构造函数
	~CircList();                //析构函数
	void makeEmpty();
	int Length()const;
	CircLinkNode<T> *getHead()const { return first; }
	CircLinkNode<T> *Search(T x);
	CircLinkNode<T> *Locate(int i);
	bool getData(int i);            //取第i个结点值
	void setData(int i,T& x);          //修改第i个结点值为x
	void Firster() { current = first; }
	void Insert(int i, T& x);        //在当前位置插入
	bool Remove(int i, T& x);                 //删除当前结点
	bool IsEmpty()
	{
		return first->link == first ? true : false;
	}


protected:
	CircLinkNode<T> *first, *current;         //链表头指针,当前位置指针
};

template<class T>							//构造函数
CircList<T>::CircList() {
	first = new CircLinkNode<T>;
	current = first;
}


template<class T>
CircList<T>::CircList(CircList<T>& L) {      //复制构造函数
	T value;
	CircLinkNode<T> *srcptr = L.getHead();
	CircLinkNode<T> *destptr = first = new CircLinkNode<T>;
	while (srcptr->link != NULL) {
		value = srcptr->link->data;
		destptr->link = new CircLinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
};

template<class T>
CircList<T>::~CircList() {
	makeEmpty();
};

template<class T>
void CircList<T>::makeEmpty() {          //将链表置为空表
	CircLinkNode<T> *q;
	while (current->link != first) {
		q = current->link;
		current->link = q->link;
		delete q;
	}
};

template<class T>
int CircList<T>::Length()const {            //计算带附加头结点的单链表长度
	CircLinkNode<T> *p = current->link; int count = 0;
	while (p != first) {
		p = p->link; count++;
	}
	return count;
};


template<class T>
CircLinkNode<T> *CircList<T>::Search(T x) {          //在表中搜索含有数据x的结点
	while (current != first && current->data != x)
		current = current->link;
		return current;
};


template<class T>
CircLinkNode<T> *CircList<T>::Locate(int i) {        //定位函数。返回表中第i个元素的地址。若i<0或i超出表中结点个数，则返回NULL。
	if (i < 0)
		return NULL;
	int k = 0;
	while (current->link != first && k < i) {
		current = current->link; k++;
	}
	return current;
};


template<class T>
bool CircList<T>::getData(int i) {         //取出链表中第i个元素的值
	if (i <= 0) 
		return NULL;
	Locate(i);
	if (current == first) return false;
	else { x = current->data; return true; }
};

template<class T>
void CircList<T>::setData(int i, T& x) {      //更改第i个元素的值
	if (i <= 0)return;
	Locate(i);
	if (current == first)return;
	else current->data = x;
};



template<class T>
void CircList<T>::Insert(int i, T& x) {             //将新元素X插入在链表中第i个结点之后    
	Locate(i);
	CircLinkNode<T> *newNode = new CircLinkNode<T>(x);
	if (newNode == first) {
		cerr << "存储分配错误！" << endl; 
		exit(1);
	}
	newNode->link = current->link;    //插在current之后
	current->link = newNode;
};

template<class T>
bool CircList<T>::Remove(int i, T& x) {             //将链表中的第i个元素删去，通过引用型参数x返回该元素的值
	Locate(i - 1);
	if (current->link == first)
		return false;
	CircLinkNode<T> *del = current->link;
	current->link = del->link;
	x = del->data; delete del;
	return true;
};




