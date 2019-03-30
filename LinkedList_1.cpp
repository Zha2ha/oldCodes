#include<iostream>
using namespace std;
struct LNode
{
	int data;
	LNode *next;
};
typedef LNode *LinkList;
LinkList create();
LinkList create1();
void print(LinkList L);
void DestroyList(LinkList &L);
int main()
{
	LinkList L;
	cout << "input numbers and end with -1" << endl;
	L = create();
	cout << "the result is (using function create())" << endl;
	print(L);
	DestroyList(L);
	cout << "input numbers and end with -1" << endl;
	L = create1();
	cout << "the result is (using function create1())" << endl;
	print(L);
	DestroyList(L);
	return 0;
}

LinkList create()
{
	LinkList p1,p2,head;
	head = NULL;
	p1 = new LNode;
	p2 = p1;
	cin >> p1->data;
	while (p1->data != -1)
	{
		if (head == NULL)
			head = p1;
		else
			p2->next = p1;
		p2 = p1;
		p1 = new LNode;
		cin >> p1->data;
	}
	p2->next = NULL;
	delete p1;
	return head;
}

LinkList create1()
{
	LinkList p, head;
	head = NULL;
	p = new LNode;
	cin >> p->data;
	while (p->data != -1)
	{
		p->next = head;
		head = p;
		p = new LNode;
		cin >> p->data;
	}
	delete p;
	return head;
}

void print(LinkList L)
{
	LinkList p;
	p = L;
	if (p == NULL)
		cout << "Null list" << endl;
	else
	{
		while (p->next!=NULL)
		{
			cout << p->data << "->";
			p = p->next;
		}
		cout << p->data << endl;
	}
}

void DestroyList(LinkList &L)
{
	LinkList p = L;
	while (p!=NULL)
	{
		L = L->next;
		delete p;
		p = L;
	}
}
