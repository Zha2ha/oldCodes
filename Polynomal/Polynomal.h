#ifndef POLYNOMAL_H
#define POLYNOMAL_H
#include<iostream>
using namespace std;
struct Term {
	float coef;             //ϵ��
	int exp;                //ָ��
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
	//�ڵ�ǰ��thisָ��ָʾ��������ô˺����Ķ��󣩺������һ�����
	link = new Term(c, e, link);
	return link;
};

ostream& operator << (ostream& out, const Term& x) {
	//Term����Ԫ���������һ����x�����ݵ������out�С�
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
	//���ƹ��캯���������ж���ʽ����R��ʼ����ǰ����ʽ����R
	first = new Term(0, -1);
	Term *destptr = first, *srcptr = R.getHead()->link;
	while (srcptr != NULL) {
		destptr->InsertAfter(srcptr->coef, srcptr->exp);
		//��destptr��ָ��������½�㣬����destptrָ������½��
		srcptr = srcptr->link;
		destptr = destptr->link;
	}
};

int Polynomial::maxOrder() {
	//������������������ʽ����������ʱ�����һ������ָ�������
	Term *current = first;
	while (current->link != NULL)current = current->link;
	//�ձ����Σ�currentͣ����first������currentͣ���ڱ�β���
	return current->exp;
};

istream& operator >> (istream& in, Polynomial& x) {
	//POlynomial�����Ԫ��������������in��������β�巨����һ������ʽ
	Term *rear = x.getHead(); int c,e;    //rear ��βָ��
	while (1) {
		cout << "Input a term(coef,exp):" << endl;
		in >> c >> e;                     //�������ϵ��c��ָ��e
		if (e < 0)break;                  //��e<0�����������
		rear = rear->InsertAfter(c, e);   //���ӵ�rear��ָ����
	}
	return in;
};

ostream& operator<<(ostream& out, const Polynomial& x) {
	//Polynomial�����Ԫ���������������ͷ�ڵ�Ķ���ʽ����x
	Term *current = x.getHead()->link;
	cout << "the polynomial is:" << endl;
	bool h = true;
	while (current != NULL) {
		if (h == false && current->coef > 0.0)
			out << "+";
		h = false;
		out << *current;                //���� Term������ز�����<<��
		current = current->link;
	}
	out << endl;
	return out;
};

Polynomial operator+(Polynomial& A, Polynomial& B) {
	//��Ԫ����������������ͷ�ڵ�İ���������Ķ���ʽ�����ͷָ��ֱ���A.first��B.first,���ص��ǽ������ʽ����
	Term *pa, *pb, *pc, *p; float temp;
	Polynomial C; pc = C.first;   //pcΪ����ʽR�ڴ��������е�βָ��
	pa = A.getHead()->link; pb = B.getHead()->link;  //pa��pb��λ��A��B�ĵ�һ����㣬�������ļ��ָ��
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
	//��һԪ����ʽA��B��ˣ��˻��ô�����ͷ�ڵ�ĵ�����洢������ֵΪָ��洢�˻�����ʽ��
	//�������ͷָ��
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

