#include <stdio.h>
#include "Tree.h"
#include <limits.h>

#define XDD 1431655764

void collatz(unsigned long int &value) {
	if (value % 2 == 0) value /= 2;
	else if(value > XDD) value = 0;
	else value = (value * 3) + 1;
}


int main(int argc, char const *argv[]) {

	AVL drzewo;

	int n;
	scanf(" %d", &n);

	//allocating memory
	//unsigned long int tmp;
	unsigned long int *tablica = new unsigned long int[n];

	//reading numbers
	for (unsigned int i = 0; i < n; ++i) {
		scanf(" %lu", &tablica[i]);
		DataTreeNode *temp = new DataTreeNode(i);
		if (tablica[i] != 1)
			drzewo.insert(tablica[i], temp);
	}

	//reading number of commands
	int q;
	scanf(" %d", &q);
	int k;
	char c;

 	bool stop = false;
	DataTreeNode *node;
	unsigned int index;

	for (int i = 0; i < q; ++i) {
		scanf(" %d %c", &k, &c);
		if (c == 's') {
			for (int j = 0; j < k; ++j) {
				node = drzewo.popMin();
				index = node->key;

				collatz(tablica[index]);

				if(tablica[index] > 1)
					drzewo.insert(tablica[index], node);
				if (drzewo.root == NULL) {
					stop = true;
					break;
				}
			}
		} else   {
			for (int j = 0; j < k; ++j) {
				node = drzewo.popMax();
				index = node->key;
				collatz(tablica[index]);

				if(tablica[index] > 1)
					drzewo.insert(tablica[index], node);
				if (drzewo.root == NULL) {
					stop = true;
					break;
				}
			}
		}
		if (stop) break;
	}

	for (int i = 0; i < n; ++i) {
		if (tablica[i] != 0)
			printf("%lu ", tablica[i]);
		else printf("m ");
	}
	printf("\n");
	//drzewo->check(drzewo->getRoot());
	return 0;
}
