#ifndef AVL_DATA_TREE_H
#define AVL_DATA_TREE_H

#include <stdlib.h>
#include <stdio.h>
#include "DataTreeNode.h"


class DataAVL {
protected:

	void balanceInsertion(DataTreeNode* parent, int newBalance) {
		/*DataTreeNode* parent = inserted->parent;
		   int newBalance = 0;

		   if (inserted == parent->left)
		        --parent->balance;
		   else
		 ++parent->balance;
		 */
		while (parent) {
			parent->balance += newBalance;

			if (parent->balance == -2) {
				if (parent->left->balance == -1) {
					parent = rotateRight(parent);
				} else {
					parent = rotateLeftRight(parent);
				}
				break;
			} else if (parent->balance == 2) {
				if (parent->right->balance == 1) {
					parent = rotateLeft(parent);
				} else {
					parent = rotateRightLeft(parent);
				}
				break;
			}

			if (parent->parent) {
				if (parent->balance != 0) {
					if (parent == parent->parent->left)
						newBalance = -1;
					else
						newBalance = 1;
				} else {
					break;
				}
			}

			parent = parent->parent;
		}
	}


	void balanceDeletion(DataTreeNode* parent, int newBalance) {
		while (parent) {
			parent->balance += newBalance;

			if (parent->balance == -2) {
				if (parent->left->balance <= 0) {
					parent = rotateRight(parent);
				} else {
					parent = rotateLeftRight(parent);
				}
			} else if (parent->balance == 2) {
				if (parent->right->balance >= 0) {
					parent = rotateLeft(parent);
				} else {
					parent = rotateRightLeft(parent);
				}
			}

			if (parent->balance != 0) {
				break;
			} else if (parent->parent) {
				if (parent == parent->parent->left) {
					newBalance = 1;
				} else {
					newBalance = -1;
				}
			}

			parent = parent->parent;
		}
	}


	// right rotation function
	DataTreeNode* rotateRight(DataTreeNode* node) {
		// make copies for data rotation
		DataTreeNode *left = node->left;
		DataTreeNode *leftRight = left->right;
		DataTreeNode *parent = node->parent;

		// FUN STUFF (belive me)
		// overall parent becomes the parent of the left node
		left->parent = parent;
		// main node becomes right node of its left node
		left->right = node;
		// left node's right node becomes left node of the main node
		node->left = leftRight;
		// left node becomes the parent of the main node
		node->parent = left;


		if (leftRight) {
			leftRight->parent = node;
		}

		// if node->parent points to NULL, we must change our root
		if (parent == NULL)
			this->root = left;
		// if main node was its parent's left node
		else if (parent->left == node)
			parent->left = left;
		// if main node was its parent's right node
		else if (node == parent->right)
			parent->right = left;


		if (left->balance == 0) {
			left->balance = 1;
			node->balance = -1;
		} else {
			left->balance = 0;
			node->balance = 0;
		}
		// right totation makes left node less left heavy
		//++left->balance;
		// main node took left's stuff on the opposite side so it's
		// balance is flipped
		//node->balance = -left->balance;

		return left;
	}


	// left rotation function
	DataTreeNode* rotateLeft(DataTreeNode* node) {
		// make copies for data rotation
		DataTreeNode *right = node->right;
		DataTreeNode *rightLeft = right->left;
		DataTreeNode *parent = node->parent;

		// FUN STUFF (belive me)
		// overall parent becomes the parent of the right node
		right->parent = parent;
		// main node becomes left node of its right node
		right->left = node;
		// right node's left node becomes right node of the main node
		node->right = rightLeft;
		// right node becomes the parent of the main node
		node->parent = right;

		if (rightLeft) {
			rightLeft->parent = node;
		}

		// if node->parent points to NULL, we must change our root
		if (parent == NULL)
			this->root = right;
		// if main node was its parent's left node
		else if (node == parent->left)
			parent->left = right;
		// if main node was its parent's right node
		else if (node == parent->right)
			parent->right = right;


		if (right->balance == 0) {
			right->balance = -1;
			node->balance = 1;
		} else {
			right->balance = 0;
			node->balance = 0;
		}
		// right totation makes right node less right heavy
		//--right->balance;
		// main node took right's stuff on the opposite side so it's
		// balance is flipped
		//node->balance = -right->balance;

		return right;
	}


