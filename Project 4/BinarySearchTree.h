/*
 * BinarySearchTree.h
 *
 *  Created on: Apr 7, 2021
 *      Author: aranawillow
 */
#include <iostream>
using namespace std;


#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <cstdlib>

//return the maximum of two integers
int max (int a, int b)
{
	if (a < b) return b;
	else return a;
}

class Exception {}; //general exception

class BinaryTreeException : Exception {}; //general binary tree exception
class BinaryTreeMemory : BinaryTreeException {}; //memory error
class BinaryTreeEmptyTree : BinaryTreeException {}; //when an empty tree exists

//general binary search tree exception
class BinarySearchTreeException: BinaryTreeException {};
//subtree has been changed
class BinarySearchTreeChangedSubtree : BinarySearchTreeException {};
//binary search tree does not exist or cannot be found
class BinarySearchTreeNotFound : BinarySearchTreeException {};

template <class DataType>
class BinarySearchTree;

template <class DataType>
//used for producing output
ostream& operator << (ostream& s,  BinarySearchTree<DataType>& X);

// /////////////////////////////////////////////////////////////
template <class DataType>
class BinarySearchTree
// /////////////////////////////////////////////////////////////
{
	//print the inorder and post order traversals of the x tree and associated y trees
	friend ostream& operator<< <DataType> (ostream& s,  BinarySearchTree<DataType>& X);
protected:
	DataType* _root; //the root
	int ID; //identification
	BinarySearchTree<DataType>* _left; //left subtree
	BinarySearchTree<DataType>* _right; //right subtree
	BinarySearchTree<DataType>* yTree; //yTree associated with current xNode
	//true if the binary search tree is the subtree of another binary search tree
	bool _subtree;
	//create a new subtree (empty tree)
	virtual BinarySearchTree<DataType>* makeSubtree();
	//copy a tree's root, left tree, and right tree
	virtual void copyTree (BinarySearchTree<DataType>* bst);
	//make the root, left tree, and right tree equal to null
	virtual void _makeNull ();
	//display the x tree using inorder traversal
	virtual void inOrder_xTreeDisplay();
	//display the y tree using inorder traversal
	virtual void inOrder_yTreeDisplay();
	//display the x tree using preorder traversal
	virtual void preOrder_xTreeDisplay();
	//display the y tree using preorder traversal
	virtual void preOrder_yTreeDisplay();
public:
	//default constructor
	BinarySearchTree ();
	//constructs a bst with the given data as the root
	BinarySearchTree (const DataType& data);
	//constructs a bst at the xNode containing x and the yNode with ID
	BinarySearchTree(const DataType& x, const DataType& y, int ID);
	//destructor
	virtual ~BinarySearchTree ();
	virtual bool isEmpty();
    // returns true if tree is empty,
    // but otherwise returns false
	virtual int height ();
    // returns the height (or depth) of the tree
	virtual int size ();
    // returns the number of nodes in the tree
	virtual DataType& root ();
    // returns data from the root
	virtual BinarySearchTree<DataType>* left ();
    // returns the left subtree
	virtual BinarySearchTree<DataType>* right ();
    // returns the right subtree
	virtual bool subtree();
	//returns true if the tree is a subtree
	virtual void makeEmpty ();
	//empties the tree and its children
	BinarySearchTree<DataType>* _find (const DataType& data);
	//finds the tree with the given data as its root
	virtual int pointFind (const DataType& x, const DataType& y);
	//finds the yNode with the given y value at the xNode with the given x value
	virtual int remove (const DataType& data);
	//removes the tree containing the given data as its root
	virtual void rangeSearch (const DataType& low, const DataType& high);
	//prints all the trees with roots within the given range
	virtual BinarySearchTree<DataType>* insert (const DataType& data);
	//inserts a new tree into the existing tree using the given data
	virtual void pointInsert(const DataType& x, const DataType& y, int ID );
	//inserts a tree into the ytree with given y value at the xtree with given x value
	virtual void pointRemove(const DataType& x, const DataType& y);
	//removes the ytree with given y value at the xtree with given x value
	virtual void pointRangeSearch(const DataType& xLow, const DataType& xHigh, const DataType& yLow, const DataType& yHigh);
	//prints the x nodes between the x range and the y nodes between the y range
	virtual int getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int index);
	//fills a given array with the inorder traversal of the given tree
	virtual void setLeft(BinarySearchTree<DataType>* left);
	//sets the left tree to be the given tree
	virtual void setRight(BinarySearchTree<DataType>* right);
	//sets the right tree to be the given tree
	virtual void setYTree(BinarySearchTree<DataType>* yTree);
	//sets the y tree to be the given tree
	virtual BinarySearchTree<DataType>* getYTree();
	//returns the y tree


};
template <class DataType>
ostream& operator<< (ostream& s,  BinarySearchTree<DataType>& X) {

	cout << "INORDER TRAVERSAL: ";
	cout << endl;
	X.inOrder_xTreeDisplay(); //prints inorder traversal of the x tree
	cout << "PREORDER TRAVERSAL: ";
	cout << endl;
	X.preOrder_xTreeDisplay(); //prints preorder traversal of the x tree

	return s;
}

