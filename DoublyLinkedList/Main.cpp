#include <iostream>
#include "LinkedList/LinkedList.h"

int main()
{
	LinkedList<int> list;

	list.InsertFirst(1);
	list.InsertFirst(2);
	list.InsertFirst(4);
	list.InsertFirst(3);

	list.Print();

	std::cin.get();
}