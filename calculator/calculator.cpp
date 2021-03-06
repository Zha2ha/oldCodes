// calculator.cpp: 定义控制台应用程序的入口点。
#include<math.h>
#include"seqstack.h"
#include<iostream>
using namespace std;
class Calculator {
	//模拟一个简单的计算器，此计算器对从键盘读入的后缀表达式求值
public:
	Calculator(int sz):s(sz){}//构造函数
	void Run();//执行计算
	void Clear();
private:
	SeqStack<double> s;//栈对象定义
	void AddOperand(double value);//进操作数栈
	bool Get2Operands(double& left, double& right);//退出两个操作数
	void DoOperator(char op);//形成运算指令，进行计算
};

void Calculator::DoOperator(char op) {
	double left, right, value;
	if (Get2Operands(left, right))
		switch (op) {
		case'+':value = left + right;
			s.Push(value);
			break;
		case'-':value = left - right;
			s.Push(value);
			break;
		case'*':value = left*right;
			s.Push(value);
			break;
		case'/':
			if (right) {
				value = left / right;
				s.Push(value);
			}
			else {
				cerr << "divide by 0!\n";
				Clear();
			}break;
		}
	else
		Clear();
}

bool Calculator::Get2Operands(double &left, double &right) {
	//从操作数栈中取出两个操作数
	if (s.IsEmpty() == true) {
		cerr << "缺少右操作数!" << endl;
		return false;
	}else
		right=s.Pop();
	if (s.IsEmpty() == true) {
		cerr << "缺少左操作数!" << endl;
		return false;
	}else
		left=s.Pop();
	return true;
}

void Calculator::AddOperand(double value) {
	s.Push(value);
}

void  Calculator::Run() {
	char ch;
	double newOperand;
	while (cin >> ch, ch != '=') {//以'='结束
		switch (ch) {
		case'+':case'-':case'*':case'/':
			DoOperator(ch);//计算
			break;
		default:
			cin.putback(ch);//将字符放回输入流
			cin >> newOperand;//读操作数
			AddOperand(newOperand);
		}
	}
	cout << s.Top() << endl;
}


void Calculator::Clear() {
	s.MakeEmpty();
}

int main() {
	Calculator CALC(50);
	CALC.Clear();
	CALC.Run();
	return 0;
}