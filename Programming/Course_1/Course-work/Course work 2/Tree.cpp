#include <iostream>
#include <fstream>
#include <queue>
#include "Tree.h"

Tree::~Tree()
{
	erase(root);
}

void Tree::insert(int num)
{
	Node* node;
	if (size == 0)
	{
		root = new Node;
		root->data = num;
		root->left = root->right = NULL;
		node = root;
		size++;
		return;
	}

	Node* temp = new Node;
	temp->left = NULL;
	temp->data = num;
	temp->right = NULL;

	node = root;

	while (node && node->data != num)
	{
		if (num < node->data && node->left == NULL)
		{
			node->left = temp;
			size++;
			return;
		}
		if (node->data < num && node->right == NULL)
		{
			node->right = temp;
			size++;
			return;
		}
		if (num < node->data)
			node = node->left;
		else
			node = node->right;
	}
}

int Tree::getSize()
{
	return size;
}

void Tree::print(bool isConsoleOutput)
{
	if (isConsoleOutput)
	{
		std::cout << '\n';
		printTree(root, nullptr, false, std::cout);
		return;
	}

	std::ofstream fout("Tree.txt");

	printTree(root, nullptr, false, fout);

	fout << "\nTree size: " << getSize() << " [" << min() << "; " << max() << "]\n";

	fout.close();
}

int Tree::min()
{
	Node* node = root;
	while (node->left)
		node = node->left;

	return node->data;
}

int Tree::max()
{
	Node* node = root;
	while (node->right)
		node = node->right;

	return node->data;
}

bool Tree::find(int num)
{
	Node* node = root;
	while (node && node->data != num)
	{
		if (node->data > num)
			node = node->left;
		else
			node = node->right;
	}
	return node != NULL;
}

void Tree::del(int num)
{
	Node* node = root;
	Node* parent = NULL;
	while (node && node->data != num)
	{
		parent = node;
		if (node->data > num)
			node = node->left;
		else
			node = node->right;
	}
	if (!node)
		return;
	if (node->left == NULL)
	{
		if(node == root)
			root = root->right;
		if (parent && parent->left == node)
			parent->left = node->right;
		if (parent && parent->right == node)
			parent->right = node->right;
		--size;
		delete node;
		return;
	}
	if (node->right == NULL)
	{
		if (node == root)
			root = root->left;
		if (parent && parent->left == node)
			parent->left = node->left;
		if (parent && parent->right == node)
			parent->right = node->left;
		--size;
		delete node;
		return;
	}

	Node* replace = node->left;

	while (replace->right)
		replace = replace->right;

	int replace_value = replace->data;

	del(replace_value);

	node->data = replace_value;
}

void Tree::straight()
{
	preOrderTravers(root);
}

void Tree::symmetrical()
{
	inOrderTravers(root);
}

void Tree::reverse()
{
	postOrderTravers(root);
}

void Tree::breadth()
{
	breadthFirstTravers(root);
}

void Tree::showTrunks(Trunk* tr, std::ostream& out)
{
	if (tr == nullptr) {
		return;
	}

	showTrunks(tr->prev, out);
	out << tr->str;

}
void Tree::printTree(Node* root, Trunk* prev, bool isLeft, std::ostream& out)
{
	if (root == nullptr) 
		return;

	std::string prev_str = "    ";
	Trunk* trunk = new Trunk(prev, prev_str);

	printTree(root->right, trunk, true, out);

	if (!prev) 
		trunk->str = "-->";
	else if (isLeft)
	{
		trunk->str = ".-->";
		prev_str = "   |";
	}
	else 
	{
		trunk->str = "`-->";
		prev->str = prev_str;
	}

	showTrunks(trunk, out);
	out << " " << root->data << std::endl;

	if (prev) 
		prev->str = prev_str;
	trunk->str = "   |";

	printTree(root->left, trunk, false, out);
}
void Tree::erase(Node* node)
{
	if (node && getSize())
	{
		erase(node->left);
		erase(node->right);
		delete node;
		size--;
	}
}
void Tree::preOrderTravers(Node* root) {
	if (root) {
		std::cout << root->data << " ";
		preOrderTravers(root->left);
		preOrderTravers(root->right);
	}
}
void Tree::inOrderTravers(Node* root) {
	if (root) {
		inOrderTravers(root->left);
		std::cout << root->data << " ";
		inOrderTravers(root->right);
	}
}
void Tree::postOrderTravers(Node* root) {
	if (root) {
		postOrderTravers(root->left);
		postOrderTravers(root->right);
		std::cout << root->data << " ";
	}
}
void Tree::breadthFirstTravers(Node* root)
{
	std::queue<Node*> q;

	if (!root) {
		return;
	}
	for (q.push(root); !q.empty(); q.pop()) {
		const Node* const temp_node = q.front();
		std::cout << temp_node->data << " ";

		if (temp_node->left) {
			q.push(temp_node->left);
		}
		if (temp_node->right) {
			q.push(temp_node->right);
		}
	}
}