#pragma once

#include "Node.h"

template<typename T>
class BinarySearchTree
{
public:
	BinarySearchTree()
	{
	}

	~BinarySearchTree()
	{
		// todo: 트리 제거 함수 구현 후 호출.
	}

	// 삽입.
	// 규칙.
	// 0. 중복된 값 허용 안함.
	// 1. 루트 노드부터 비교 시작.
	// 1-1. 루트가 null이면 루트 생성.
	// 2. 추가할 값이 작으면 왼쪽에 저장.
	// 3. 추가할 값이 크면 오른쪽에 저장.
	bool InsertNode(const T& newData)
	{
		// 중복 여부 확인.
		Node<T>* outNode = nullptr;
		if (SearchNode(newData, outNode))
		{
			return false;
		}

		if (!root)
		{
			root = new Node<T>(newData);
			return true;
		}

		// 2/3을 처리하기 위해 재귀 함수 호출.
		root = InsertNodeRecursive(
			root, nullptr, newData
		);

		return true;
	}

	// 삭제.
	bool DeleteNode(const T& deleteData)
	{
		//  재귀함수 구현호출.
		return DeleteNodeRecursive(
			root,
			deleteData,
			root
		);
	}
	// 검색.
	bool SearchNode(const T& data, Node<T>*& outNode)
	{
		return SearchNodeRecursive(
			root,
			data,
			outNode
		);
	}

	// 순회.

private:
	// 재귀 함수.

	//  삽입 재귀 함수.
	Node<T>* InsertNodeRecursive(
		Node<T>* node,
		Node<T>* parent,
		const T& newData)
	{
		if (!node)
		{
			return new Node<T>(newData, parent);
		}

		if (node->data > newData)
		{
			node->left = InsertNodeRecursive(
				node->left, node, newData
			);
		}
		else
		{
			node->right = InsertNodeRecursive(
				node->right, node, newData
			);
		}

		return node;
	}

	// 검색 재귀 함수
	bool SearchNodeRecursive(
		Node<T>* node,
		const T& data,
		Node<T>*& outNode)
	{
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		// 찾았는지 확인
		if (node->data == data)
		{
			outNode = node;
			return true;
		}

		// 작은 경우 왼쪽으로.
		if (node->data > data)
		{
			return SearchNodeRecursive(node->left, data, outNode);
		}
		else
		{
			return SearchNodeRecursive(node->right, data, outNode);
		}
	}
	
	//삭제 재귀 함수
	bool DeleteNodeRecursive(
		Node<T>* node,
		const T& deleteData,
		Node<T>*& outNode
	)
	{
		if (!node)
		{
			outNode = nullptr;
			return false;
		}

		if (node->data > deleteData)
		{
			return DeleteNodeRecursive(
				node->left, deleteData, node->left
			);
		}

		else if (node->data < deleteData)
		{
			return DeleteNodeRecursive(
				node->right, deleteData, node->right
			);
		}

		else {
			// 경우의 1 - 자식이 없는 경우
			// l,r 모두 0일 경우
			if (!node->left && !node->right)
			{
				delete node;
				outNode = nullptr;
				return true;
			}

			// 경우의 수2 - 자식 노드 둘 다 있는 경우.
			if (node->left && node->right)
			{
				// 여기에서는 2가지 방법이 가능.
				// 1. 왼쪽 하위 트리에서 가장 큰 값의 노드를 대체.
				// 2. 오른쪽 하위 트리에서 가장 작은 값의 노드를 대체.
				// 하위 노드에서 최소값 찾는 함수 호출.
				node->data = SearchMinValue(node->right)->data;

				// 오른쪽 하위 트리에서 가장 작은 값의 노드를 삭제 및 정리
				DeleteNodeRecursive(node->right, node->data, node->right);
				
				return true;
			}

			// 경우의 수3 - 둘 중에 하나만 있는 경우.
			else
			{
				// 왼쪽 자손이 null -> 오른쪽 자손만 있는 경우
				if (!node->left)
				{
					// 오른쪽 자손 정보를 임시 저장.
					Node<T>* right = node->right;

					// 오른쪽 자손의 부모를 삭제할 노드의 부모로 설정.
					right->parent = node->parent;

					// 노드 제거
					delete node;

					// 오른쪽 자손 정보 설정.
					outNode = right;
					return true;
				}
				else if (!node->right)
				{
					Node<T>* left = node->left;

					left->parent = node->parent;

					delete node;

					outNode = left;
					return true;
				}
			}

			outNode = nullptr;
			return false;
		}
	}

	// 최소값 검색 함수.
	// node: 검색을 시작하는 노드.
	Node<T>* SearchMinValue(Node<T>* node)
	{
		while (node->left)
		{
			// 왼쪽 하위 노드로 이동.
			node = node->left;
		}

		return node;
	}

	// 파괴 함수.

private:
	Node<T>* root = nullptr;
};