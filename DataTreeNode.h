#ifndef DATA_TREE_NODE_H
#define DATA_TREE_NODE_H

#include <stddef.h>

class DataTreeNode {
public:
	DataTreeNode *left;         // left node
	DataTreeNode *right;        // right node
	DataTreeNode *parent;       // parent node
	unsigned int key;  // node's key
	int balance;            // node's balance

	DataTreeNode() {
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->balance = 0;
	}


	DataTreeNode(unsigned long int value) {
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->key = value;
		this->balance = 0;
	}


};

#endif
