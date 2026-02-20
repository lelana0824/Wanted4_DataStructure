#include <iostream>
#include "Container/HashTable.h"

int main()
{
	HashTable table;

	table.Add("Ronnie", "010-1234-1234");
	table.Add("Ronnie", "010-1234-1111");
	table.Add("AAAA", "010-1234-2222");
	table.Add("BBBB", "010-1234-3333");
	table.Add("CCCC", "010-1234-4444");

	table.Print();

	Pair<std::string, std::string> outValue;
	if (table.Find("AAAA", outValue))
	{
		std::cout << "검색성공: \n";
		std::cout << outValue.key << "\n";
		std::cout << outValue.value << "\n";
	}

	table.Delete("AAAA");

	table.Print();

	std::cout << "검색성공: \n";
	std::cout << outValue.key << "\n";
	std::cout << outValue.value << "\n";

	std::cin.get();
}