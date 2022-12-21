//
// Created by tomso on 21/12/2022.
//

#include "HashTable.h"


void HashTable::expend()
{

}

HashTable::~HashTable()
{
    delete[] arr;
}

void HashTable::insert(const Player& player)
{
    int index = NOT_EXIST;
    try
    {
        index = find(player.getId());
        if (index != NOT_EXIST)
            throw std::invalid_argument("player exists");
    }
    catch (const Full&)
    {
        HashTable::expend();
        index = find(player.getId());
    }
    catch (const NotExist& e)
    {
        index = e.index;
    }
    auto new_player = new Upside_Node<Player>(player);
    *(arr+index) = new_player;
}

Upside_Node<Player> *HashTable::operator[](int id) {
    int index = find(id);

}

int HashTable::hashFunction(int k, int id) const
{
    return ((id % m) + k * (1+ (id % (m - c)))) % m;
}

int HashTable::find(int id)
{
    int first_index = hashFunction(0,id);
    for (int i = 0; i < max_size; i++)
    {
        int index = hashFunction(i, id);
        if (i !=0 && index == first_index)
            throw Full(); // full
        if (*(arr+index) == nullptr)
            throw NotExist(index); // not exist
        if ((*(arr+index))->data.getId() == id)
            return index;
    }
}
;