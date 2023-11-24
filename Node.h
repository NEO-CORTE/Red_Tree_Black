#pragma once
#include <string>
#include <iostream>

using namespace std;
template <typename T>
class Node {
	int id = 0;
	bool color = 1;
	Node* left = NULL;
	Node* parent = NULL;
	Node* right = NULL;
	T* object = NULL;

public:

	// getId
	int getId() {
		return this->id;
	}

	// setId
	void setId(int id) {
		this->id = id;
	}

	// 0 - black, 1 - red
	bool getColor() {
		return this->color;
	}

	// 0 - black, 1 - red
	void setColor(bool color) {
		this->color = color;
	}


	// Object of type T
	void setObject(T* object) {
		this->object = object;
	}

	// getObject
	T* getObject() {
		return this->object;
	}

	// 1 - left, 2 - parent, 3 - right
	Node* getFamily(int option) {
		switch (option) {
		case 1:
			return left;
		case 2:
			return parent;
		case 3:
			return right;
		default:
			return NULL;
		}
	}

	// 1 - left, 2 - parent, 3 - right
	void setFamily(int option, Node* node) {
		switch (option) {
		case 1:
			left = node;
			break;
		case 2:
			parent = node;
			break;
		case 3:
			right = node;
			break;
		default:
			return;
		}
	}

	// getGrandparent
	Node* getGrandparent() {
		return this->getFamily(2)->getFamily(2);
	}

	~Node() {
		delete(object);
	}

	friend ostream& operator<<(ostream& os, Node* node) {
		os << "[Color: ";
		node->color ? os << "\x1b[31;47m  red  \t" : os << "\x1b[30;47m black \t";
		os << "\033[0mKey:\033[0;35m\t" << node->id << "\033[0m\tleft:\t\033[1;32m";
		if (node->left != NULL) {
			os << node->left->id;
			os << "\033[0m\t";
		}
		else {
			os << "NULL";
			os << "\033[0m\t";
		}
		os << " parent:\t\033[0;31m";
		if (node->parent != NULL) {
			os << node->parent->id;
			os << "\033[0m\t";
		}
		else {
			os << "NULL";
			os << "\033[0m\t";
		}
		os << " right:\t\033[0;36m";
		if (node->right != NULL) {
			os << node->right->id;
			os << "\033[0m\t";
		}
		else {
			os << "NULL";
			os << "\033[0m\t";
		}
		os << "\033[0m\t";
		os << " object:\t\u001b[32m";
		if (node->object != NULL) {
			os << *node->object;
			os << "\033[0m\t";
		}
		else {
			os << "NULL";
			os << "\033[0m\t";
		}
		os << "\033[0m]\t";
		os << "\n";
		return os;
	}
};