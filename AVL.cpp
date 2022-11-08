#include "AVL.h"

Node* AVL::getRootNode() const {
	return root;
}

/* * * * * * * ADD * * * * * */
bool AVL::add(int data) {
	return addHelper(data,this->root);
}

bool AVL::addHelper(int data, Node*& curr_root) {
	if(curr_root == NULL) {		// if the tree is empty
		curr_root = new Node(data);	// insert the value as the root, L,R&Parent deafult to NULL
		return true;	//success
	}
	else {
		if (data < curr_root->data) {	// if value less than stored data
			return addHelper(data, curr_root->left);	// search and insert to Left
		}
		else if (data > curr_root->data) {	// if value greater than stored data
			return addHelper(data, curr_root->right);	// search and insert to right
		}
		else {		// otherwise, it's a match
			return false;	// failure
		}
	}
}

/* * * * * * REMOVE * * * * * */
bool AVL::remove(int data) {
	return removeHelper(data,this->root);
}

bool AVL::removeHelper(int data, Node*& curr_root) {
	if (curr_root == NULL) {
		return false;
	}
	else {
		if(data < curr_root->data) {
			return removeHelper(data,curr_root->left);
		}
		else if (data > curr_root->data) {
			return removeHelper(data,curr_root->right);
		}
		else {
			Node* old_root = curr_root;
			if (curr_root->left == NULL) {
				curr_root = curr_root->right;
			}
			else if (curr_root->right == NULL) {
				curr_root = curr_root->left;
			}
			else {
				newPar(old_root, old_root->left);
			}
			delete old_root;
			return true;
		}
	}
}

void AVL::newPar(Node*& old, Node*& curr) {
	if (curr->right != NULL) {
		newPar(old,curr->right);
	}
	else {
		old->data = curr->data;
		old = curr;
		curr = curr->left;
	}
}

/* * * * * * CLEAR * * * * * */
void AVL::clear() {
	//cout << "entered the clear" << endl;
	clearHelper(root);
	//delete root;
	root = NULL;
}

void AVL::clearHelper(Node*& curr_root) {
	if(curr_root != NULL) {
		clearHelper(curr_root->left);
		clearHelper(curr_root->right);
		delete curr_root;
	}
}