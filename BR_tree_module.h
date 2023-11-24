#pragma once
#include "Node.h"
#include <Windows.h>

template <typename T>
class BR_tree_module {
public:
	Node<T>* root = NULL;
	int treeSizeHeight = 0;
	
	friend ostream& operator<<(ostream& os, BR_tree_module<T>* tree) {
		os << "Lokacja wezla root w pamieci: " << &tree->root << "\n";
		os << "Wysokosc drzewa: " << tree->treeSizeHeight << "\n\n";
		return os;
	}

	Node<T>* createNode(int id, T* object) {
		Node<T>* temp = new Node<T>;
		temp->setId(id);
		temp->setObject(object);
		return temp;
	}

	bool insertNode(int id, T* object) {
		Node<T>* tmp = createNode(id, object);
		Node<T>* root_temp = root;
		Node<T>* tmp2 = NULL;
		while (root_temp != NULL) {
			tmp2 = root_temp;
			if (tmp->getId() < root_temp->getId()) {
				root_temp = root_temp->getFamily(1);
			}
			else if(tmp->getId() > root_temp->getId()) {
				root_temp = root_temp->getFamily(3);
			}
			else {
				//cerr << "Id already used\n";
				//fprintf(stderr, "Id already used\n");
				delete(tmp);
				return 0;
			}
		}
		tmp->setFamily(2, tmp2);
		if (tmp2 == NULL) {
			root = tmp; 
		}
		else if (tmp->getId() < tmp2->getId()) {
			tmp2->setFamily(1, tmp);
		}
		else {
			tmp2->setFamily(3, tmp);
		}
		insertFixRotation(tmp);
		treeSizeHeight = treeHeight();
		return 1;
	}

	void insertFixRotation(Node<T>* node) {
		while ((node->getFamily(2) != NULL) && (node->getFamily(2)->getColor())) {
			if (node->getFamily(2) == node->getGrandparent()->getFamily(1)) {
				Node<T>* temp = node->getGrandparent()->getFamily(3);
				if ((temp != NULL) && (temp->getColor())) {
					node->getFamily(2)->setColor(0);
					temp->setColor(0);
					node->getGrandparent()->setColor(1);
					node = node->getGrandparent();
				}
				else {
					if (node == (node->getFamily(2)->getFamily(3))) {
						node = node->getFamily(2);
						rotateLeft(node);
					}
					node->getFamily(2)->setColor(0);
					node->getGrandparent()->setColor(1);
					rotateRight(node->getGrandparent());
				}
			}
			else {
				Node<T>* temp = node->getGrandparent()->getFamily(1);
				if ((temp != NULL) && temp->getColor()) {
					node->getFamily(2)->setColor(0);
					temp->setColor(0);
					node->getGrandparent()->setColor(1);
					node = node->getGrandparent();
				}
				else {
					if (node == node->getFamily(2)->getFamily(1)) {
						node = node->getFamily(2);
						rotateRight(node);
					}
					node->getFamily(2)->setColor(0);
					node->getFamily(2)->getFamily(2)->setColor(1);
					rotateLeft(node->getGrandparent());
				}
			}
		}
		this->root->setColor(0);
	}
	
	void rotateLeft(Node<T>* node) {
		Node<T>* temp = node->getFamily(3);
		node->setFamily(3, temp->getFamily(1));
		if (temp->getFamily(1) != NULL) {
			temp->getFamily(1)->setFamily(2, node);
		}
		temp->setFamily(2, node->getFamily(2));
		if (node->getFamily(2) == NULL) {
			this->root = temp;
		}
		else if (node == node->getFamily(2)->getFamily(1)) {
			node->getFamily(2)->setFamily(1, temp);
		}
		else {
			node->getFamily(2)->setFamily(3, temp);
		}
		temp->setFamily(1, node);
		node->setFamily(2, temp);
		this->treeSizeHeight = treeHeight();
	}

	void rotateRight(Node<T>* node) {
		Node<T>* temp = node->getFamily(1);
		node->setFamily(1, temp->getFamily(3));
		if (temp->getFamily(3) != NULL) {
			temp->getFamily(3)->setFamily(2, node);
		}
		temp->setFamily(2, node->getFamily(2));
		if (node->getFamily(2) == NULL) {
			this->root = temp;
		}
		else if (node == node->getFamily(2)->getFamily(1)) {
			node->getFamily(2)->setFamily(1, temp);
		}
		else {
			node->getFamily(2)->setFamily(3, temp);
		}
		temp->setFamily(3, node);
		node->setFamily(2, temp);
		this->treeSizeHeight = treeHeight();
	}

	void nukeTree(Node<T>* node = NULL) {
		if (node == NULL) {
			deleteTree(root);
		}
		else {
			deleteTree(node);
		}
	}

	void deleteTree(Node<T>* node) {
		if (node == NULL) {
			return;
		}
		deleteTree(node->getFamily(1));
		deleteTree(node->getFamily(3));
		delete(node);
		root = NULL;
	}

	void printBST(Node<T>* node = NULL) {
		if (node == NULL) {
			print(root);
		}
		else {
			print(node);
		}
	}

	void print(Node<T>* node)
	{
		if (node == NULL)
			return;
		else {
			print(node->getFamily(1));
			cout << node << "\n";
			print(node->getFamily(3));
		}
	}

	void Inorder(Node<T>* node = NULL) {
		if (node == NULL) {
			In_Traversal(root);
		}
		else {
			In_Traversal(node);
		}
	}

	void In_Traversal(Node<T>* node)
	{
		if (node == NULL)
			return;
		else {
			In_Traversal(node->getFamily(1));
			cout << "\x1b[31m" << node->getId() << "\033[0m";
			if (node != maxVal(root)) {
				cout << " -> ";
			}
			In_Traversal(node->getFamily(3));
		}
	}

	void Preorder(Node<T>* node = NULL) {
		if (node == NULL) {
			Pre_Traversal(root);
		}
		else {
			Pre_Traversal(node);
		}
	}

	void Pre_Traversal(Node<T>* node)
	{
		if (node == NULL)
			return;
		else {
			cout << "\x1b[31m" << node->getId() << "\033[0m";
			if (node != maxVal(root)) {
				cout << " -> ";
			}
			Pre_Traversal(node->getFamily(1));
			Pre_Traversal(node->getFamily(3));
		}
	}

	Node<T>* iterativeSearch(Node<T>* node, int key)
	{
		while (node != NULL) {
			if (key > node->getId()) {
				node = node->getFamily(3);
			}
			else if (key < node->getId()) {
				node = node->getFamily(1);
			}
			else {
				return node;
			}
		}
		return NULL;
	}

	Node<T>* minVal(Node<T>* node) {
		Node<T>* temp = node;
		while ((temp && temp->getFamily(1)) != NULL) {
			temp = temp->getFamily(1);
		}
		return temp;
	}
	Node<T>* maxVal(Node<T>* node) {
		Node<T>* temp = node;
		while ((temp && temp->getFamily(3)) != NULL) {
			temp = temp->getFamily(3);
		}
		return temp;
	}

	int treeHeight(Node<T>* node = NULL) {
		if (node == NULL) {
			return height(root);
		}
		else {
			return height(node);
		}

	}

	int height(Node<T>* node) {
		if (node == NULL) {
			return 0;
		}
		int lheight = height(node->getFamily(1));
		int rheight = height(node->getFamily(3));
		return max(lheight, rheight) + 1;
	}
};