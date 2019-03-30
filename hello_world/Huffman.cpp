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

//查找最小权值结点
int Select(HuffmanTree pHT, int nSize)
{
	int minValue = 0x7FFFFFFF;//最小值,初值设为最大值
	int min = 0;//元素序号

	//找到最小权值的元素序号
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
{//无栈非递归遍历Huffman树，求Huffman编码
	char cd[256] = { '\0' };//记录访问路径
	int cdlen = 0;//记录当前路径长度
	for (int i = 1; i < 512; i++)
	{
		pHT[i].weight = 0;//遍历Huffman树时用作节点的状态标志
	}
	int p = 511;//根节点
	while (p != 0)
	{
		if (pHT[p].weight == 0)//向左
		{
			pHT[p].weight = 1;
			if (pHT[p].lchild != 0)
			{
				p = pHT[p].lchild;
				cd[cdlen++] = '0';
			}
			else if (pHT[p].rchild == 0)//登记叶子节点的字符的编码
			{
				pHC[p] = (char *)malloc((cdlen + 1) * sizeof(char));
				cd[cdlen] = '\0';
				strcpy(pHC[p], cd);//复制编码
			}
		}
		else if (pHT[p].weight == 1)//向右
		{
			pHT[p].weight = 2;
			if (pHT[p].rchild != 0)//右孩子为叶节点
			{
				p = pHT[p].rchild;
				cd[cdlen++] = '1';
			}
		}
		else
		{//退回父节点，编码长度减1
			pHT[p].weight = 0;
			p = pHT[p].parent;
			--cdlen;
		}
	}
	//free(cd);
	return OK;
}