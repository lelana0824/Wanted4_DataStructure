#pragma once

#include "Node.h"

#include <iostream>

template<typename T>
class LinkedList
{
	using NodeType = Node<T>*;

public:
	LinkedList()
		: head(nullptr), count(0)
	{
	}
	~LinkedList()
	{
		NodeType current = head;
		NodeType next = nullptr;

		while (current)
		{
			next = current->next;

			delete current;

			current = next;
		}

		head = nullptr;
		count = 0;
	}

	void Insert(const T& data)
	{
		NodeType newNode = new Node<T>(data);

		// 노드 삽입할 위치 확인

		// 헤드가 빈 상태인지 확인.
		if (!head)
		{
			head = newNode;
		}
		else
		{
			// 자리 검색을 위한 변수.
			NodeType current = head;
			NodeType trail = nullptr;

			while (current)
			{
				if (current->data >= data)
				{
					break;
				}


				trail = current;
				current = current->next;
			}

			// 검색한 위치가 헤드인 경우
			if (current == head)
			{
				// newNode를 헤드로 전환
				newNode->next = head;
				head = newNode;
			}
			else
			{
				trail->next = newNode;
				newNode->next = current;
			}
		}

		count++;
	}

	void Delete(const T& data)
	{
		// 예외처리
		if (!head)
		{
			std::cout << "List is empty";
			return;
		}

		NodeType current = head;
		NodeType trail = nullptr;

		while (current)
		{
			if (current->data == data)
			{
				break;
			}

			trail = current;
			current = current->next;
		}

		if (!current)
		{
			std::cout << "Failed to find the node\n";
			return;
		}

		// 삭제할 노드가 헤드인 경우
		if (head == current)
		{
			head = head->next;
		}
		else
		{
			trail->next = current->next;
		}

		delete current;
		--count;
	}


	void Print()
	{
		NodeType current = head;

		while (current)
		{
			std::cout << current->data << "\n";
			current = current->next;
		}
	}
private:
	// 헤드
	NodeType head = nullptr;
	int count = 0;


};