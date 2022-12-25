#include "UpsideNode.h"

void linkNodes(Upside_Node *node1, Upside_Node *node2)
{
    if (node1 != nullptr && node2 != nullptr)
    {
        node2->father = node1;
        node1->size += node2->size;
        node2->isRoot = false;
    }
}

void shrinkPaths(Upside_Node *node, Upside_Node *root)
{

    Upside_Node *temp = node->father;
    node->father = root;
    while (!temp->isRoot)
    {
        node = temp;
        temp = node->father;
        node->father = root;
        // update the size for each node exept the first node (he keeps it's subtree)
        node->size = 1;
    }
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
};

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

    source_root->father = dest_root;

    if (dest_root_is_buyer)
    {
        // b points to a
        // fix spirit
        source_root->spirit_to_calculate = source_root->spirit_to_calculate * dest_root->data->getTeam()->getTeamSpirit();
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

    source_root->isRoot = false;
    dest_root->size += source_root->size;
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
