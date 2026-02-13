#pragma once

// 자동으로 크기가 늘어나는 배열 (List/ Vector)

#include <iostream>
#include <cassert>

template<typename List>
class ListIterator
{
public:
	// List가 템플릿 파라미터로 넘어오는 경우 typename 까지 지정
	using ValueType = typename List::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

public:
	ListIterator(PointerType ptr)
		:ptr(ptr)
	{

	}

	// 전위 증가 연산자.
	ListIterator& operator++()
	{
		++ptr;
		return *this;
	}

	// 후위 증가 연산자.
	ListIterator& operator++(int)
	{
		// 현재 반복자를 임시 저장.
		ListIterator iterator = *this;

		++(*this);
		return iterator;
	}

	ListIterator& operator--()
	{
		--ptr;
		return *this;
	}

	// 후위 감소 연산자.
	ListIterator& operator--(int)
	{
		// 현재 반복자를 임시 저장.
		ListIterator iterator = *this;

		--(*this);
		return iterator;
	}

	ReferenceType operator[](int index)
	{
		return *(ptr + index);
	}

	PointerType operator->()
	{
		return ptr;
	}

	ReferenceType operator*()
	{
		return *ptr;
	}

	// 비교연산자 오버로딩
	bool operator==(const ListIterator& other) const
	{
		return ptr == other.ptr;
	}

	bool operator!=(const ListIterator& other) const
	{
		return !(*this == other);
	}

private:
	// 반복자는 결국 포인터.
	PointerType ptr = nullptr;


};



template<typename T>
class List
{
public:
	using ValueType = T;
	using Iterator = ListIterator<List<T>>;

public:
	List()
	{
		Reallocate(capacity);
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

	// 범위 기반 루프 처리를 위한 함수 작성 (begin/end).
	// cpp 컴파일러에 맞춰서 소문자로 작성
	// 배열의 첫 위치를 반환하는 함수
	
	//Iterator begin()
	T* begin()
	{
		return data;
		//return Iterator(data);
	}

	// 배열에 저장된 마지막 요소의 다음 위치를 반환
	// 마지막 요소가 아님에 주의
	//Iterator end()
	T* end()
	{
		return data + size;
		//return Iterator(data + size);
	}

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
		if (data)
		{
			memcpy(newBlock, data, sizeof(T) * size);
		}

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