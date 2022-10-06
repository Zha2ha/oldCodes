#include "BinaryTree.h"
#include <iostream>

bool BinaryTree::Insert(BinTreeNode* parent, const int& x, bool asLeft)
{
	if (!parent)
		return false;
	BinTreeNode* p = new BinTreeNode(x);
	if (!p)
	{
		cerr << "memory error\n";
		return false;
	}
	if (asLeft)
	{
		p->leftChild = parent->leftChild;
		parent->leftChild = p;
	}
	else
	{
		p->rightChild = parent->rightChild;
		parent->rightChild = p;
	}
	return true;
}

void BinaryTree::_Destroy(BinTreeNode* subTree)
{
	if (subTree != nullptr)
	{
		//递归释放subTree的左子树
		_Destroy(subTree->leftChild);
		//递归释放subTree的右子树
		_Destroy(subTree->rightChild);
		delete subTree;
		subTree = nullptr;
	}
}

BinTreeNode* BinaryTree::_Parent(BinTreeNode* subTree, BinTreeNode* current)
{
	if (subTree == nullptr) return NULL;
	if (subTree->leftChild == current || subTree->rightChild == current)
		return subTree;
	BinTreeNode* p;
	if ((p = _Parent(subTree->leftChild, current)) != NULL)
		return p;
	else
		return _Parent(subTree->rightChild, current);
	return nullptr;
}

void BinaryTree::_Traverse(BinTreeNode* current, ostream& out) const
{
	if (current != NULL)
	{
		out << current->data << " ";
		_Traverse(current->leftChild, out);
		_Traverse(current->rightChild, out);

	}
}

ostream& operator<<(ostream& out, BinaryTree& tree)
{
	// TODO: 在此处插入 return 语句
	out << "PreOrder look through\n";
	tree._Traverse(tree.root, out);
	out << endl;
	return out;
}
