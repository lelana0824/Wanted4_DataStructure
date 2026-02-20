#pragma once

#include "Node.h"
#include <vector>
#include <iostream>

template<typename T>
class Tree
{
public:
	Tree(const T& data)
	{
		root = new Node<T>(data);
	}
	~Tree()
	{
		//todo: 자손노드 모두 제거하는 함수 구현 호 호출.

	}
	
	// 부모 노드의 값을 사용해 해당 부모에 자손 추가
	bool AddChild(const T& parentData, const T& childData)
	{
		Node<T>* outParent = nullptr;
		bool result = 
			FindRecursive(parentData, root, outParent);
		
		if (result)
		{
			outParent->AddChild(childData);
			return true;
		}

		return false;
	}

	bool Find(const T& data, Node<T>*& outNode)
	{
		return FindRecursive(data, root, outNode);
	}

private:
	// data: 검색하려는 값.
	// node: 현재 검색하는 노드
	// outNode: 검색에 성공시 반환할 노드
	// 함수의 반환값: 검색의 성공실패여부.
	bool FindRecursive(const T& data, Node<T>* node, Node<T>*& outNode)
	{
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		if (node->GetData() == data)
		{
			outNode = node;
			return true;
		}

		std::vector<Node<T>*> & children = node->GetChildren();
		const int length = static_cast<int>(children.size());

		for (int i = 0; i < length; i++)
		{
			bool result = FindRecursive(data, children[i], outNode);
			if (result)
			{
				return true;
			}
		}

		// 검색실패
		outNode = nullptr;
		return false;

	}

private:
	Node<T>* root = nullptr;
};