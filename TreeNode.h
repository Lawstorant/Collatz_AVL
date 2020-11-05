#ifndef TREE_NODE_H
#define TREE_NODE_H

#include "DataTree.h"

class TreeNode {
public:
	TreeNode *left;         // left node
	TreeNode *right;        // right node
	TreeNode *parent;       // parent node
	unsigned int key;  // node's key
	DataAVL *data;         // list of data nodes
	int balance;            // node's balance

	TreeNode() {
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->data = new DataAVL();
		this->balance = 0;
	}


	TreeNode(unsigned long int &value, DataTreeNode *newNode) {
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->data = new DataAVL();
		this->data->insert(newNode);
		this->key = value;
		this->balance = 0;
	}


};

#endif
