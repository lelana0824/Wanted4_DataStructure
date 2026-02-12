#include <iostream>
#include <cassert>
#include <array>

template<typename T, size_t size = 1>
class Array
{
public:
	size_t Size() const
	{
		return size;
	}

	// 배열 연산자 오버로딩.
	T& operator[](size_t index)
	{
		assert(index < 0 || index >= size);
		
		{
			
			__debugbreak();
		}

		return data[index];
	}

private:
	T data[size] = {};
};

int main()
{
	Array<int,20> array;
	array.Size();

	std::cin.get();
}