//
// Created by tomso on 21/12/2022.
//

#ifndef WORLDCUP23A2_CPP_HASHTABLE_H
#define WORLDCUP23A2_CPP_HASHTABLE_H
#include "AVLTree.h"
#include "UpsideNode.h"
#include "Player.h"

class HashTable
{
private:
    Upside_Node<Player> **arr;
    int size, m;
    void expend();
    static const int EXPAND_RATE = 2;
    static const int INITIAL_M = 15;
    static const int C = 5;
    static const int INITIAL_SIZE = 10;
    static const int NOT_EXIST;

public:
    HashTable() : arr(new Upside_Node<Player> *[INITIAL_SIZE]), size(INITIAL_SIZE), m(INITIAL_M) {}
    ~HashTable();
    int hashFunction(int k, int id) const;
    void insert(const Player &);
    int find(int id);
    Upside_Node<Player> *operator[](int id);
    class Full
    {
    public:
        Full() {}
    };
    class NotExist
    {
    public:
        NotExist(int index) : index(index) {}
        int index;
    };
};

#endif // WORLDCUP23A2_CPP_HASHTABLE_H
