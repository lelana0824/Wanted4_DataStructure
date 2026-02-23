#include <iostream>
#include "Container/BinarySearchTree.h"

int main()
{
	BinarySearchTree<int> tree;

	tree.InsertNode(10);
	tree.InsertNode(20);
	tree.InsertNode(5);
	tree.InsertNode(30);

	std::cin.get();
}