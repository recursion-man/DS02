//
// Created by tomso on 21/12/2022.
//

#ifndef WORLDCUP23A2_CPP_HASHTABLE_H
#define WORLDCUP23A2_CPP_HASHTABLE_H
#include "AVLTree.h"
#include "UpsideNode.h"



class HashTable
{
public:
    class Cell
    {
        bool active;
        Upside_Node<Player>* address;
    public:
        Cell(): active(false), address(nullptr){}
        void activate(Upside_Node<Player>* new_address);
        bool isActive() const;
        Upside_Node<Player>* getAddress() const;
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
    void transfer(Upside_Node<Player>*);
    int getIndex(const Player&);
    int find (int id);
    Upside_Node<Player>* operator[] (int id);
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
