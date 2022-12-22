//
// Created by tomso on 21/12/2022.
//

#include "HashTable.h"



void HashTable::expend(bool origin, const Player& player)
{
    //std::cout<<"expand"<<std::endl;
    auto temp = arr;
    m = ((m+1)*2)-1;
    arr = new Cell[m];
    try {
        for (int i = 0; i < size; i++) {
            //std::cout << i << std::endl;
            if (temp[i].isActive()) {
                //std::cout<< i <<" : "<< temp[i].getAddress()->data.getId()<<std::endl;
                transfer(temp[i].getAddress());
            }
        }
        try {
            find(player.getId());
        } catch (const NotExist&){}
    }catch (const Full&)
    {
        delete[] arr;
        arr = temp;
        //std::cout<<"expand in expand "<<std::endl;
        expend(false, player);
    }
    size=m;
   // std::cout<<"size of temp " <<sizeof(temp)<<std::endl;
    if (origin)
        delete[] temp;
    //std::cout<<"end_expand, now "<< size<<std::endl;
}

HashTable::~HashTable()
{
    delete[] arr;
}

void HashTable::transfer(Upside_Node<Player>* address)
{
    int index = getIndex(address->data);
    arr[index].activate(address);
}

int HashTable::getIndex(const Player& player)
{
    int index = NOT_EXIST;
    try
    {
        index = find(player.getId());
        if (index != NOT_EXIST)
            throw std::invalid_argument("player exists");
    }
    catch (const NotExist& e)
    {
        return e.index;
    }
}

void HashTable::insert(const Player& player)
{
    int index;
    try {
        index = getIndex(player);
    } catch (const Full&)
    {
//        std::cout<<"got 1"<<std::endl;
        expend(true, player);
        index = getIndex(player);
//        std::cout<<"got 2"<<std::endl;
//        std::cout<<"got 3"<<std::endl;
    }
    auto new_player = new Upside_Node<Player>(player);
    arr[index].activate(new_player);
}

Upside_Node<Player> *HashTable::operator[](int id) {
    int index;
    try
    {
        index = find(id);
    }
    catch (const Full&) {throw std::invalid_argument("player doesn't exist");}
    catch (const NotExist&) {throw std::invalid_argument("player doesn't exist");}
    return arr[index].getAddress();
}

int HashTable::hashFunction(int k, int id) const
{
    return ((id % m) + k * (1+ (id % (m - C)))) % m;
}

int HashTable::find(int id)
{
    int first_index = hashFunction(0,id);
    for (int i = 0; i < size; i++)
    {
        int index = hashFunction(i, id);
        if (i !=0 && index == first_index)
            throw Full(); // full
        if (!arr[index].isActive())
            throw NotExist(index); // not exist
        if (arr[index].getAddress()->data.getId() == id)
            return index;
    }
    throw Full();
}




void HashTable::Cell::activate(Upside_Node<Player> *new_address)
{
    active= true;
    address = new_address;
}

bool HashTable::Cell::isActive()const {
    return active;
}

Upside_Node<Player> *HashTable::Cell::getAddress() const {
    return address;
}

HashTable::Cell::~Cell()
{
    address= nullptr;
    active= false;
}
