#include "HashTable.h"

// 해시함수
// 키를 어떠한 과정을 통해서 숫자로 변환해주는 함수.
static int GenerateHash(const std::string& keyString)
{
    int hash = 0;

    // 문자열을 문자 배열로 활용해 해시 생성. (시스템마다 방법다름)
    const int length = static_cast<int>(keyString.length());
    for (int i = 0; i < length; i++)
    {
        // 해시 생성 로직.
        //hash += keyString[i] * (i + 1);
        // Hornor`s Method.
        hash = hash * 31 + keyString[i];
    }
    return hash;
}


HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

void HashTable::Add(const std::string& key, const std::string& value)
{
}

void HashTable::Delete(const std::string& key)
{
}

bool HashTable::Find(const std::string& key, Entry& outEntry)
{
    return false;
}

void HashTable::Print()
{
};

bool HashTable::IsEmpty() const
{
};
