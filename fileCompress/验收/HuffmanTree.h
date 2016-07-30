#pragma once

#include "heap.h"
template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;

	T _weight;

	HuffmanTreeNode(const T& w)
		:_left(NULL)
		,_right(NULL)
		,_weight(w)
	{}
	//////////////////////////////////////////////
	//bool operator!=(const HuffmanTreeNode& h)
	//{

	//	return this->_weight != h._weight;
	//}
	
};

template<class T>
class HuffmanTree
{

	typedef HuffmanTreeNode<T> Node;
public:
	HuffmanTree(const T a[], size_t n, const T& invalid)
	{
		struct NodeCompare
		{
			bool operator()(const Node*l, const Node* r)
			{
				return l->_weight < r->_weight;
			}
		};

		Heap<Node*, NodeCompare> minHeap;
		for (size_t i = 0; i < n; ++i)
		{
			if (a[i] != invalid)
			{
				minHeap.Push(new Node(a[i]));
			}
		}
		
		while (minHeap.size()>1)
		{
			Node* left = minHeap.Top();
			minHeap.Pop();
			Node* right = minHeap.Top();
			minHeap.Pop();

			Node* parent = new Node(left->_weight + right->_weight);
			parent->_left = left;
			parent->_right = right;

			minHeap.Push(parent);
		}
		_root = minHeap.Top();
	}

	Node* GetRoot()
	{
		return _root;
	}

	~HuffmanTree()
	{
		Destory(_root);
		_root = NULL;
	}

	void Destory(Node* root)
	{
		if (root == NULL)
			return;

		Destory(root->_left);
		Destory(root->_right);

		delete root;

	}

protected:
	HuffmanTree(const HuffmanTree<T>&);
	HuffmanTree<T>operator=(const HuffmanTree<T>&);
protected:
	Node* _root;
};

void TestHuffmanTree()
{
	int a[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	HuffmanTree<int> t(a, 10, 0);
}