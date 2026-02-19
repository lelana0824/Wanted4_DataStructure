#pragma once
#include <iostream>
// FIFO

template<typename T, int capacity = 10>
class Queue
{
public:
	Queue()
	{

	}
	// 추가 함수.
	bool Enqueue(const T& value)
	{
		if (IsFull()) return false;

		rear = (rear + 1) % (capacity + 1);
		data[rear] = value;
		return true;
	}

	// 추출 함수.
	bool Dequeue(T& outValue)
	{
		if (IsEmpty()) return false;

		front = (front + 1) % (capacity + 1);
		outValue = data[front];

		// 자료형의 기본값으로 초기화.
		data[front] = T();
		//memset(&data[front], 0, sizeof(T))

		return true;
	}

	// 삭제하지 않고 제일 앞의 값 반환하는 함수.
	bool Peek(T& outValue)
	{
		if (IsEmpty()) return false;

		outValue = data[(front + 1) % (capacity + 1)];
		return true;
	}

	void Print()
	{
		std::cout << "큐 내용 출력: \n";

		const int max = (front < rear) 
			? rear 
			: rear + (capacity + 1);

		for (int i = front + 1; i <= max; i++)
		{
			std::cout << " " << data[i % (capacity + 1)];
		}

		std::cout << "\n";
	}

	inline bool IsEmpty() const { return rear == front; }
	inline bool IsFull() const { 
		return ((rear + 1) % (capacity + 1)) == front;
	}
	inline int Capacity() const { return capacity; }

private:
	int front = 0;
	int rear = 0;

	// 데이터 저장 공간. 
	// 데이터 front, rear 구별을 위해서 한칸 비워둠
	T data[capacity + 1] = {};
};