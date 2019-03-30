#ifndef POLYNOMAL_H
#define POLYNOMAL_H
#include<iostream>
using namespace std;
struct Term {
	float coef;             //系数
	int exp;                //指数
	Term *link;
	Term(float c, int e, Term *next = NULL) {
		coef = c; exp = e; link = next;
	}
	Term *InsertAfter(float c, int e);
	friend ostream& operator<<(ostream&, const Term&);
};

class Polynomial {
public:
	Polynomial() { first = new Term(0, -1); }
	Polynomial(Polynomial& R);
	int maxOrder();
	Term *getHead()const { return first; }
private:
	Term *first;
	friend ostream& operator <<(ostream&, const Polynomial&);
	friend istream& operator >>(istream&, Polynomial&);
	friend Polynomial operator + (Polynomial&, Polynomial&);
	friend Polynomial operator * (Polynomial&, Polynomial&);
};

Term *Term::InsertAfter(float c, int e) {
	//在当前由this指针指示的项（即调用此函数的对象）后面插入一个新项。
	link = new Term(c, e, link);
	return link;
};

ostream& operator << (ostream& out, const Term& x) {
	//Term的友元函数：输出一个项x的内容到输出流out中。
	if (x.coef == 0.0)return out;
	out << x.coef;
	switch (x.exp)
	{
	case 0:break;
	case 1:out << "X"; break;
	default:out << "X^" << x.exp; break;
	}
	return out;
};

Polynomial::Polynomial(Polynomial& R) {
	//复制构造函数：用已有多项式对象R初始化当前多项式对象R
	first = new Term(0, -1);
	Term *destptr = first, *srcptr = R.getHead()->link;
	while (srcptr != NULL) {
		destptr->InsertAfter(srcptr->coef, srcptr->exp);
		//在destptr所指结点后插入新结点，再让destptr指到这个新结点
		srcptr = srcptr->link;
		destptr = destptr->link;
	}
};

int Polynomial::maxOrder() {
	//计算最大阶数，当多项式按升序排列时，最后一项中是指数最大者
	Term *current = first;
	while (current->link != NULL)current = current->link;
	//空表情形，current停留在first，否则current停留在表尾结点
	return current->exp;
};

istream& operator >> (istream& in, Polynomial& x) {
	//POlynomial类的友元函数：从输入流in输入各项，用尾插法建立一个多项式
	Term *rear = x.getHead(); int c,e;    //rear 是尾指针
	while (1) {
		cout << "Input a term(coef,exp):" << endl;
		in >> c >> e;                     //输入项的系数c和指数e
		if (e < 0)break;                  //用e<0控制输入结束
		rear = rear->InsertAfter(c, e);   //链接到rear所指结点后
	}
	return in;
};

ostream& operator<<(ostream& out, const Polynomial& x) {
	//Polynomial类的友元函数：输出带附加头节点的多项式链表x
	Term *current = x.getHead()->link;
	cout << "the polynomial is:" << endl;
	bool h = true;
	while (current != NULL) {
		if (h == false && current->coef > 0.0)
			out << "+";
		h = false;
		out << *current;                //调用 Term类的重载操作“<<”
		current = current->link;
	}
	out << endl;
	return out;
};

Polynomial operator+(Polynomial& A, Polynomial& B) {
	//友元函数：两个带附加头节点的按升幂排序的多项式链表的头指针分别是A.first和B.first,返回的是结果多项式链表
	Term *pa, *pb, *pc, *p; float temp;
	Polynomial C; pc = C.first;   //pc为多项式R在创建过程中的尾指针
	pa = A.getHead()->link; pb = B.getHead()->link;  //pa与pb定位于A与B的第一个结点，是两链的检测指针
	while (pa != NULL&&pb != NULL) {
		if (pa->exp == pb->exp) {
			temp = pa->coef + pb->coef;
			if (fabs(temp) > 0.001)
				pc = pc->InsertAfter(temp, pa->exp);
			pa = pa->link; pb = pb->link;
		}
		else if (pa->exp < pb->exp) {
			pc = pc->InsertAfter(pa->coef, pa->exp);
			pa = pa->link;
		}
		else {
			pc = pc->InsertAfter(pb->coef, pb->exp);
			pb = pb->link;
		}
	}
	if (pa != NULL)p = pa;
	else p = pb;
	while (p!=NULL)
	{
		pc = pc->InsertAfter(p->coef, p ->exp);
		p = p->link;
	}
	return C;
};

Polynomial operator*(Polynomial& A, Polynomial& B) {
	//将一元多项式A和B相乘，乘积用带附加头节点的单链表存储，返回值为指向存储乘积多项式的
	//单链表的头指针
	Term *pa, *pb, *pc; int AL, BL,i,k, maxExp;
	Polynomial C;
	pc = C.getHead();
	AL = A.maxOrder(); BL = B.maxOrder();
	if (AL != -1 || BL != -1) {
		maxExp = AL + BL;
		float *result = new float[maxExp + 1];
		for (i = 0; i < maxExp; i++) result[i] = 0.0;
		pa = A.getHead()->link;
		while (pa != NULL) {
			pb = B.getHead()->link;
			while (pb != NULL) {
				k = pa->exp + pb->exp;
				result[k] = result[k] + pa->coef*pb->coef;
				pb = pb->link;
			}
			pa = pa->link;
		}
		for (i = 0; i <= maxExp; i++)
			if (fabs(result[i]) > 0.001)
				pc = pc->InsertAfter(result[i], i);
		delete[]result;
	}
	pc->link = NULL;
	return C;
};
#endif

