#include <iostream>
#include "Container/BinarySearchTree.h"

int main()
{
	BinarySearchTree<int> tree;

	tree.InsertNode(20);
	tree.InsertNode(10);
	tree.InsertNode(5);
	tree.InsertNode(30);
	tree.InsertNode(35);
	tree.InsertNode(8);

	// ªË¡¶
	tree.DeleteNode(30);
	tree.DeleteNode(10);
	tree.DeleteNode(8);

	
	std::cin.get();
}