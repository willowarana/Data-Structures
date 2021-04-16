/*
 * project4.cpp
 *
 *  Created on: Apr 7, 2021
 *      Author: aranawillow
 */

/*
 *    Data Structures Featuring C++  (c) 2021 Sridhar Radhakrishnan
 */

#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

//Rebalances the binary search tree to a minimum height
template<class DataType>
BinarySearchTree<DataType>* GlobalRebalance(BinarySearchTree<DataType>** inOrderArray, int l, int r)
{
	int mid = 0;
	BinarySearchTree<DataType>* temp = new BinarySearchTree<DataType>();

	if(l <= r) //make sure that the current array section is valid
	{
		mid = ((l + r) / 2); //find the middle value of the array
		temp = inOrderArray[mid]; //temp is the bst at this middle value
		 //recursive call to left child
		temp->setLeft(GlobalRebalance(inOrderArray, l, mid - 1));
		//recursive call to right child
		temp->setRight(GlobalRebalance(inOrderArray, mid + 1, r));
	}

	return temp;
}

int main()
{
	char c; //current user command
	bool initialized = false; //becomes true once the bst is initialized
	BinarySearchTree<int>* bst; //the binary search tree object
	int x; //x value
	int y;//y value
	cin.get(c); //priming read for the first user input
	while(!cin.eof()) { //while the user continues inputting commands/ file has not ended
		switch(c) { //switch case for input
		case 'I' : //insert a point
			int id;
			cin >> x; //get values for x, y and id
			cin >> y;
			cin >> id;

			//initialize a binary search tree if it has not been initialized
			if(!initialized) {
				bst = new BinarySearchTree<int>(x, y, id);
				initialized = true;
			}
			else {
				//insert the point
				bst->pointInsert(x, y, id);
			}
			//print out the inserted point
			cout << x << " " << y << " " << id << endl;
			break;

		case 'R' : //remove a point
			cin >> x; //get input values
			cin >> y;
			cout << "Remove: " << x << " " << y << endl;
			bst->pointRemove(x, y);
			break;

		case 'F' : //find a point
			cin >> x;
			cin >> y;
			cout << "Find: " << x << " " << y << endl;
			bst->pointFind(x, y);
			break;

		case 'S' : //search for a point within a specified range
			int xLow;
			int xHigh;
			int yLow;
			int yHigh;
			cin >> xLow;
			cin >> xHigh;
			cin >> yLow;
			cin >> yHigh;
			cout << "Range search" << endl;
			cout << xLow << " " << xHigh << " " << yLow << " " << yHigh << endl;
			bst->pointRangeSearch(xLow, xHigh, yLow, yHigh);
			break;

		case 'Y': //balance a y-tree
			cin >> x;
			cout << "Y tree balance" << endl;
			cout << x << endl;
			BinarySearchTree<int>* xNode;
			xNode= bst->_find(x); //find the bst with x value
			BinarySearchTree<int>* yTree;
			yTree = xNode->getYTree(); //get its y-tree
			//get the inorder traversal of the y tree
			BinarySearchTree<int>** inOrderTraversal;
			inOrderTraversal = new BinarySearchTree<int>*[yTree->size()];
			bst->getInorderTraversal(yTree, inOrderTraversal, 0);
			//rebalance the y tree
			BinarySearchTree<int>* newY;
			newY = GlobalRebalance(inOrderTraversal, 0, yTree->size() - 1);
			//change the original yTree to the balanced yTree
			xNode->setYTree(newY);
			break;

		case 'P' : //print the inorder and preorder traversals of the xtree and associated ytrees
			cout << "Print" << endl << (*bst) << endl;
			break;


		}
		cin.get(c); //get the next input/command
	}

	delete bst; //delete the binary search tree
    return 0;

}



