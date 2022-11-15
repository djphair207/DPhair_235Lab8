#include "Node.h"

int Node::getData() const {
	return data;
}

Node* Node::getLeftChild() const {
	return left;
}

Node* Node::getRightChild() const {
	return right;
}

int Node::getHeight() {	// HOPEFULLY IT WORKS
	return height;
}
