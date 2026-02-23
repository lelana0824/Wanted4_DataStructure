#include "HashTable.h"
#include <iostream>
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

    // 오버플로우로 인한 음수 변환 가능성으로 인해 절대값으로 반환.
    return std::abs(hash);
}


HashTable::HashTable()
{
}

HashTable::~HashTable()
{
}

bool HashTable::Add(const std::string& key, const std::string& value)
{
    int bucketIndex = GenerateHash(key) % bucketCount;
    
    // 저장할 동적 배열 선택.
    std::vector<Entry>& position = table[bucketIndex];
   
    const int length = static_cast<int>(position.size());
    for (int i = 0; i < length; i++)
    {
        // 중복된 키값 확인.
        if (position[i].key == key)
        {
            return false;
        }
    }

    position.emplace_back(Entry(key, value));
    return true;
}

bool HashTable::Delete(const std::string& key)
{
    int bucketIndex = GenerateHash(key) % bucketCount;

    // 저장할 동적 배열 선택.
    std::vector<Entry>& position = table[bucketIndex];

    const int length = static_cast<int>(position.size());
    for (int i = 0; i < length; i++)
    {
        // 중복된 키값 확인.
        if (position[i].key == key)
        {
            position.erase(position.begin() + i);
            return true;
        }
    }


    return false;
}

bool HashTable::Find(const std::string& key, Entry& outEntry)
{
    int bucketIndex = GenerateHash(key) % bucketCount;

    // 저장할 동적 배열 선택.
    std::vector<Entry>& position = table[bucketIndex];

    // 예외처리 - 2차 자료구조에 저장된 데이터가 없으면 실패
    if (position.size() == 0) {
        return false;
    }
    const int length = static_cast<int>(position.size());
    for (int i = 0; i < length; i++)
    {
        // 중복된 키값 확인.
        if (position[i].key == key)
        {
            outEntry = position[i];
            return true;
        }
    }
    return false;
}

void HashTable::Print()
{
    for (const auto& container : table)
    {
        if (container.size() == 0)
        {
            continue;
        }

        for (const auto& item : container)
        {
            std::cout
                << "Key: " << item.key
                << " | Value: " << item.value
                << "\n";
        }
    }
};

bool HashTable::IsEmpty() const
{
    // 배열 - 2차 자료구조 전체에 저장된 데이터가 없는지 확인

    int sum = 0;
    for (const auto& container : table)
    {
        sum += static_cast<int>(container.size());
    }

    return sum == 0;
}