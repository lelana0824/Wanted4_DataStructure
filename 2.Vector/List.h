#pragma once

// 자동으로 크기가 늘어나는 배열 (List/ Vector)

#include <iostream>
#include <cassert>

template<typename T>
class List
{


public:
	List()
	{
		//Reallocate(capacity);
		data = new T[capacity];
		memset(data, 0, sizeof(T) * capacity);
	}
	~List()
	{
		if (data)
		{
			delete[] data;
		}
	}
	void Add(const T& value)
	{
		if (size == capacity)
		{
			Reallocate(capacity * 2);
		}

		data[size++] = value;
	}

	void Add(const T&& value)
	{
		if (size == capacity)
		{
			Reallocate(capacity * 2);
		}

		data[size++] = std::move(value);
	}

	T& operator[](int index)
	{
		assert(index < 0 || index >= size);

		return data[index];
	}

	int Size() const { return size; }
	int Capacity() const { return capacity; }


private:
	// 저장 공간 할당하는 함수.
	void Reallocate(int newCapacity)
	{
		// 1. 이주할 새로운 공간 할당 (new)
		T* newBlock = new T[newCapacity];
		memset(newBlock, 0, sizeof(T) * newCapacity);

		// 2. 기존 항목을 새로운 공간에 복사/이동.
		/*for (int i = 0; i < size; i++)
		{
			newBlock[i] = data[i];
		}*/
		memcpy(newBlock, data, sizeof(T) * capacity);


		// 3. 기존 배열 공간 해제.
		delete[] data;
		data = newBlock;
		capacity = newCapacity;
	}

	

private:
	// 힙에 할당되는 배열을 관리할 포인터 변수.
	T* data = nullptr;

	int size = 0;
	int capacity = 2;
};