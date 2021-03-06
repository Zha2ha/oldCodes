// circularlist.cpp: 定义控制台应用程序的入口点。
#include<iostream>
#include"CircList.h"
template <class T>
void Josephus(CircList<T>& Js,int n, int m) {
	CircLinkNode<T> *p = Js.Locate(1);
	CircLinkNode<T> *pre = NULL;
	int i, j;
	for (i = 0; i < n - 1; i++) {
		for (j = 1; j < m; j++) {
			{pre = p; p = p->link; }
		}
		cout << "出列的人数是" << p->data << endl;
		pre->link = p->link; delete p;
		p = pre->link;
	}
};

void main() {
	CircList<int> clist;
	int i, n, m;
	cout << "输入游戏者人数和报数间隔：";
	cin >> n >> m;
	int t[100];
	for (i = 0; i <= n-1; i++) {
		cout << "输入第" << i + 1 << "个人的数据：";
		cin >> t[i];
		clist.Insert(i, t[i]);
	}
	Josephus(clist,n,m);
};
