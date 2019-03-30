#include<iostream>
#include<stdlib.h>
#include"Compress.h"
using namespace std;
int Compress(const char *pFilename)
{
	int weight[256] = { 0 };//保存256种字节重复的次数
	FILE *in = fopen(pFilename, "rb");//以二进制流形式打开文件
	int ch = 0;
	unsigned long nSize = 0;
	//扫描文件，获得权重
	while ((ch = getc(in)) != EOF)
	{
		weight[ch]++;
	}
	//关闭文件
	fclose(in);
	in = NULL;
	HTNode *HT = NULL;
	HuffmanCode HC;
	HC = (HuffmanCode)malloc(257 * sizeof(char*));
	for (int j = 0; j<256; j++)
	{
		HC[j] = (char*)malloc(257 * sizeof(char));
	}
	unsigned long fileSize = 0;
	for (int i = 0; i<256; i++)
	{
		fileSize += weight[i];
	}
	cout << fileSize << " 字节" << endl;

	aHuffmanTree(HT, weight);//建树
	if (!HuffmanCoding(HC, HT))
	{
		return ERROR;
	}
	
	for (int i = 0; i<256; i++)
	{
		nSize += weight[i] * strlen(HC[i + 1]);
	}
	nSize = (nSize % 8) ? nSize / 8 + 1 : nSize / 8;
	char *pBuffer = NULL;
	pBuffer = Encode(pFilename, HC, pBuffer, nSize);
	if (!pBuffer)
	{
		return ERROR;
	}
	HEAD sHead;
	unsigned long len = 0;
	if (InitHead(pFilename, sHead))
	{
		len = WriteFile(pFilename, sHead, pBuffer, nSize);
	}
	else
	{
		return ERROR;
	}
	cout << len << " 字节" << endl;
	cout << "压缩比率：" << (double)len / fileSize * 100 << "%" << endl;
	return OK;
	return 0;
}

//字符串转码，将字符串转换为字节
char Str2byte(const char *pBinStr)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;//左移一位
		if (pBinStr[i] == '1')
		{
			b = b | 0x01;
		}
	}
	return b;
}

//压缩编码
char * Encode(const char *pFilename, const HuffmanCode pHC, char *pBuffer, const int nSize)
{
	FILE *in = fopen(pFilename, "rb");
	if (!in)
	{
		cerr << "打开源文件失败！" << endl;
		return ERROR;
	}

	pBuffer = (char *)malloc(nSize * sizeof(char));//开辟缓冲区
	if (!pBuffer)
	{
		cerr << "Buffer failed" << endl;
		return ERROR;
	}

	char cd[256] = { 0 };
	int pos = 0;
	int ch;
	//扫描文件，根据Huffman编码表对其进行压缩，压缩结果暂存到缓存区中。
	while ((ch = fgetc(in)) != EOF)
	{
		strcat(cd, pHC[ch + 1]);//复制编码到cd
		//压缩编码
		while (strlen(cd) >= 8)
		{
			//截取字符串左边8个字符，编码成字节
			pBuffer[pos++] = Str2byte(cd);
			//字符串整体左移8字节
			for (int i = 0; i<256 - 8; i++)
			{
				cd[i] = cd[i + 8];
			}
		}
	}
	if (strlen(cd)>0)
	{
		pBuffer[pos++] = Str2byte(cd);
	}
	return pBuffer;
}

int InitHead(const char *pFilename, HEAD& sHead)
{
	//初始化头文件
	strcpy(sHead.type, "HUF");//文件类型
	sHead.length = 0;//原文件长度
	for (int i = 0; i<256; i++)
	{
		sHead.weight[i] = 0;//权值
	}
	FILE *in = fopen(pFilename, "rb");
	if (!in)
	{
		cerr << "文件打开失败！";
		return ERROR;
	}
	int ch;
	while ((ch = getc(in)) != EOF)
	{
		sHead.weight[ch]++;
		sHead.length++;
	}
	fclose(in);
	in = NULL;
	return OK;
}

int WriteFile(const char *pFilename, const HEAD sHead, const BUFFER pBuffer, const int nSize)
{
	//生成文件名
	char filename[256] = { 0 };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");
	FILE *out = fopen(filename, "wb");
	if (!out)
	{
		return ERROR;
	}
	fwrite(&sHead, sizeof(HEAD), 1, out);	//写文件头
	fwrite(pBuffer, sizeof(char), nSize, out);//写压缩后的编码
	fclose(out);
	out = NULL;
	cout << "生成压缩文件：" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	return len;
}