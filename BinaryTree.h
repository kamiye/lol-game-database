// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Ye Aung
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include "BinarySearchTree.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree()						{rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree)	{ rootPtr = copyTree(tree.rootPtr); count = tree.size(); }
	virtual ~BinaryTree()				{ destroyTree(rootPtr); }
	BinaryTree & operator=(const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const				{return count == 0;}
	int size() const					{return count;}
	void clear()						{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const		{_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const		{_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const	{_postorder(visit, rootPtr);}
	void reverseOrder(void visit(ItemType &)) const { _reverseorder(visit, rootPtr); }
	void indentTree(void visit(ItemType &, int )) const { int h = 0; _indentTree(visit, rootPtr, h); }
	void filterOrder(void visit(ItemType &, ItemType &, int &), ItemType &target, int &num) const	{ _filterOrder(visit, rootPtr, target, num); }

	void freeMe(void visit(ItemType*)){ _freeMe(visit, rootPtr); };
	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0; 
	virtual bool remove(const ItemType & data) = 0; 
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;



private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _reverseorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _indentTree(void visit(ItemType &, int), BinaryNode<ItemType> *nodePtr, int) const;
	void _filterOrder(void visit(ItemType &, ItemType &, int &), BinaryNode<ItemType>* nodePtr, ItemType &target, int &num) const;

	void _freeMe(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const;

}; 

//////////////////////////////////////////////////////////////////////////
//This function copy the whole tree to an empty tree
template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = 0;
	if (nodePtr != 0)
	{
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem(), 0, 0);
		newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	}

    return newNodePtr;
}  

//This function is used in the ~destructor() function
template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
	}
}  

//transverse in preorder
template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

//transverse in inorder
template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();


		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

//transverse in postorder
template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}  

//transverse in reverseorder
template<class ItemType>
void BinaryTree<ItemType>::_reverseorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_reverseorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_reverseorder(visit, nodePtr->getLeftPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_indentTree(void visit(ItemType &, int), BinaryNode<ItemType> *nodePtr, int h) const
{
	if (nodePtr != 0)
	{
		_indentTree(visit, nodePtr->getRightPtr(), ++h);
		ItemType item = nodePtr->getItem();
		visit(item, h);
		_indentTree(visit, nodePtr->getLeftPtr(), h);

	}
}

template<class ItemType>
void BinaryTree<ItemType>::_filterOrder(void visit(ItemType &, ItemType &, int &), BinaryNode<ItemType>* nodePtr, ItemType &target, int &num) const
{
	if (nodePtr != 0)
	{
		_filterOrder(visit, nodePtr->getLeftPtr(), target, num);
		ItemType item = nodePtr->getItem();
		visit(item, target, num);
		_filterOrder(visit, nodePtr->getRightPtr(), target, num);
	}
}

//This function made a operator overload function that can assign from tree to tree
template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	if (this != &sourceTree)
	{
		this->clear();
		rootPtr = copyTree(sourceTree.rootPtr);
		count = sourceTree.count;
	}
	return *this;
}  

//transverse in inorder
template<class ItemType>
void BinaryTree<ItemType>::_freeMe(void visit(ItemType *), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_freeMe(visit, nodePtr->getLeftPtr());
		nodePtr->setFree(visit);
		_freeMe(visit, nodePtr->getRightPtr());
	}
}

#endif