template <class DataType>
void BinarySearchTree<DataType>::inOrder_xTreeDisplay() {
	if(_left != NULL)
	_left->inOrder_xTreeDisplay(); //recursive call to left child
	if(_root != NULL)
	cout << root() << ": " << endl; //prints the root value
	if(yTree != NULL) {
	yTree->inOrder_yTreeDisplay(); //prints inorder traversal of ytree
	cout << endl;
	}
	if(_right != NULL)
	_right->inOrder_xTreeDisplay(); //recursive call to right child
}

template <class DataType>
void BinarySearchTree<DataType>::inOrder_yTreeDisplay() {
	if(_left != NULL)
	_left->inOrder_yTreeDisplay(); //recursive call to left child
	if(_root != NULL)
	cout << " " << root() << "(" << ID << ") "; //prints the root value and id
	if(_right != NULL)
	_right->inOrder_yTreeDisplay(); //recursive call to right child
}

template<class DataType>
void BinarySearchTree<DataType>::preOrder_xTreeDisplay() {
	if(_root != NULL)
	cout << root() << ": " << endl; //prints the root value
	if(yTree != NULL) {
	yTree->preOrder_yTreeDisplay(); //prints the preorder traversal of the ytree
	cout << endl;
	}
	if(_left != NULL)
	_left->preOrder_xTreeDisplay(); //recursive call to left child
	if(_right != NULL)
	_right->preOrder_xTreeDisplay(); //recursive call to right child

}

template<class DataType>
void BinarySearchTree<DataType>::preOrder_yTreeDisplay() {
	if(_root != NULL)
	cout << " " << root() << "(" << ID << ") "; //print the root value and id
	if(_left != NULL)
	_left->preOrder_yTreeDisplay(); //recursive call to left child
	if(_right != NULL)
	_right->preOrder_yTreeDisplay(); //recurisve call to right child
}

