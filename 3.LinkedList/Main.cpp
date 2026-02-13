#include <iostream>
#include "LinkedList/LinkedList.h"
#include <list>
#include <forward_list>

int main()
{
	LinkedList<int> list;

	std::forward_list<int> stdList;
	

	list.Insert(1);
	list.Insert(3);
	list.Insert(2);
	list.Insert(0);

	list.Print();

	list.Delete(2);
	list.Delete(0);

	std::cout << "삭제후출력\n";
	list.Print();

	std::cin.get();
}