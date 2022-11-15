#include "AVL.h"

Node* AVL::getRootNode() const {
	return root;
}

/* * * * * * * ADD * * * * * */
// need to add the rotation to the end of add helper
bool AVL::add(int data) {
	cout << "Adding a value: " << data << endl;
	return addHelper(data,this->root);
}

bool AVL::addHelper(int data, Node*& curr_root) {
	if(curr_root == NULL) {		// if the tree is empty
		curr_root = new Node(data);	// insert the value as the root, L,R&Parent deafult to NULL
		updateHeight(root);	// update the heights in the tree
		reBalance(root);		// rebalance the tree
		//updateHeight(curr_root);	// update the height, I don't think this will be good enough
		
		debug_helper(curr_root);
		debug_helper(root);
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
// need to add the rotation to the end of remove helper
bool AVL::remove(int data) {
	cout << "Removing a value\n";
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
			reBalance(curr_root);
			//updateHeight(curr_root);	// update the height, I don't think this will be good enough
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

/* * * * * * ROTATIONS * * * * * */
// Rotation code might need to change
// see 47:20 in the help video
void AVL::rotateRight(Node*& ptr) {
	cout << "Performing R Rotation on node containing " << ptr->data << endl;
	//Node* temp = ptr;
	//ptr = ptr->left;
	//temp->left = ptr->right;
	//ptr->right = temp;

	Node* temp = ptr->left;
	ptr->left = temp->right;
	temp->right = ptr;
	ptr = temp;
	updateHeight(ptr->right);
	debug_helper(ptr->right);
	updateHeight(ptr);
	debug_helper(ptr);
}

void AVL::rotateLeft(Node*& ptr) {
	cout << "Performing L Rotation on node containing " << ptr->data << endl;
	//Node* temp = ptr;
	//ptr = ptr->right;
	//temp->right = ptr->left;
	//ptr->left = temp;

	Node* temp = ptr->right;
	ptr->right = temp->left;
	temp->left = ptr;
	ptr = temp;
	updateHeight(ptr->left);
	updateHeight(ptr);
	debug_helper(ptr->left);
	debug_helper(ptr);
	debug_helper(ptr->right);
}

void AVL::reBalance(Node*& ptr) {		
	// THIS ONE PROBABLY NEEDS TO BE RECURSIVE
	//	Base Case: ptr->left && ptr->right have no children?
	//							ptr->left && ptr->right have height <= 1?
	cout << "Checking if rebalancing necessary" << endl;
	int LHeight;						// declare two ints for the child heights
	int RHeight;
	int LLHeight, LRHeight;	// declare ints to keep track of child heights
	int RRHeight, RLHeight;
	int balance;							// declare an int to test balance
	
	if(ptr->left == NULL) {		// if L child is null...
		cout << "\tL child is NULL\n";
		LHeight = -1;					// L height is 0
	}
	else {
		cout << "\tL child is NOT NULL\n";
		LHeight = ptr->left->getHeight() + 1; // Otherwise get its height and add 1
	}
	if(ptr->right == NULL) {	// if R child is null...
		cout << "\tR child is NULL\n";
		RHeight = -1;				// R height is 0
	}
	else {
		cout << "\tR child is NOT NULL\n";
		RHeight = ptr->right->getHeight() + 1;	// Otherwise get its height and add 1
	}
	
	balance = RHeight - LHeight;
	cout << "The balance is: " << balance << endl;
	
	// if balance <= -2 (should only ever get to -2 never less)
	// check if LL or LR
	// LL: do a right rotation on ptr
	// LR: do a left on ptr->left, then a right on ptr
	if(balance < -1) {
		if(ptr->left->left == NULL) {		// if LL child is null...
			LLHeight = 0;					// LL height is 0
		}
		else {
			LLHeight = ptr->left->left->getHeight(); // Otherwise get its height
		}
		if(ptr->left->right == NULL) {	// if LR child is null...
			LRHeight = 0;				// LR height is 0
		}
		else {
			LRHeight = ptr->left->right->getHeight();	// Otherwise get its height
		}
		if(LRHeight > LLHeight) {	// if the R child of the L child is heavier
			cout << "LR case" << endl;
			// LR case: do a left on ptr->left, then a right on ptr
			rotateLeft(ptr->left);
			rotateRight(ptr);
		}
		else {
			// LL case: do a right rotation on ptr
			cout << "LL case" << endl;
			rotateRight(ptr);
		}
	}
	
	// if balance >= 2
	// check if RR or RL
	// RR: do a left rotation on ptr
	// RL: do a right on ptr->right, then a left on ptr
	else if(balance > 1) {
		if(ptr->right->right == NULL) {		// if RR child is null...
			RRHeight = 0;					// RR height is 0
		}
		else {
			RRHeight = ptr->right->right->getHeight(); // Otherwise get its height
		}
		if(ptr->right->left == NULL) {	// if RL child is null...
			RLHeight = 0;				// RL height is 0
		}
		else {
			RLHeight = ptr->right->left->getHeight();	// Otherwise get its height
		}
		if(RLHeight > RRHeight) {	// if the L child of the R child is heavier
			// RL case: do a right on ptr->right, then a left on ptr
			cout << "RL case" << endl;
			rotateRight(ptr->right);
			rotateLeft(ptr);
		}
		else {
			// RR case: do a left rotation on ptr
			cout << "RR case" << endl;
			rotateLeft(ptr);
		}
	}
	else {
		cout << "\tRebalancing not necessary\n";
	}
	
	return;
}

void AVL::updateHeight(Node*& ptr) {
	cout << "updating height\n";
	int leftHeight;						// declare two ints for the child heights
	int rightHeight;

	if(ptr->left == NULL && ptr->right == NULL) {		// if the node has no children
		cout << "\tthis node("<<ptr->data<<") has no children. Its height is 0\n";
		ptr->height = 0;
		return;
	}
	else if(ptr->left != NULL && ptr->right == NULL) {		// if there is a L child but no R child
		cout << "\tthis node("<<ptr->data<<") has a L child but no R child. Updating its L child\n";
		updateHeight(ptr->left);	// update its height of the child
		ptr->height = ptr->left->height + 1;	// set the current node's height to its child's + 1
		cout << "\tthis node("<<ptr->data<<") now has a height of " << ptr->height << endl;
	}
	else if(ptr->left == NULL && ptr->right != NULL) {		// if there is a R child but no L child
		cout << "\tthis node("<<ptr->data<<") has a R child but no L child. Updating its R child\n";
		updateHeight(ptr->right);	// update its height of the child
		ptr->height = ptr->right->height + 1;	// set the current node's height to its child's + 1
		cout << "\tthis node("<<ptr->data<<") now has a height of " << ptr->height << endl;
	}
	else if(ptr->left != NULL && ptr->right != NULL) {		// if there are children on both sides
		cout << "\tthis node("<<ptr->data<<") has children on both sides. Update both\n";
		updateHeight(ptr->left);		// update the L height
		updateHeight(ptr->right);		// update the R height
		ptr->height = max(ptr->left->height,ptr->right->height) + 1;		// set the current node's height to the higher of the children + 1
		cout << "\tthis node("<<ptr->data<<") now has a height of " << ptr->height << endl;
	}

/*
	if(ptr->left == NULL) {		// if L child is null...
		cout << "\tthis node("<<ptr->data<<") has no L child so L height is -1\n";
		leftHeight = -1;					// L height is -1 b/c it's the NULL
	}
	else {
		leftHeight = ptr->left->getHeight(); // Otherwise get its height
		cout << "\tthis node("<<ptr->data<<") has a L child so L height is " << leftHeight << endl;
	}
	if(ptr->right == NULL) {	// if R child is null...
		cout << "\tthis node("<<ptr->data<<") has no R child so R height is -1\n";
		rightHeight = -1;				// R height is -1 b/c it's the NULL
	}
	else {
		rightHeight = ptr->right->getHeight();	// Otherwise get its height
		cout << "\tthis node("<<ptr->data<<") has a R child so R height is " << rightHeight << endl;
	}
	int M = max(leftHeight,rightHeight);
	cout << "\tthe max of these two is " << M << endl;
	ptr->height = max(leftHeight,rightHeight) + 1;	// parent height is highest child + 1
	cout << "\t So this node's height is " << ptr->height << endl;
*/
}

void AVL::debug_helper(Node* ptr) {
	cout << "DEBUG\n";
	cout << "\t\tThis node contains " << ptr->data << endl;
	if(ptr->left != NULL && ptr->right != NULL) {
		cout << "\t\t\tIt has L & R children\n";
	}
	else if(ptr->left != NULL && ptr->right == NULL) {
		cout << "\t\t\tIt has a L child and no R child\n";
	}
	else if(ptr->left == NULL && ptr->right != NULL) {
		cout << "\t\t\tIt has a R child and no L child\n";
	}
	else {	//ptr->left == NULL && ptr->right == NULL
		cout << "\t\t\tIt has no children\n";
	}
	cout << "\t\t\tIts height is " << ptr->height << endl;
}
