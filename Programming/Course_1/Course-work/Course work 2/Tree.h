#pragma once
#include <iostream>

struct Node
{
	int data;
	Node* left, * right;
};

struct Trunk
{
	Trunk* prev;
	std::string str;

	Trunk(Trunk* prev, std::string str)
	{
		this->prev = prev;
		this->str = str;
	}
};

class Tree
{
private:
	int   size;
	Node* root;

	void showTrunks(Trunk*, std::ostream&);
	void printTree(Node*, Trunk*, bool, std::ostream&);
	void erase(Node*);
	void preOrderTravers(Node*);
	void inOrderTravers(Node*);
	void postOrderTravers(Node*);
	void breadthFirstTravers(Node*);
public:
	Tree() : size(0), root(NULL) {};

	~Tree();

	void insert(int);

	int getSize();

	void print(bool = true);

	int min();

	int max();

	bool find(int);

	void del(int);

	void straight();

	void symmetrical();

	void reverse();

	void breadth();
};