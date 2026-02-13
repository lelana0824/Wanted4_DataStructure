#pragma once

#include "Node.h"
#include <iostream>

template<typename T>
class LinkedList
{
	using NodeType = Node<T>*;

public:
	LinkedList(): first(new Node<T>()),
		last(new Node<T>()),
		count(0)
	{
		// 처음과 마지막 노드 연결
		first->next = last;
		last->prev = first;
	}
	~LinkedList()
	{
		
		Clear();

		delete first;
		first = nullptr;

		delete last;
		last = nullptr;
	}

	void Clear()
	{
		NodeType current = first->next;

		while (current && current != last)
		{
			NodeType next = current->next;
			delete current;
			current = next;
		}

		count = 0;

		first->next = last;
		last->prev = first;
	}

	NodeType Find(const T& data)
	{
		NodeType current = first->next;

		while (current && current != last)
		{
			if (current->data == data)
			{
				return current;
			}

			current = current->next;
		}
		
		std::cout << "Can`t find the data.\n";
		return nullptr;
	}

	NodeType FindReverse(const T& data)
	{
		NodeType current = last->prev;

		while (current && current != first)
		{
			if (current->data == data)
			{
				return current;
			}

			current = current->prev;
		}

		std::cout << "Can`t find the data.\n";
		return nullptr;
	}

	void InsertFirst(const T& data)
	{
		NodeType newNode = new Node<T>();
		newNode->data = data;

		// 포인터 정리.
		NodeType next = first->next;

		newNode->next = next;
		next->prev = newNode;

		newNode->prev = first;
		first->next = newNode;

		count++;
	}

	void InsertLast(const T& data)
	{
		NodeType newNode = new Node<T>();
		newNode->data = data;

		NodeType temp = last->prev;

		newNode->prev = temp;
		temp->next = newNode;

		newNode->next = last;
		last->prev = newNode;

		count++;
	}

	void Delete(const T& data)
	{
		if (count == 0) return;

		NodeType t = Find(data);

		if (!t) return;

		NodeType prev = t->prev;
		NodeType next = t->next;
		prev->next = next;
		next->prev = prev;

		delete t;
		t = nullptr;

		count--;
	}

	void Print()
	{
		NodeType current = first->next;

		std::cout << "List Item count: "
			<< count << "\n";

		while (current != last)
		{
			std::cout << current->data
				<< "\n";
			current = current->next;
		}
	}

private:
	NodeType first = nullptr;
	NodeType last = nullptr;
	
	int count = 0;
};