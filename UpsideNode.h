
#ifndef UPSIDE_NODE
#define UPSIDE_NODE
#include <iostream>
// #include "Team.h"

// class Team;

template <class T>
struct Upside_Node
{
    Upside_Node<T> *father;
    // Team *team;
    bool isRoot;
    int gamesPreviousTeamPlayed;
    int spiritOfNewTeam;
    T data;
    Upside_Node(T data) : father(nullptr), isRoot(true), gamesPreviousTeamPlayed(0), spiritOfNewTeam(1), data(data){};
    Upside_Node() : father(nullptr), isRoot(true), gamesPreviousTeamPlayed(0), spiritOfNewTeam(1){};
};

template <class T>
Upside_Node<T> *find(Upside_Node<T> *player_node)
{
    if (player_node->isRoot)
    {
        return player_node;
    }
    // find the root
    Upside_Node<T> *root = player_node;
    while (!root->isRoot)
    {
        root = root->father;
    }

    // shrink pathways
    Upside_Node<T> *temp = player_node->father;
    while (!temp->isRoot)
    {
        player_node->father = root;
        player_node = temp;
        temp = player_node->father;
    }
    return root;
};

template <class T>
Upside_Node<T> *union_tree(Upside_Node<T> *destRoot, Upside_Node<T> *sourceRoot)
{
    while (!destRoot->isRoot)
    {
        destRoot = destRoot->father;
    }
    while (!sourceRoot->isRoot)
    {
        sourceRoot = sourceRoot->father;
    }
    if (sourceRoot == destRoot)
    {
        return destRoot;
    }
    sourceRoot->father = destRoot;
    // לעדכן את השדות בשביל משחקים ששוחקו והרוח
    sourceRoot->isRoot = false;
    // sourceRoot->team = nullptr;
    return destRoot;
};

#endif // UPSIDE_Node