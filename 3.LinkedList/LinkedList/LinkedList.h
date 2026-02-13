#pragma once

#include "Node.h"
template<typename T>
class LinkedList
{
	using NodeType = Node<T>*;

public:
	LinkedList()
		: head(nullptr), count(0)
	{
	}

private:
	// Çìµå
	NodeType head = nullptr;

	int count = 0;


};