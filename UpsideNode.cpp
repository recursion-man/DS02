#include "UpsideNode.h"

void linkNodes(Upside_Node *node1, Upside_Node *node2)
{
    if (node1 != nullptr && node2 != nullptr && node1 != node2)
    {
        Upside_Node *temp1 = node1;
        Upside_Node *temp2 = node2;
        while (temp1->father)
            temp1 = temp1->father;
        while (temp1->father)
            temp2 = temp2->father;
        if (temp1 == temp2)
            return; // has the same father and we will make a circle if we link

        node2->father = node1;
        node1->size += node2->size;
        while (!node1->isRoot)
        {
            node1 = node1->father;
            node1->size += node2->size;
        }

        node2->isRoot = false;
    }
}

void updateSizesForNodesOnPath(Upside_Node *node)
{
    if (node == nullptr || node->isRoot)
    {
        return;
    }
    int prev_size;
    if (!node->father->isRoot)
    {
        prev_size = node->father->size;
        node->father->size -= node->size;
        node = node->father;
    }

    while (!node->father->isRoot)
    {
        int temp = node->father->size;
        node->father->size -= prev_size;
        prev_size = temp;
        node = node->father;
    }
}

void shrinkPaths(Upside_Node *node, Upside_Node *root)
{

    updateSizesForNodesOnPath(node);
    Upside_Node *temp = node->father;
    node->father = root;
    while (!temp->isRoot)
    {
        node = temp;
        temp = node->father;
        node->father = root;
    }
}

int getGamesToAdd(Upside_Node *node)
{
    int games_to_add = node->games_to_add;
    while (!node->isRoot)
    {
        node = node->father;
        games_to_add += node->games_to_add;
    }
    return games_to_add;
}

int getUpdatedGamesUntilRoot(Upside_Node *node)
{
    int updated_games_to_add = node->games_to_add;
    while (!node->father->isRoot)
    {
        node = node->father;
        updated_games_to_add += node->games_to_add;
    }
    return updated_games_to_add;
}

int getPlayerTotalGames(Upside_Node *node)
{
    return node->data->getGamesPlayed() + node->data->getGamesTeamPlayedWhenAdded() + getGamesToAdd(node);
}

void updateGamesForPlayersOnPath(Upside_Node *node)
{
    while (!node->father->isRoot)
    {
        node->games_to_add = getUpdatedGamesUntilRoot(node);
        node = node->father;
    }
}

permutation_t getUpdatedSpiritUntilRoot(Upside_Node *node)
{
    permutation_t new_parital_spirit = node->spirit_to_calculate;
    while (!node->father->isRoot)
    {
        node = node->father;
        new_parital_spirit = new_parital_spirit * node->spirit_to_calculate;
    }
    return new_parital_spirit;
}

void updateSpiritForPlayersOnPath(Upside_Node *node)
{
    while (!node->father->isRoot)
    {
        node->spirit_to_calculate = getUpdatedSpiritUntilRoot(node);
        node = node->father;
    }
}

Upside_Node *find(Upside_Node *player_node)
{
    if (player_node->isRoot)
    {
        return player_node;
    }

    // find the root
    Upside_Node *temp = player_node;
    while (!temp->isRoot)
    {
        temp = temp->father;
    }
    Upside_Node *root = temp;

    // update spirit for players on path
    updateSpiritForPlayersOnPath(player_node);

    // update games for players on path
    updateGamesForPlayersOnPath(player_node);

    // shrink pathways
    shrinkPaths(player_node, root);
    return root;
}

bool isTeamActive(Upside_Node *node)
{
    return find(node)->data->getTeam() != nullptr;
}

void handleUnion(Upside_Node *dest_root, Upside_Node *source_root, bool dest_root_is_buyer)
{
    // make sure to get the roots
    while (!dest_root->isRoot)
    {
        dest_root = dest_root->father;
    }
    while (!source_root->isRoot)
    {
        source_root = source_root->father;
    }
    if (dest_root == source_root)
    {
        return;
    }

    linkNodes(dest_root, source_root);
    if (dest_root_is_buyer)
    {
        // b points to a
        // fix spirit
        source_root->spirit_to_calculate = source_root->spirit_to_calculate * dest_root->team_updated_total_spirit;
        // fix games
        source_root->games_to_add -= dest_root->games_to_add;
    }

    else
    {
        // a points to b
        // fix spirit
        dest_root->spirit_to_calculate = dest_root->spirit_to_calculate * source_root->team_updated_total_spirit;
        source_root->spirit_to_calculate = source_root->spirit_to_calculate * dest_root->spirit_to_calculate.inv();
        // fix games
        source_root->games_to_add -= dest_root->games_to_add;
    }
}

Upside_Node *union_tree(Upside_Node *root1, Upside_Node *root2)
{
    if (root1 == root2)
    {
        return root1;
    }

    if (root1->size >= root2->size)
    {
        handleUnion(root1, root2, true);
        return root1;
    }
    else
    {
        handleUnion(root2, root1, false);
        return root2;
    }
};