// ==============================================================
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree ()
{
	//set all values to NULL
	_root = NULL;
	_left = NULL;
	_right = NULL;
	_subtree = false; //default is that the tree is not a subtree
	yTree = NULL;
	ID = -1; //default id
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree (const DataType& data)
{
	_subtree = false; //because this is a constructor, assume that this tree is the head
	_root = new DataType(data);
	//if (data == NULL) throw BinaryTreeMemory();
	//make empty subtrees for left and right children and yTree
	_left = makeSubtree ();
	_right = makeSubtree ();
	yTree = makeSubtree();
}

template <class DataType>
BinarySearchTree<DataType>::BinarySearchTree(const DataType& x, const DataType& y, int ID) {
	_subtree = false; //because this is a constructor, assume that this tree is the head
	_root = new DataType(x);
	//make empty subtrees for left and right children and yTree
	_left = makeSubtree();
	_right = makeSubtree();
	yTree = makeSubtree();
	//insert the y node into the y tree
	BinarySearchTree<DataType>* yNode = yTree->insert(y);
	yNode->ID = ID;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::makeSubtree()
{
	//create a new bst
	BinarySearchTree<DataType>* bst = new BinarySearchTree<DataType> ();
	bst->_subtree = true;
	return bst;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>::~BinarySearchTree ()
{
	//delete root, left and right children, and y tree and set them all to NULL
	if (_root != NULL)
        delete _root;
    _root = NULL;
	if (_left != NULL)
        delete _left;
    _left = NULL;
	if (_right != NULL)
        delete _right;
    _right = NULL;
    if(yTree != NULL)
    	delete yTree;
    yTree = NULL;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::setLeft(BinarySearchTree<DataType>* left) {
	_left = left;
}

template <class DataType>
void BinarySearchTree<DataType>::setRight(BinarySearchTree<DataType>* right) {
	_right = right;
}

template<class DataType>
void BinarySearchTree<DataType>::setYTree(BinarySearchTree<DataType>* yTree) {
	this->yTree = yTree;
}

// --------------------------------------------------------------
template <class DataType>
bool BinarySearchTree<DataType>::isEmpty()
{
	return (_root == NULL); //if the root is null, the bst is empty
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::height ()
{
	if (isEmpty()) return 0;
    return (1 + max (_left->height(), _right->height())); //recursively call for left and right children
   	// max() is in stdlib.h
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::size ()
// returns the number of nodes in the tree
{
	if (isEmpty())
		return 0;
	return (1 + _left->size() + _right->size()); //recursive call for left and right children
}
// --------------------------------------------------------------
template <class DataType>
DataType& BinarySearchTree<DataType>::root ()
{
	if (isEmpty()) throw BinaryTreeEmptyTree();
	return *_root;
}
// returns data from the root
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::left () { return _left; }
// returns the left subtree
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::right (){ return _right; }
// returns the right subtree

// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::getYTree() {
	return yTree;
}
// --------------------------------------------------------------
template <class DataType>
bool BinarySearchTree<DataType>::subtree() { return _subtree; }
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::makeEmpty ()
{
	//delete root, left and right children, and y tree and set all to null
	if (_subtree) throw BinarySearchTreeChangedSubtree();
	if (_root != NULL)
   		delete _root;
    _root = NULL;
	if (_left != NULL)
	   	delete _left;
    _left = NULL;
	if (_right != NULL)
	   	delete _right;
    _right = NULL;
    if(yTree != NULL) {
    	delete yTree;
    }
    yTree = NULL;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::copyTree(BinarySearchTree<DataType>* bst)
{
	//copy over the root, id, children, and y tree
	_root = bst->_root;
	 ID = bst->ID;
	_left = bst->_left;
	_right = bst->_right;
	yTree = bst-> yTree;
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::_makeNull ()
{
	_root = NULL;
	_left = NULL;
	_right = NULL;
	yTree = NULL;
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::_find (const DataType& data)
{
	BinarySearchTree<DataType>* bst = this;
	while (true)
	{
		if (bst->isEmpty())
			return bst; //node where bst should go
		if (*(bst->_root) < data)
		{
			bst = bst->_right; //if current tree is  smaller than desired one,
								// check right subtree
		}
		else if (*(bst->_root) > data)
		{
            bst = bst->_left; //if current tree is bigger than desired one
            					//check left subtree
		}
		else
		{
			return bst; //it must be equal to desired tree
		}
	}
}

// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::pointFind (const DataType& x, const DataType& y)
{
	try{
		BinarySearchTree<DataType>* bstX = _find(x); //look for x node
		if (bstX->isEmpty()) { //if there is no x node, the coordinate does not exist
				cout << "\nSorry!!! Coordinate is not found in the X tree";
				cout << endl;
				return -1;
			}
		//look for yNode in the ytree of the xnode
		BinarySearchTree<DataType>* bstY = bstX->yTree->_find(y);
		if (bstY->isEmpty()) { //if there is no y node, the coordinate does not exist
			cout << "\nSorry!!! Coordinate is not found in the X tree";
			cout << endl;
			return -1;
		}
		else { //both nodes exist, so coordinate exists
		cout<<"\nThe coordinates "<<bstX->root()<< ", " << bstY->root() << " is found in the tree with ID value " << bstY->ID << endl;
		return bstY->ID;
		}
	}
	catch(Exception& e)
	{
		cout<<"\nSorry!!! Element is not found in the tree";
		cout << endl;
		return -1;
	}
}
// --------------------------------------------------------------
template <class DataType>
BinarySearchTree<DataType>* BinarySearchTree<DataType>::insert (const DataType& data)
{
//	if (_subtree) throw BinarySearchTreeChangedSubtree();
	BinarySearchTree<DataType>* bst = _find (data);
	if (bst->isEmpty()) //if _find returned an empty node, that is where tree should be put
	{
		bst->_root = new DataType (data);
		bst->_left = makeSubtree ();
		bst->_right = makeSubtree ();
		bst->yTree = makeSubtree();
	}
	else
	{
		//replace node with new data
        delete bst->_root;
		bst->_root = new DataType (data);
	}
	return bst;
}

template <class DataType>
void BinarySearchTree<DataType>::pointInsert(const DataType& x, const DataType& y, int ID) {
	BinarySearchTree<DataType>* temp1;
	temp1 = _find(x); //look for the x node to insert at
	if(temp1->isEmpty()) {
		temp1 = insert(x); //insert x node if it does not already exist
	}
	(*temp1).ID = -1; //since this is an x node, it has an id of -1
	//insert the y node into the x node's y tree
	BinarySearchTree<DataType>* temp2 = (*((*temp1).yTree)).insert(y);
	(*temp2).ID = ID; //set the y node to have the given id
}
// --------------------------------------------------------------
template <class DataType>
int BinarySearchTree<DataType>::remove (const DataType& data)
{
	//if (_subtree) throw BinarySearchTreeChangedSubtree();
	BinarySearchTree<DataType>* bst;
	BinarySearchTree<DataType>* bst2;
	BinarySearchTree<DataType>* bst3;

	bst = _find (data);
	int toReturn = bst->ID;
	if (bst->isEmpty()) {
		cout << "The element you are trying to remove is not in the tree";
		cout << endl;
		return -1;
	}

	else {
    // dispose of the existing data; the pointer will be overwritten
    delete bst->_root;

    // .............................................................
	if (bst->_left->isEmpty())
	{
        // the left subtree exists, but the pointer will be overwritten,
        // so we must dispose of it
        delete bst->_left;
        bst2 = bst->_right;		// save the pointer to the right subtree
		bst->copyTree (bst2);	// copy the right subtree;
        // this empties tree if right empty
        bst2->_makeNull ();		// prepare right subtree for deletion
        delete bst2;				// delete right subtree to avoid garbage
	}

	else if (bst->_right->isEmpty())
	{
        // the right subtree exists, but the pointer will be overwritten,
        // so we must dispose of it
        delete bst->_right;
        bst2 = bst->_left;		// save the pointer to the left subtree
		bst->copyTree (bst2);	// copy the left subtree
        bst2->_makeNull ();		// prepare left subtree for deletion
        delete bst2;				// delete left subtree to avoid garbage
	}

	else		// both subtrees non-empty
	{
        // move to the right
		bst2 = bst->_right;
        // then move down to the left as far as possible
		while (!bst2->_left->isEmpty()) bst2 = bst2->_left;
        // overwrite the data pointer
		bst->_root = bst2->_root;

        // bst2's left child is known to be empty and pointer will be overwritten
     	delete bst2->_left;
        // now bst2's right child is copied into it
		if (bst2->_right->isEmpty())
        {
	     	delete bst2->_right;
            bst2->_makeNull();
        }
		else
        {
            bst3 = bst2->_right;
            bst2->copyTree(bst2->_right);
            bst3->_makeNull ();
            delete bst3;
        }
	}
	return toReturn;
	}
}

template <class DataType>
void BinarySearchTree<DataType>::pointRemove(const DataType& x, const DataType& y) {
	BinarySearchTree<DataType>* bstX;
	bstX = _find(x); //look for the x node
	if(!bstX->isEmpty()) {
	bstX->yTree->remove(y); //remove the y node from the y tree if the x node was found
	if(bstX->yTree->isEmpty() || bstX->yTree == NULL) {
		bstX->yTree = NULL;
			remove(x); //if the x node does not have any more y nodes, remove the x node
		}
	} else {
		//otherwise, the x node or y node was not found
		cout << "The element you are trying to remove is not in the tree";
		cout << endl;
	}
}
// --------------------------------------------------------------
template <class DataType>
void BinarySearchTree<DataType>::rangeSearch (const DataType& low, const DataType& high)
{
	if (isEmpty()) return;
	if (*_root >= low) //if the root is bigger than lowest range value
    {
        _left->rangeSearch(low,high); //look in the left subtree
		if (*_root <= high) //if root is within range
		{
			cout << *_root << " "; //print out root data
		}
    }
	if (*_root <= high) //if root is smaller than highest range value
        _right->rangeSearch(low,high); //look in the right subtree
}

template <class DataType>
void BinarySearchTree<DataType>::pointRangeSearch(const DataType& xLow, const DataType& xHigh, const DataType& yLow, const DataType& yHigh) {
	if (isEmpty()) return;
		if (*_root >= xLow) //if x node is above low range value
	    {
	        _left->pointRangeSearch(xLow,xHigh,yLow,yHigh); //check left subtree
	    }
		if(*_root>= xLow && *_root<= xHigh) { //if x node is within range
			cout << *_root << " : "; //print out the root data
	        yTree->rangeSearch(yLow,yHigh); //search y tree
	        cout << endl;
		}
		if (*_root <= xHigh) //if x node is below high range value
	        _right->pointRangeSearch(xLow,xHigh,yLow,yHigh); //check right subtree
}

template <class DataType>
int BinarySearchTree<DataType>::getInorderTraversal(BinarySearchTree<DataType>* node, BinarySearchTree<DataType>** inOrderArray, int index)
{
	try{
		if (node->isEmpty()) throw BinarySearchTreeNotFound();
	}
	catch(BinarySearchTreeNotFound e){
		cout << "No tree for inorder traversal";
		cout << endl;
		return index;
	}

	// cout << "value: " << this->root() << endl;
	// cout << "left: " << *(this->left()->_root) << endl;
	// cout << "right: " << *(this->right()->_root) << endl;

	if (!this->isEmpty()) { //if node has a value on the tree
		if(node->left()->_root != NULL) //if left child has a value
		{
			// cout << "\tcalling left" << endl;

			//recursive call on left subtree
			index = node->left()->getInorderTraversal(node->left(), inOrderArray, index);
		}

		inOrderArray[index++] = node; //put the root into the inorder array
		// cout << "index: " << index - 1 << " inOrderArray[i]: " << inOrderArray[index - 1]->root() << endl;

		if(node->right()->_root != NULL) //if right child has a value
		{
			// cout << "\tcalling right" << endl;
			//recursive call on right subtree
			index = node->right()->getInorderTraversal(node->right(), inOrderArray, index);
		}
	}
	return index; //keep track of index in array to know where to add next
}




#endif /* BINARYSEARCHTREE_H_ */
