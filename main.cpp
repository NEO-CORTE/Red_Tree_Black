#include <iostream>
#include <Windows.h>
#include "BR_tree_module.h"

int main() {
	BR_tree_module<int>* tree = new BR_tree_module<int>;
	srand(time(NULL));
	
	//tree->insertNode(50, new int(50));
	//tree->insertNode(10, new int(0));
	//tree->insertNode(5, new int(3));
	//tree->insertNode(15, new int(4));
	//tree->insertNode(15, new int(2));
	//tree->insertNode(50, new int(11));
	//tree->insertNode(65, new int(9));
	//tree->insertNode(100, new int(1));

	for (int i = 0; i < 10000; i++) {
		tree->insertNode(rand() % 1000, new int(i));
	}

	cout << tree->root;
	//tree->printBST();
	tree->Inorder();
	cout << "\n" << tree;
	tree->nukeTree();
}