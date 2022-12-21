//
// Created by tomso on 21/12/2022.
//

#include "HashTable.h"


void HashTable::m_expend()
{

}

HashTable::~HashTable()
{
    delete[] arr;
}

void HashTable::insert(const Player&)
{

}

NodeUpside *HashTable::operator[](int id) {
    return nullptr;
}

int HashTable::hashFunction(int k, int id) const
{
    return ((id % m) + k * (1+ (id % (m - c)))) % m;
}

int HashTable::find(int id)
{
    // h_0(id)
    int first_index = hashFunction(0,id);
    // h_0 is empty
    if (*(arr+first_index) == nullptr)
    {
        return NOT_FOUND;
    }
    for (int i = 1; i < max_size; i++)
    {
        int index = hashFunction(i, id);
        if (*(arr+index) == nullptr)
            return NOT_FOUND;
        if ((*(arr+index))->id )
    }
}
