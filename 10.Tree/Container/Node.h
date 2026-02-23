#pragma once
#include <vector>
template<typename T>
void SafeDelete(T*& t)
{
	if (t)
	{
		delete t;
		t = nullptr;
	}
}

template<typename T>
class Node
{
public:
	Node()
		: data()
	{
	}

	Node(const T& data) : data(data)
	{
	}

	~Node()
	{
		data = T();
		parent = nullptr;
		children.clear();
	}

	
public:
	// 값을 전달해 자손 추가하는 함수
	// Wrapper함수 -> 다른 함수를 외부에서 감싸는 형태.
	void AddChild(const T& data)
	{
		AddChild(new Node<T>(data));
	}
	// 노드 직접 전달해 자손 추가하는
	void AddChild(Node<T>* newChild)
	{
		newChild->SetParent(this);
		children.emplace_back(newChild);
	}

	void RemoveChild(Node<T>* child)
	{
		// 하위노드까지 순회하면서 노드 검색 후 삭제.
		RemoveChildRecursive(child);
	}

	inline T GetData() const { return data; }
	inline std::vector<Node<T>*>& GetChildren() { return children; }
	inline Node<T>* GetParent() const { return parent; }
	inline void SetParent(Node<T>* newParent) { parent = newParent; }

private:
	// 재귀함수 -> 자기 자신을 호출하는 함수.
	// 언제 사용? -> 자기 자신을 호출하면서 데이터의 범위가 줄어들때
	// 주의사항! - 탈출 조건이 항상 있어야 함.
	// 주의사항! - 스택 오버플로우 위험 (콜스택 사용하기 때문)
	void RemoveChildRecursive(Node<T>* child)
	{
		// 탈출조건
		if (!child) return;

		// 하위노드 확인
		std::vector<Node<T>*>& children = child->GetChildren();

		// 경우의 수 나누기
		// 자손 노드가 없는 경우
		if (!children.size())
		{
			// 부모 노드의 자손 목록 가져오기
			auto& parentVector = child->GetParent()->GetChildren();
			
			// 자손 목록에서 삭제할 노드 검색
			auto childIt = std::find(
				parentVector.begin(),
				parentVector.end(),
				child
			);

			// 자손 목록에서 노드 검색에 성공했으면 해당 노드 제거
			if (childIt != parentVector.end())
			{
				parentVector.erase(childIt);
			}

			SafeDelete(child);
			return;
		}

		// 자손 노드가 있는 경우
		while (children.size() > 0)
		{
			// 자손을 순회하면서 재귀 삭제 함수 호출.
			RemoveChildRecursive(children[0]);
		}

		// 마무리.
		auto& parentVector = child->GetParent()->GetChildren();
		// 자손 목록에서 삭제할 노드 검색
		auto childIt = std::find(
			parentVector.begin(),
			parentVector.end(),
			child
		);

		// 자손 목록에서 노드 검색에 성공했으면 해당 노드 제거
		if (childIt != parentVector.end())
		{
			parentVector.erase(childIt);
		}

		SafeDelete(child);
	}
private:
	T data;

	Node<T>* parent = nullptr;
	std::vector<Node<T>*> children;
};