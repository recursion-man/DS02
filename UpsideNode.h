
#ifndef UPSIDE_NODE
#define UPSIDE_NODE
#include <iostream>
#include "Team.h"
#include "wet2util.h"
#include "Player.h"

class Player;

struct Upside_Node
{
    Upside_Node *father;
    bool isRoot;
    int size;
    int games_to_add;
    permutation_t spirit_to_calculate;
    permutation_t team_updated_total_spirit; // this field needs to be updated in the root by team in each added player
    std::shared_ptr<Player> data;
    Upside_Node(std::shared_ptr<Player> data, bool isRoot = true) : father(nullptr), isRoot(isRoot), size(1), games_to_add(0), spirit_to_calculate(permutation_t::neutral()), team_updated_total_spirit(permutation_t::neutral()), data(data){};
};

void linkNodes(Upside_Node *node1, Upside_Node *node2);
void shrinkPaths(Upside_Node *node, Upside_Node *root);
int getGamesToAdd(Upside_Node *node);
void updateGamesForPath(Upside_Node *node);
permutation_t getUpdatedSpiritUntilRoot(Upside_Node *node);
int getUpdatedGamesUntilRoot(Upside_Node *node);
void updateGamesForPlayersOnPath(Upside_Node *node);
void updateSpiritForPlayersOnPath(Upside_Node *node);
Upside_Node *find(Upside_Node *player_node);
void handleUnion(Upside_Node *dest_root, Upside_Node *source_root, bool dest_root_is_buyer);
Upside_Node *union_tree(Upside_Node *root1, Upside_Node *root2);
int getPlayerTotalGames(Upside_Node *node);
bool isTeamActive(Upside_Node *node);
permutation_t getSpiritToMultiPly(Upside_Node *player_node);
permutation_t getPlayerTotalSpirit(Upside_Node *player_node);

#endif // UPSIDE_NODE