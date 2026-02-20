#include "Container/Tree.h"

int main()
{
	Tree<int> tree(10);
	tree.AddChild(10, 9);
	tree.AddChild(10, 8);
	tree.AddChild(9, 7);
	tree.AddChild(9, 6);

	Node<int>* outNode = nullptr;

	if (tree.Find(6, outNode))
	{
		int number2 = 30;
	}

	
	// 전위 순회 테스트
	tree.PreorderTraversal();

	int number = 19;
}