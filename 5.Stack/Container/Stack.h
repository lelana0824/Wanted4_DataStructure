#pragma once

// 스택 자료구조 클래스
template <typename T, int capacity = 10>
class Stack
{
public:
	Stack()
		:top(0)
	{
	}

	bool Push(const T& value)
	{
		if (IsFull()) return false;

		data[top++] = value;

		return true;
	}

	// 고민해볼 사항
	// 1: 반환 값을 불값으로 할지
	// 2: 반환 값을 스택의 값으로 할지.
	bool Pop(T& outValue)
	{
		if (IsEmpty()) return false;

		top--;
		outValue = data[top];
		return true;
	}

	inline int Count() const { return top; }

	inline bool IsEmpty() const { return top == 0; }

	inline bool IsFull() const { return top >= capacity; }



private:
	void Clear()
	{
		top = 0;
	}

private:
	T data[capacity] = {};

	int top = 0;
};