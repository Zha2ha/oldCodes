#pragma once
#include <iostream>
using namespace std;

const int DEFAULT_SIZE = 100;
template<typename T>
struct Trituple//��Ԫ��ṹ����,����Ԫ��洢
{
	int row, col;//�кţ��к�
	T value;     //ֵ
	Trituple<T>& operator=(Trituple<T>& x)
	{
		row = x.row;
		col = x.col;
		value = x.value;
	}
};

template<typename T>
class SparseMatrix//ϡ�������ඨ�壬����Ԫ�����ʽ��ʾϡ�����
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
	SparseMatrix<T>& Transpose();//ת��
	SparseMatrix<T>& FastTranspose();//����ת��
	//SparseMatrix<T>& Add(SparseMatrix<T>& b);//���
	//SparseMatrix<T>& Multiply(SparseMatrix<T>& b);//���

private:
	int rows, cols, terms;//�У��У�����Ԫ����
	int maxTerms;//��Ԫ�����������
	Trituple<T>* smArray;//��Ԫ������

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
inline SparseMatrix<T>& SparseMatrix<T>::FastTranspose()//����ʱ�临�Ӷ�
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