	DataTreeNode* rotateRightLeft(DataTreeNode* node) {
		// copies for easier handling
		DataTreeNode* right = node->right;
		DataTreeNode* rightLeft = right->left;
		DataTreeNode* parent = node->parent;
		DataTreeNode* rightLeftLeft = rightLeft->left;
		DataTreeNode* rightLeftRight = rightLeft->right;

		// overall parent becomes parent of the right->left node
		rightLeft->parent = parent;
		// right->left->left node becomes main node's right node
		node->right = rightLeftLeft;
		// right->left->right node becomes main node's left node
		right->left = rightLeftRight;
		// right node becomes right->left's right node
		rightLeft->right = right;
		// main node becomes right->left's left node
		rightLeft->left = node;
		// right->left node becomes the parent of the right node
		right->parent = rightLeft;
		// right->left node becomes the parent of the main node
		node->parent = rightLeft;

		// if right->left->left's node isn't NULL, main node becomes
		// it's parent
		if (rightLeftLeft) {
			rightLeftLeft->parent = node;
		}

		// if right->left->right's node isn't NULL, right node becomes
		// it's parent
		if (rightLeftRight) {
			rightLeftRight->parent = right;
		}

		// if node->parent points to NULL, we must change our root
		if (parent == NULL) {
			this->root = rightLeft;
		}
		// if main node was its parent's right node
		else if (node == parent->right) {
			parent->right = rightLeft;
		}
		// if main node was its parent's left node
		else {
			parent->left = rightLeft;
		}

		// if right->left node was left heavy
		if (rightLeft->balance <= -1) {
			node->balance = 0;
			right->balance = 1;
		}
		// if right->left node was balanced
		else if (rightLeft->balance == 0) {
			node->balance = 0;
			right->balance = 0;
		}
		// if right->left node was right heavy
		else if (rightLeft->balance >= 1) {
			node->balance = -1;
			right->balance = 0;
		}

		// rotation's done so our balance is surely 0 (don't quote me on
		// that)
		rightLeft->balance = 0;

		return rightLeft;
	}


	DataTreeNode* rotateLeftRight(DataTreeNode* node) {
		// copies for easier handling
		DataTreeNode* left = node->left;
		DataTreeNode* leftRight = left->right;
		DataTreeNode* parent = node->parent;
		DataTreeNode* leftRightRight = leftRight->right;
		DataTreeNode* leftRightLeft = leftRight->left;

		// overall parent becomes parent of the left->right node
		leftRight->parent = parent;
		// left->right->right node becomes main node's left node
		node->left = leftRightRight;
		// left->right->left node becomes main node's right node
		left->right = leftRightLeft;
		// left node becomes left->right's left node
		leftRight->left = left;
		// main node becomes left->right's right node
		leftRight->right = node;
		// left->right node becomes the parent of the left node
		left->parent = leftRight;
		// left->right node becomes the parent of the main node
		node->parent = leftRight;

		// if left->right->right's node isn't NULL, main node becomes
		// it's parent
		if (leftRightRight) {
			leftRightRight->parent = node;
		}

		// if left->right->left's node isn't NULL, left node becomes
		// it's parent
		if (leftRightLeft) {
			leftRightLeft->parent = left;
		}

		// if node->parent points to NULL, we must change our root
		if (parent == NULL) {
			this->root = leftRight;
		} else if (node == parent->left) {
			// if main node was its parent's left node
			parent->left = leftRight;
		} else {
			// if main node was its parent's right node
			parent->right = leftRight;
		}
		// if left->right node was right heavy
		if (leftRight->balance >= 1) {
			node->balance = 0;
			left->balance = -1;
		}
		// if left->right node was balanced
		else if (leftRight->balance == 0) {
			node->balance = 0;
			left->balance = 0;
		}
		// if left->right node was left heavy
		else if (leftRight->balance <= -1) {
			node->balance = 1;
			left->balance = 0;
		}

		// rotation's done so our balance is surely 0 (don't quote me on
		// that)
		leftRight->balance = 0;

		return leftRight;
	}


public:
	DataTreeNode *root;
	DataTreeNode *min;
	DataTreeNode *max;

