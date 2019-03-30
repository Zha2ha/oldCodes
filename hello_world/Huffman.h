#pragma once
#define OK 1
#define ERROR 0
//HUffman树节点
struct HTNode
{
	int weight;//权值
	int parent;//父节点
	int lchild;//左孩子
	int rchild;//右孩子
};

//Huffman树
typedef HTNode * HuffmanTree;//存储结点
typedef char **HuffmanCode;//存储每个叶节点的huffman编码
void aHuffmanTree(HuffmanTree &pHT, int *w);
int Select(HuffmanTree pHT, int nSize);
int HuffmanCoding(HuffmanCode& pHC, HuffmanTree& pHT);
//void TestHufTree(HuffmanTree pHT);
//void TestHufTreeN(int root, HuffmanTree pHT);
void TestHufCode(int root, HuffmanTree pHT, HuffmanCode pHC);
