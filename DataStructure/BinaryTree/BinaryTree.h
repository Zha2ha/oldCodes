#pragma once
//unfinished
#include <iostream>
#include "BinTreeNode.h"
using namespace std;

class BinaryTree
{
public:
	BinaryTree():root(0){}
	BinaryTree(BinaryTree& s)
	{
		root = _Copy(s.root);
	}
	~BinaryTree() { _Destroy(root); }
	bool IsEmpty()
	{
		return root == 0 ? true : false;
	}
	BinTreeNode* Parent(BinTreeNode* cur)
	{
		return root == 0 || root == cur ? 0 : _Parent(root, cur);
	}
	BinTreeNode* LeftChild(BinTreeNode* cur)
	{
		return cur != 0 ? cur->leftChild : 0;
	}
	BinTreeNode* RightChild(BinTreeNode* cur)
	{
		return cur != 0 ? cur->rightChild : 0;
	}
	int Height()
	{
		return _Height(root);
	}
	int Size()
	{
		return _Size(root);
	}
	BinTreeNode* GetRoot()const
	{
		return root;
	}
	bool Insert(BinTreeNode* parent, const int& x, bool asLeft = true);
	BinTreeNode* Find(const int& item)const;
	//ǰ�����򣬺��򣬲������
	void PreOrder(void(*Visit)(BinTreeNode* p))
	{
		_PreOreder(root, Visit);//���õݹ麯��
	}
	void InOrder(void(*Visit)(BinTreeNode* p))
	{
		_InOreder(root, Visit);//���õݹ麯��
	}
	void PostOrder(void(*Visit)(BinTreeNode* p))
	{
		_PostOreder(root, Visit);//���õݹ麯��
	}
	void LevelOrder(void(*Visit)(BinTreeNode* p));//�������,������ȱ���,Ҫ�õ�����,������,FIFO

protected:
	BinTreeNode* root;
	void _CreateBinTree(istream& in, BinTreeNode* subTree);
	void _Destroy(BinTreeNode* subTree);//ɾ������
	BinTreeNode* _Copy(BinTreeNode* oriNode);//���ƽڵ�
	int _Height(BinTreeNode* subTree);//�����߶�
	int _Size(BinTreeNode* subTree);//�����ڵ���
	BinTreeNode* _Parent(BinTreeNode* subTree, BinTreeNode* current);
	BinTreeNode* _Find(BinTreeNode* subTree, int& x)const;
	//TO-DO:��Ա������������ʵ��
	void _Traverse(BinTreeNode* current, ostream& out)const;//ǰ������������
	void _PreOreder(BinTreeNode* subTree, void(*Visit)(BinTreeNode* p));
	void _InOreder(BinTreeNode* subTree, void(*Visit)(BinTreeNode* p));
	void _PostOreder(BinTreeNode* subTree, void(*Visit)(BinTreeNode* p));
	friend istream& operator>>(istream& in, BinaryTree& tree)
	{
		_CreateBinTree(in, tree.root);
		return in;
	}
	friend ostream& operator<<(ostream& out, BinaryTree& tree);
};

