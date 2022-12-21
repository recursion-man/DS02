
#ifndef UPSIDE_NODE
#define UPSIDE_NODE
#include <iostream>
// #include "Team.h"
#include "wet2util.h"

class Team;

template <class T>
struct Upside_Node
{
    Upside_Node<T> *father;
    Team *team;
    bool isRoot;
    int size;
    int games_played_with_previous_teams;
    int games_team_played_when_added;
    int games_team_played_when_deleted;
    permutation_t spirit_to_calculate;
    bool take_spirit_to_calculate;
    T data;
    Upside_Node(T data) : father(nullptr), team(nullptr), isRoot(true), size(1), games_played_with_previous_teams(0), games_team_played_when_added(0), games_team_played_when_deleted(0), spirit_to_calculate(), take_spirit_to_calculate(false), data(data){};
};

template <class T>
void shrinkPaths(Upside_Node<T> *node, Upside_Node<T> *root)
{
    Upside_Node<T> *temp = node->father;
    while (!node->isRoot)
    {
        node->father = root;
        node = temp;
        temp = node->father;
    }
}

template <class T>
void updateGamesForPath(Upside_Node<T> *node)
{
    int games_played_with_previous_teams = 0;
    Upside_Node<T> *temp = node;
    int games_team_played_when_added = node->games_team_played_when_added;
    while (!temp->isRoot)
    {

        Upside_Node<T> *temp2 = temp->father;
        while (!temp2->isRoot)
        {
            if (temp2->games_team_played_when_deleted != 0)
            {
                games_played_with_previous_teams += temp2->games_team_played_when_deleted - games_team_played_when_added;
                games_team_played_when_added = temp2->games_team_played_when_added;
            }
            temp2 = temp2->father;
        }
        temp->games_played_with_previous_teams += games_played_with_previous_teams;
        temp = temp->father;
    }
}

template <class T>
Upside_Node<T> *find(Upside_Node<T> *player_node)
{
    if (player_node->isRoot)
    {
        return player_node;
    }
    // find the root
    Upside_Node<T> *temp = player_node;
    while (!temp->isRoot)
    {
        temp = temp->father;
    }
    Upside_Node<T> *root = temp;

    // update games playes with previeous teams for the nodes in the path
    // updateGamesForPath(player_node);

    // shrink pathways
    shrinkPaths(player_node, root);
    return root;
};

template <class T>
void handleUnion(Upside_Node<T> *dest_root, Upside_Node<T> *source_root, bool take_source_team)
{
    // make sure to get the root
    while (!dest_root->isRoot)
    {
        dest_root = dest_root->father;
    }
    while (!source_root->isRoot)
    {
        source_root = source_root->father;
    }

    source_root->father = dest_root;
    // לעדכן את השדות בשביל משחקים ששוחקו והרוח
    source_root->isRoot = false;
    // source_root->games_team_played_when_deleted = source_root->team->getGamesTeamPlayed();
    // source_root->games_team_played_when_added = dest_root->team->getGamesTeamPlayed();

    dest_root->size += source_root->size;
    dest_root->team = take_source_team ? source_root->team : dest_root->team; // comment
    source_root->team = nullptr;                                              // comment
}

template <class T>
Upside_Node<T> *union_tree(Upside_Node<T> *root1, Upside_Node<T> *root2)
{
    if (root1 == root2)
    {
        return root1;
    }

    if (root1->size >= root2->size)
    {
        handleUnion(root1, root2, false);
        return root1;
    }
    else
    {
        handleUnion(root2, root1, true);
        return root2;
    }
};

#endif // UPSIDE_Node