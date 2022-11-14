#ifndef NODE_H_
#define NODE_H_

#include "NodeInterface.h"		// Include the interface file
#include <cstddef>

using namespace std;		// Use the standard namespace

class Node : public NodeInterface {
public:						
// Each Node will contain...
	int data;					// the data specific to the node
	Node *left;				// a pointer to the node down to the left
	Node *right;			// a pointer to the node down to the right
	int height;				// the height of the node, 1 if no children
// Member Functions
		// Base Constructor
	Node(const int& the_data = 0, Node* leftChild = NULL, Node* rightChild = NULL, int H = 0){
		data = the_data;
		left = leftChild;
		right = rightChild;
		H = height;
	};
	~Node() {};		// Destructor
	int getData() const;		// return the value stored at the node
	Node *getLeftChild() const;		// return the ptr to the Node's left child
	Node *getRightChild() const;	// retrun the ptr to the Node's right child
	int getHeight();			// return the height of the node
};

#endif