#include<iostream>

using namespace std;
template <class T>
struct CircLinkNode {
	T data;                        //�������
	CircLinkNode<T> *link;               //����ָ��
	CircLinkNode(CircLinkNode<T> *next = NULL) :link(next){}
	CircLinkNode(T d, CircLinkNode<T> *next = NULL) :data(d),link(next){}
};

template <class T>
class CircList {
public:
	CircList();      //���캯��
	CircList(CircList<T>& L);    //���ƹ��캯��
	~CircList();                //��������
	void makeEmpty();
	int Length()const;
	CircLinkNode<T> *getHead()const { return first; }
	CircLinkNode<T> *Search(T x);
	CircLinkNode<T> *Locate(int i);
	bool getData(int i);            //ȡ��i�����ֵ
	void setData(int i,T& x);          //�޸ĵ�i�����ֵΪx
	void Firster() { current = first; }
	void Insert(int i, T& x);        //�ڵ�ǰλ�ò���
	bool Remove(int i, T& x);                 //ɾ����ǰ���
	bool IsEmpty()
	{
		return first->link == first ? true : false;
	}


protected:
	CircLinkNode<T> *first, *current;         //����ͷָ��,��ǰλ��ָ��
};

template<class T>							//���캯��
CircList<T>::CircList() {
	first = new CircLinkNode<T>;
	current = first;
}


template<class T>
CircList<T>::CircList(CircList<T>& L) {      //���ƹ��캯��
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
void CircList<T>::makeEmpty() {          //��������Ϊ�ձ�
	CircLinkNode<T> *q;
	while (current->link != first) {
		q = current->link;
		current->link = q->link;
		delete q;
	}
};

template<class T>
int CircList<T>::Length()const {            //���������ͷ���ĵ�������
	CircLinkNode<T> *p = current->link; int count = 0;
	while (p != first) {
		p = p->link; count++;
	}
	return count;
};


template<class T>
CircLinkNode<T> *CircList<T>::Search(T x) {          //�ڱ���������������x�Ľ��
	while (current != first && current->data != x)
		current = current->link;
		return current;
};


template<class T>
CircLinkNode<T> *CircList<T>::Locate(int i) {        //��λ���������ر��е�i��Ԫ�صĵ�ַ����i<0��i�������н��������򷵻�NULL��
	if (i < 0)
		return NULL;
	int k = 0;
	while (current->link != first && k < i) {
		current = current->link; k++;
	}
	return current;
};


template<class T>
bool CircList<T>::getData(int i) {         //ȡ�������е�i��Ԫ�ص�ֵ
	if (i <= 0) 
		return NULL;
	Locate(i);
	if (current == first) return false;
	else { x = current->data; return true; }
};

template<class T>
void CircList<T>::setData(int i, T& x) {      //���ĵ�i��Ԫ�ص�ֵ
	if (i <= 0)return;
	Locate(i);
	if (current == first)return;
	else current->data = x;
};



template<class T>
void CircList<T>::Insert(int i, T& x) {             //����Ԫ��X�����������е�i�����֮��    
	Locate(i);
	CircLinkNode<T> *newNode = new CircLinkNode<T>(x);
	if (newNode == first) {
		cerr << "�洢�������" << endl; 
		exit(1);
	}
	newNode->link = current->link;    //����current֮��
	current->link = newNode;
};

template<class T>
bool CircList<T>::Remove(int i, T& x) {             //�������еĵ�i��Ԫ��ɾȥ��ͨ�������Ͳ���x���ظ�Ԫ�ص�ֵ
	Locate(i - 1);
	if (current->link == first)
		return false;
	CircLinkNode<T> *del = current->link;
	current->link = del->link;
	x = del->data; delete del;
	return true;
};