	DataAVL() {
		this->root = NULL;
		this->min = NULL;
		this->max = NULL;
	}


	// inserts new data node to the tree
	void insert(DataTreeNode *newNode) {
		unsigned long int value = newNode->key;
		// =========
		// INSERTION
		// =========
		// if root is empty, make new root and job's done
		if (!this->root) {
			this->root = newNode;
			this->max = this->root;
			this->min = this->root;
		} else {
			DataTreeNode *tmp = this->root;

			// continue looping until new data is inserted
			while (true) {
				if (value < tmp->key) {
					if (tmp->left) tmp = tmp->left;
					else {
						tmp->left = newNode;
						tmp->left->parent = tmp;
						if (tmp->left->key < this->min->key)
							this->min = tmp->left;
						// left insert so balance is
						// decreasing
						balanceInsertion(tmp, -1);
						break;
					}
				} else if (value > tmp->key) {
					if (tmp->right) tmp = tmp->right;
					else {
						tmp->right = newNode;
						tmp->right->parent = tmp;
						if (tmp->right->key > this->max->key)
							this->max = tmp->right;
						// right insert so balance is
						// increasing
						balanceInsertion(tmp, 1);
						break;
					}
				}
				// We're done here!
			}
		}
	}


	DataTreeNode* popMin() {
		//DataTreeNode *tmp = this->root;
		DataTreeNode *tmp = this->min;

		// itareate until there's no more children to the left
		//while (tmp->left) {
		//	tmp = tmp->left;
		//}

		// remove DataNode with the lowest index number

		// if all DataNodes are gone

		DataTreeNode* right = tmp->right;
		if (tmp == this->root) {
			if (right) {
				this->root = right;
				this->min = right;
				this->max = right;
				right->parent = NULL;
			} else {
				this->root = NULL;
				this->min = NULL;
				this->max = NULL;
			}
		} else {
			if (right) {
				this->min = right;
				tmp->parent->left = right;
				right->parent = tmp->parent;
				balanceDeletion(right->parent, 1);
			} else {
				this->min = tmp->parent;
				balanceDeletion(tmp->parent, 1);
				tmp->parent->left = NULL;
			}
		}

		tmp->parent = NULL;
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->balance = 0;
		return tmp;
	}


	DataTreeNode* popMax() {
		//DataTreeNode *tmp = this->root;
		DataTreeNode *tmp = this->max;

		// itareate until there's no more children to the right

		//while (tmp->right != NULL) {
		//	tmp = tmp->right;
		//}

		// if all DataNodes are gone

		DataTreeNode* left = tmp->left;
		if (tmp == this->root) {
			if (left) {
				this->root = left;
				this->min = left;
				this->max = left;
				left->parent = NULL;
			} else {
				this->root = NULL;
				this->min = NULL;
				this->max = NULL;
			}
		} else {
			if (left) {
				this->max = left;
				tmp->parent->right = left;
				left->parent = tmp->parent;
				balanceDeletion(left->parent, -1);
			} else {
				this->max = tmp->parent;
				balanceDeletion(tmp->parent, -1);
				tmp->parent->right = NULL;
			}
		}

		return tmp;
	}


};


#endif
