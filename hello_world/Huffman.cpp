#include<iostream>
#include<stdlib.h>
#include"Huffman.h"
using namespace std;
void aHuffmanTree(HuffmanTree &pHT,int *w)
{
	pHT = (HuffmanTree)malloc(512 * sizeof(HTNode));
	if (!pHT)
	{
		cout << "malloc failed" << endl;
	}
	int i, s1, s2;
	for (i = 1; i < 512; i++)
	{
		if (i <= 256)
		{
			pHT[i].weight = w[i-1];
		}
		else
		{
			pHT[i].weight = 0;
		}
		pHT[i].parent = NULL;
		pHT[i].lchild = NULL;
		pHT[i].rchild = NULL;
	}
	for (i = 257; i < 512; i++)
	{
		s1 = Select(pHT, i - 1);
		pHT[s1].parent = i;
		s2 = Select(pHT, i - 1);
		pHT[s2].parent = i;
		pHT[i].weight = pHT[s1].weight + pHT[s2].weight;
		pHT[i].lchild = s1;
		pHT[i].rchild = s2;
	}
}

//������СȨֵ���
int Select(HuffmanTree pHT, int nSize)
{
	int minValue = 0x7FFFFFFF;//��Сֵ,��ֵ��Ϊ���ֵ
	int min = 0;//Ԫ�����

	//�ҵ���СȨֵ��Ԫ�����
	for (int i = 1; i <= nSize; i++)
	{
		if (pHT[i].parent == 0 && pHT[i].weight < minValue)
		{
			minValue = pHT[i].weight;
			min = i;
		}
	}
	return min;
}

int HuffmanCoding(HuffmanCode& pHC, HuffmanTree& pHT)
{//��ջ�ǵݹ����Huffman������Huffman����
	char cd[256] = { '\0' };//��¼����·��
	int cdlen = 0;//��¼��ǰ·������
	for (int i = 1; i < 512; i++)
	{
		pHT[i].weight = 0;//����Huffman��ʱ�����ڵ��״̬��־
	}
	int p = 511;//���ڵ�
	while (p != 0)
	{
		if (pHT[p].weight == 0)//����
		{
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0)
			{
				p = pHT[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (pHT[p].rchild == 0)//�Ǽ�Ҷ�ӽڵ���ַ��ı���
			{
				pHC[p] = (char *)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(pHC[p], cd);//���Ʊ���
			}
		}
		else if (pHT[p].weight == 1)//����
		{
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0)//�Һ���ΪҶ�ڵ�
			{
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{//�˻ظ��ڵ㣬���볤�ȼ�1
			pHT[p].weight = 0;
			p = pHT[p].parent;
			--cdlen;
		}
	}
	//free(cd);
	return OK;
}