#pragma once
#include"Huffman.h"
struct HEAD
{
	char type[4];//文件类型
	int length;//原文件长度
	int weight[256];//权值
};
typedef char *BUFFER;
int Compress(const char *pFilename);
char Str2byte(const char *pBinStr);
char * Encode(const char *pFilename, const HuffmanCode pHC, char *pBuffer, const int nSize);
int InitHead(const char *pFilename, HEAD& sHead);
int WriteFile(const char *pFilename, const HEAD sHead, const BUFFER pBuffer, const int nSize);