//
// Created by tomso on 21/12/2022.
//

#include "HashTable.h"

void HashTable::expend(bool origin, const Player &player)
{
    auto temp = arr;
    m = ((m + 1) * 2) - 1;
    arr = new Cell[m];
    try
    {
        for (int i = 0; i < size; i++)
        {
            if (temp[i].isActive())
            {
                transfer(temp[i].getAddress());
            }
        }
        try
        {
            find(player.getId());
        }
        catch (const NotExist &)
        {
        }
    }
    catch (const Full &)
    {
        delete[] arr;
        arr = temp;
        expend(false, player);
    }
    size = m;
    if (origin)
        delete[] temp;
}

HashTable::~HashTable()
{
    delete[] arr;
}

void HashTable::transfer(std::shared_ptr<Upside_Node> address)
{
    int index = getIndex(*address->data);
    arr[index].activate(address);
}

int HashTable::getIndex(const Player &player)
{
    int index = NOT_EXIST;
    try
    {
        index = find(player.getId());
        if (index != NOT_EXIST)
            throw std::invalid_argument("player exists");
    }
    catch (const NotExist &e)
    {
        return e.index;
    }
    return -1;
}

Upside_Node *HashTable::insert(const Player &player)
{
    int index;
    try
    {
        index = getIndex(player);
    }
    catch (const Full &)
    {
        expend(true, player);
        index = getIndex(player);
    }
    std::shared_ptr<Player> new_player(new Player(player));
    std::shared_ptr<Upside_Node> new_player_node(new Upside_Node(new_player));
    arr[index].activate(new_player_node);
    return new_player_node.get();
}

Upside_Node *HashTable::operator[](int id)
{
    int index;
    try
    {
        index = find(id);
    }
    catch (const Full &)
    {
        throw std::invalid_argument("player doesn't exist");
    }
    catch (const NotExist &)
    {
        throw std::invalid_argument("player doesn't exist");
    }
    return arr[index].getAddress().get();
}

int HashTable::hashFunction(int k, int id) const
{
    return ((id % m) + k * (1 + (id % (m - C)))) % m;
}

int HashTable::find(int id)
{
    int first_index = hashFunction(0, id);
    for (int i = 0; i < size; i++)
    {
        int index = hashFunction(i, id);
        if (i != 0 && index == first_index)
            throw Full(); // full
        if (!arr[index].isActive())
            throw NotExist(index); // not exist
        if (arr[index].getAddress()->data->getId() == id)
            return index;
    }
    throw Full();
}

void HashTable::Cell::activate(std::shared_ptr<Upside_Node> new_address)
{
    active = true;
    address = new_address;
}

bool HashTable::Cell::isActive() const
{
    return active;
}

std::shared_ptr<Upside_Node> HashTable::Cell::getAddress() const
{
    return address;
}

HashTable::Cell::~Cell()
{
    address = nullptr;
    active = false;
}
