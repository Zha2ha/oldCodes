#pragma once
#include <iostream>
using namespace std;

const int DEFAULT_SIZE = 100;
template<typename T>
struct Trituple//三元组结构定义,用三元组存储
{
	int row, col;//行号，列号
	T value;     //值
	Trituple<T>& operator=(Trituple<T>& x)
	{
		row = x.row;
		col = x.col;
		value = x.value;
	}
};

template<typename T>
class SparseMatrix//稀疏矩阵的类定义，用三元组的形式表示稀疏矩阵
{
public:
	SparseMatrix(int maxSz = DEFAULT_SIZE);
	SparseMatrix(SparseMatrix<T>& x);
	~SparseMatrix() { delete[]smArray; }
	SparseMatrix<T>& operator = (SparseMatrix<T>& x)
	{
		rows = x.rows;
		cols = x.cols;
		terms = x.terms;
		maxTerms = x.maxTerms;
		smArray = new Trituple<T>[maxTerms];
		if (smArray == NULL)
		{
			cerr << "memory distribute error" << endl;
			exit(1);
		}
		for (int i = 0; i < terms; ++i)
		{
			smArray[i] = x.smArray[i];
		}
	}
	SparseMatrix<T>& Transpose();//转置
	SparseMatrix<T>& FastTranspose();//快速转置
	//SparseMatrix<T>& Add(SparseMatrix<T>& b);//相加
	//SparseMatrix<T>& Multiply(SparseMatrix<T>& b);//相乘

private:
	int rows, cols, terms;//行，列，非零元素数
	int maxTerms;//三元组数组的容量
	Trituple<T>* smArray;//三元组数组

};

template<typename T>
inline SparseMatrix<T>::SparseMatrix(int maxSz):maxTerms(maxSz)
{
	if (maxSz < 1)
	{
		cerr << "initialize error" << endl;
		exit(1);
	}
	smArray = new Trituple<T>[maxSz];
	if (smArray == NULL)
	{
		cerr << "memory distribute error" << endl;
		exit(1);
	}
	rows = cols = terms = 0;
}

template<typename T>
inline SparseMatrix<T>::SparseMatrix(SparseMatrix<T>& x)
{
	rows = x.rows;
	cols = x.cols;
	terms = x.terms;
	maxTerms = x.maxTerms;
	smArray = new Trituple<T>[maxTerms];
	if (smArray == NULL)
	{
		cerr << "memory distribute error" << endl;
		exit(1);
	}
	for (int i = 0; i < terms; ++i)
	{
		smArray[i] = x.smArray[i];
	}
}

template<typename T>
inline SparseMatrix<T>& SparseMatrix<T>::Transpose()
{
	SparseMatrix<T>& b(maxTerms);
	b.rows = cols;
	b.cols = rows;
	b.terms = terms;
	if (terms > 0)
	{
		int k, i, currentB = 0;
		for (k = 0; k < cols; ++k)
		{
			for (i = 0; i < terms; ++i)
			{
				if (smArray[i].col == k)
				{
					b.smArray[currentB].row = k;
					b.smArray[currentB].col = smArray[i].row;
					b.smArray[currentB].value = smArray[i].value;
					++currentB;
				}
			}
		}
	}
	return b;
}

template<typename T>
inline SparseMatrix<T>& SparseMatrix<T>::FastTranspose()//降低时间复杂度
{
	int* rowSize = new int[cols];
	int* rowStart = new int[cols];
	SparseMatrix<T> b(maxTerms);
	b.rows = cols;
	b.cols = rows;
	b.terms = terms;
	if (terms > 0)
	{
		int i, j;
		for (i = 0; i < cols; ++i)
		{
			rowSize[i] = 0;
		}
		for (i = 0; i < terms; ++i)
		{
			++rowSize[smArray[i].col];
		}
		rowStart[0] = 0;
		for (i = 1; i < cols; ++i)
		{
			rowStart[i] = rowStart[i - 1] + rowSize[i - 1];
		}
		for (i = 0; i < terms; ++i)
		{
			j = rowStart[smArray[i].col];
			b.smArray[j].row = smArray[i].col;
			b.smArray[j].col = smArray[i].row;
			b.smArray[j].value = smArray[i].value;
			++rowStart[smArray[i].col];
		}
	}
	delete[]rowSize;
	delete[]rowStart;
	return b;
}
