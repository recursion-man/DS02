//
// Created by tomso on 21/12/2022.
//

#ifndef WORLDCUP23A2_CPP_HASHTABLE_H
#define WORLDCUP23A2_CPP_HASHTABLE_H
#include "AVLTree.h"


class Player{int id;};
class NodeUpside;
class HashTable
{
private:
    NodeUpside** arr;
    int size, max_size, m, c;
    void m_expend();
    static const int EXPAND_RATE = 2;
    static const int INITIAL_SIZE = 10;
    static const int NOT_FOUND;
    static const int  FULL;

public:
    HashTable() : arr(new NodeUpside* [INITIAL_SIZE]), size(0), max_size(INITIAL_SIZE) {}
    ~HashTable();
    int hashFunction(int k, int id) const;
    void insert(const Player&);
    int find (int id);
    NodeUpside* operator[] (int id);
};


#endif //WORLDCUP23A2_CPP_HASHTABLE_H
