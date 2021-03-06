// demo1.cpp: 定义控制台应用程序的入口点。
#include<stdio.h>
#include<iostream>
template <class T>
class Link {
public:
	T data;
	Link<T> *next;

	Link(const T info, Link<T> *nextValue = NULL) {
		data = info;
		next = nextValue;
	}
	Link(const Link<T> * nextValue) {
		next = nextValue;
	}
};
template <class T>
class lnkList {
private:
	Link<T> *head, *tail;
	//Link<T> *setPos(const int p);
public:
	lnkList();                       //构造函数
	~lnkList();                      //析构函数
	bool isEmpty();                  //判断表是否是空
	void clear();                    //清空
	int length();                    //返回表长
	bool append(const T value);      //在表尾追加一个元素，表长自动加1
									 //bool insert(const int p, const T value);
									 //bool deletej(const int p);
									 //bool setPos(const int i);
	bool create(T n);                 //创建长度为n的链表
	void display();                   //显示链表的内容
									  //bool getValue(const int p,T &value);
									  //bool getPos(int &p,const T value);
	void Josephus(int m, int s);       //实现Josephus问题
};

template<class T>
bool lnkList<T>::isEmpty() {//判断是否是空
	if (head == NULL&&head->next == NULL)
		return true;
	else
		return false;
}

template<class T>
void lnkList<T>::clear() {//表清空
	head = tail = NULL;
}

template <class T>
bool lnkList<T>::create(T n)
{
	int i;
	for (i = 1; i <= n; i++)                         //赋初值
		append(i);
	tail->next = head;                         //指向头，形成循环链表
	return true;
}

template<class T>
void lnkList<T>::display() {              ////////////////显示链表里的内容
	int l = length();
	cout << "表里的元素有：";
	for (int i = 0; i < l; i++) {
		cout << head->data << "  ";
		head = head->next;
	}
	cout << endl;
}

template<class T>
int lnkList<T>::length() {//返回表长
	int i = 1;
	Link<T> *h;
	if (head == NULL)
		return i - 1;
	h = head->next;
	while (h != tail->next) {
		i++;
		h = h->next;
	}
	return i;
}

template<class T>
bool lnkList<T>::append(const T value)               //////////在表尾追加
{
	if (head == NULL) {
		head = new Link<T>(value, NULL);
		tail = head;
	}
	else
	{
		tail->next = new Link<T>(value, NULL);
		tail = tail->next;
	}
	return true;
}

template <class T>
lnkList<T>::lnkList() {
	head = tail = NULL;
}
template<class T>
lnkList<T>::~lnkList() {
	Link<T> *temp;
	while (head != NULL) {
		temp = head;
		head = head->next;
		delete temp;
	}
}
/**
template <class T>
Link<T> * lnkList<T>::setPos(int i){
int count=0;
if(i==0)
return 0;
Link<T> *p=new Link<T>(head->next);
while(p!=NULL&&count<i){
p=p->next;
count++;
}
return p;
}
/template<class T>
bool lnkList<T>::insert(const int i, const T value){
Link<T> *p, *q;
if ((p = setPos(i - 1)) == NULL){
cout << "非法插入点" << endl;
return false;
}
q = new Link<T>(value, p->nxet);
p - next = q;
if (p == tail)
tail = q;
return true;
}*/
template<class T>
void lnkList<T>::Josephus(int m, int s) {
	if (head != NULL) {
		for (int i = 0; i < m - 1; i++)
			head = head->next;
	}
	Link<T> *h = head, *p;
	while (!isEmpty()) {
		for (int i = 0; i < s - 1; i++) {
			p = h;
			h = h->next;
		}
		cout << "出列的人是：" << h->data << endl;
		p->next = h->next;
		delete h;
		h = p->next;
	}
	delete p;
}
using namespace std;
int main() {
	int n, m, s;
	cout << "请输入进行游戏的人数：" << endl;
	cin >> n;
	if (n <= 0)
		cout << "输入数据有错误！" << endl;
	lnkList<int>list;
	list.create(n);
	list.display();
	cout << "请输入要报的数字：" << endl;
	cin >> m;
	cout << "请输入从第几个人开始：" << endl;
	cin >> s;
	if (m>0 && s>0)
		list.Josephus(s, m);
	else
		cout << "输入数据有错误！" << endl;
	//system("pause");
	return 0;
}


