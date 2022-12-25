//
// Created by tomso on 21/12/2022.
//

#ifndef WORLDCUP23A2_CPP_HASHTABLE_H
#define WORLDCUP23A2_CPP_HASHTABLE_H

#include "UpsideNode.h"
#include "Player.h"


class HashTable
{
public:
    class Cell
    {
        bool active;
        std::shared_ptr<Upside_Node> address;
    public:
        Cell(): active(false), address(nullptr){}
        void activate(std::shared_ptr<Upside_Node> new_address);
        bool isActive() const;
        std::shared_ptr<Upside_Node> getAddress() const;
        ~Cell();
    };

    Cell* arr;
    int size, m;
    void expend(bool, const Player&);
    static const int C = 5;
    static const int INITIAL_SIZE = 7;
    static const int NOT_EXIST = -1;

public:
    HashTable() : arr(new Cell[INITIAL_SIZE]), size(INITIAL_SIZE), m(INITIAL_SIZE) {}
    ~HashTable();
    int hashFunction(int k, int id) const;
    void insert(const Player&);
    void transfer(std::shared_ptr<Upside_Node>);
    int getIndex(const Player&);
    int find (int id);
    Upside_Node* operator[] (int id);
    class Full{
        public:
            Full(){}
    };
    class   NotExist{
        public:
            NotExist(int index): index(index){}
            int index;
    };
};


#endif //WORLDCUP23A2_CPP_HASHTABLE_H
