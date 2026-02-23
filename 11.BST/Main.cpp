#include <iostream>
#include "Container/BinarySearchTree.h"

class Test
{
public:
	Test(const int i) : data(i)
	{

	}

private:
	int data = 0;

};

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
	tree.DeleteNode(20);


	std::cin.get();
}