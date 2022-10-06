#pragma once
struct BinTreeNode
{
	int data;
	BinTreeNode* leftChild, * rightChild;
	BinTreeNode():leftChild(0), rightChild(0){}
	BinTreeNode(int x, BinTreeNode* l = 0, BinTreeNode* r = 0):data(x), leftChild(l), rightChild(r){}
};

