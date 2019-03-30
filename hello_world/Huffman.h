#pragma once
#define OK 1
#define ERROR 0
//HUffman���ڵ�
struct HTNode
{
	int weight;//Ȩֵ
	int parent;//���ڵ�
	int lchild;//����
	int rchild;//�Һ���
};

//Huffman��
typedef HTNode * HuffmanTree;//�洢���
typedef char **HuffmanCode;//�洢ÿ��Ҷ�ڵ��huffman����
void aHuffmanTree(HuffmanTree &pHT, int *w);
int Select(HuffmanTree pHT, int nSize);
int HuffmanCoding(HuffmanCode& pHC, HuffmanTree& pHT);
//void TestHufTree(HuffmanTree pHT);
//void TestHufTreeN(int root, HuffmanTree pHT);
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC);
