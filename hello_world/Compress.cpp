#include<iostream>
#include<stdlib.h>
#include"Compress.h"
using namespace std;
int Compress(const char *pFilename)
{
	int weight[256] = { 0 };//����256���ֽ��ظ��Ĵ���
	FILE *in = fopen(pFilename, "rb");//�Զ���������ʽ���ļ�
	int ch = 0;
	unsigned long nSize = 0;
	//ɨ���ļ������Ȩ��
	while ((ch = getc(in)) != EOF)
	{
		weight[ch]++;
	}
	//�ر��ļ�
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
	cout << fileSize << " �ֽ�" << endl;

	aHuffmanTree(HT, weight);//����
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
	cout << len << " �ֽ�" << endl;
	cout << "ѹ�����ʣ�" << (double)len / fileSize * 100 << "%" << endl;
	return OK;
	return 0;
}

//�ַ���ת�룬���ַ���ת��Ϊ�ֽ�
char Str2byte(const char *pBinStr)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;//����һλ
		if (pBinStr[i] == '1')
		{
			b = b | 0x01;
		}
	}
	return b;
}

//ѹ������
char * Encode(const char *pFilename, const HuffmanCode pHC, char *pBuffer, const int nSize)
{
	FILE *in = fopen(pFilename, "rb");
	if (!in)
	{
		cerr << "��Դ�ļ�ʧ�ܣ�" << endl;
		return ERROR;
	}

	pBuffer = (char *)malloc(nSize * sizeof(char));//���ٻ�����
	if (!pBuffer)
	{
		cerr << "Buffer failed" << endl;
		return ERROR;
	}

	char cd[256] = { 0 };
	int pos = 0;
	int ch;
	//ɨ���ļ�������Huffman�����������ѹ����ѹ������ݴ浽�������С�
	while ((ch = fgetc(in)) != EOF)
	{
		strcat(cd, pHC[ch + 1]);//���Ʊ��뵽cd
		//ѹ������
		while (strlen(cd) >= 8)
		{
			//��ȡ�ַ������8���ַ���������ֽ�
			pBuffer[pos++] = Str2byte(cd);
			//�ַ�����������8�ֽ�
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
	//��ʼ��ͷ�ļ�
	strcpy(sHead.type, "HUF");//�ļ�����
	sHead.length = 0;//ԭ�ļ�����
	for (int i = 0; i<256; i++)
	{
		sHead.weight[i] = 0;//Ȩֵ
	}
	FILE *in = fopen(pFilename, "rb");
	if (!in)
	{
		cerr << "�ļ���ʧ�ܣ�";
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
	//�����ļ���
	char filename[256] = { 0 };
	strcpy(filename, pFilename);
	strcat(filename, ".huf");
	FILE *out = fopen(filename, "wb");
	if (!out)
	{
		return ERROR;
	}
	fwrite(&sHead, sizeof(HEAD), 1, out);	//д�ļ�ͷ
	fwrite(pBuffer, sizeof(char), nSize, out);//дѹ����ı���
	fclose(out);
	out = NULL;
	cout << "����ѹ���ļ���" << filename << endl;
	int len = sizeof(HEAD) + strlen(pFilename) + 1 + nSize;
	return len;
}