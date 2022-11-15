#ifndef AVL_H_
#define AVL_H_

#include "AVLInterface.h"
#include "NodeInterface.h"
#include "Node.h"
#include <iostream>
#include <cstddef>
#include <algorithm>

using namespace std;

class AVL : public AVLInterface {
protected:
	Node* root;		// ptr to the root node of the tree
public:
	AVL() { root = NULL; };		// constructor, defaults to NULL
	~AVL() {};	// destructor
	Node* getRootNode() const;	// returns the ptr to the root
	bool add(int data);					// adds the given value to the tree in its correct place
	bool remove(int data);			// removes the fiven value and rearranges the tree 
	void clear();								// deletes all values from the tree

private:
	bool addHelper(int data, Node*& curr_root);			// recursive func called by "add"
	bool removeHelper(int data, Node*& curr_root);	// recursive func called by "remove"
	void newPar(Node*& old, Node*& curr);
	void rotateRight(Node*& ptr);		// perform a right rotation about the Node
	void rotateLeft(Node*& ptr);		// perform a left rotation about the Node
	void reBalance(Node*& ptr);	// check the balance of the node by comparing the heights of its two children
	void updateHeight(Node*& ptr); // update the height of the nodes 
	void clearHelper(Node*& curr_root);	// recursive, called by clear to delete
	void debug_helper(Node* ptr); // prints out all the stuff for the node
};

#endif