#ifndef AVL_H_
#define AVL_H_

#include "AVLInterface.h"
#include "Node.h"

using namespace std;

class AVL : public AVLInterface {
public:
	AVL() {};
	~AVL() {};
	Node* getRootNode() const;
	bool add(int data);
	bool remove(int data);
	void clear();

};

#endif