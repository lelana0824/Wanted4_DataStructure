#pragma once
#include "Pair.h"
#include <vector>
#include <string>
class HashTable
{
	using Entry = Pair<std::string, std::string>;

public:
	HashTable();
	~HashTable();

	bool Add(const std::string& key, const std::string& value);
	bool Delete(const std::string& key);
	bool Find(const std::string& key, Entry& outEntry);
	void Print();

	bool IsEmpty() const;

private:
	// 내부 저장소 크기.
	// - 내부 저장소 크기는 소수(1과 자기자신으로만 나눠지는 수)를 선택하는게 해시 충돌 방지에 좋음.
	// 사용 가능한 소수 중에서 큰 수를 사용.
	// 왜? 
	// 나머지 연산하고 나서 결과가 겹치지 않는 수를 조사해봤더니 소수..
	// 상용에서는 31을 많이 씀.
	static const int bucketCount = 19;

	// 이차저장소(해시 충돌 해결 방ㅂ접으로 체이닝.)
	std::vector<Entry> table[bucketCount];


};
