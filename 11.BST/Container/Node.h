#pragma once

#include <iostream>
// 이진 트리에 사용할 노드 클래스

template<typename T>
class Node
{
	template<typename T>
	friend class BinarySearchTree;
public:
	Node(
		const T& data, 
		Node<T>* const parent = nullptr
	)
		: data(data), parent(parent)
	{

	}
private:
	T data = T();

	Node<T>* parent = nullptr;
	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
};