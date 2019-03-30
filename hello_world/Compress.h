#pragma once
#include"Huffman.h"
struct HEAD
{
	char type[4];//�ļ�����
	int length;//ԭ�ļ�����
	int weight[256];//Ȩֵ
};
typedef char *BUFFER;
int Compress(const char *pFilename);
char Str2byte(const char *pBinStr);
char * Encode(const char *pFilename, const HuffmanCode pHC, char *pBuffer, const int nSize);
int InitHead(const char *pFilename, HEAD& sHead);
int WriteFile(const char *pFilename, const HEAD sHead, const BUFFER pBuffer, const int nSize);