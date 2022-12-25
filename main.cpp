#define CATCH_CONFIG_MAIN

#include "UpsideNode.h"
#include "Player.h"

#include "catch.hpp"

TEST_CASE("Find and union", "find")
{

    SECTION("simple find ")
    {
        Player p1(1);
        Upside_Node n1(p1);
        Upside_Node n2(p1);
        REQUIRE(find(&n1) == &n1);
        REQUIRE(find(&n2) == &n2);
        linkNodes(&n1, &n2);
        REQUIRE(find(&n2) == &n1);
        Upside_Node n3(p1);
        Upside_Node n4(p1);
        linkNodes(&n1, &n3);
        linkNodes(&n1, &n4);
        REQUIRE(find(&n3) == &n1);
        REQUIRE(find(&n4) == &n1);
        REQUIRE(n4.father == &n1);
        REQUIRE(n3.father == &n1);
        REQUIRE(n1.isRoot == true);
        REQUIRE(n2.isRoot == false);
        REQUIRE(n3.isRoot == false);
        REQUIRE(n4.isRoot == false);
    }

    SECTION("simple find with union")
    {

        Player p1(1);
        Upside_Node node1(p1);
        Upside_Node node2(p1);
        REQUIRE(find(&node1) == &node1);
        REQUIRE(find(&node2) == &node2);

        REQUIRE(union_tree(&node1, &node2) == &node1);
        REQUIRE(node2.isRoot == false);
        REQUIRE(find(&node2) == &node1);

        Upside_Node node3(p1);
        Upside_Node node4(p1);
        REQUIRE(find(&node3) == &node3);
        REQUIRE(find(&node4) == &node4);
        REQUIRE(union_tree(&node3, &node4) == &node3);
        REQUIRE(find(&node4) == &node3);
        REQUIRE(union_tree(&node3, &node1) == &node3);
        REQUIRE(node2.father == &node1);
        REQUIRE(find(&node2) == &node3);
        REQUIRE(node2.father == &node3);
        REQUIRE(node1.isRoot == false);
    }
    SECTION("find shrink path")
    {
        // checking if 6 and 5 also points diractly to the root 8 after find(5)
        Player p1(1);
        Upside_Node node5(p1);
        Upside_Node node6(p1);
        Upside_Node node7(p1);
        Upside_Node node8(p1);
        linkNodes(&node8, &node7);
        linkNodes(&node7, &node6);
        linkNodes(&node6, &node5);
        REQUIRE(node5.father == &node6);
        REQUIRE(node6.father == &node7);
        REQUIRE(node7.father == &node8);
        REQUIRE(node7.size == 3);
        REQUIRE(node8.size == 4);
        REQUIRE(node6.isRoot == false);

        REQUIRE(find(&node5) == &node8);
        REQUIRE(node6.father == &node8);
        REQUIRE(node7.father == &node8);
        REQUIRE(find(&node7) == &node8);
    }
    SECTION("union by size")
    {
        Player p1(1);
        Upside_Node node5(p1);
        Upside_Node node6(p1);
        Upside_Node node7(p1);
        Upside_Node node8(p1);

        REQUIRE(union_tree(&node5, &node6) == &node5);
        REQUIRE(node5.size == 2);
        REQUIRE(union_tree(&node5, &node7) == &node5);
        REQUIRE(find(&node7) == &node5);
        REQUIRE(union_tree(&node8, &node5) == &node5);
        REQUIRE(node8.father == &node5);
        REQUIRE(node7.father == &node5);
    }

    SECTION("Find update games")
    {
        Player p1(1);
        Upside_Node node1(p1);
        Upside_Node node2(p1);
        Upside_Node node3(p1);
        Upside_Node node4(p1);
        Upside_Node node5(p1);
        node1.games_to_add = 3;
        node2.games_to_add = 2;
        node3.games_to_add = 1;
        node4.games_to_add = 0;
        node5.games_to_add = 8;
        linkNodes(&node1, &node2);
        linkNodes(&node2, &node3);
        linkNodes(&node3, &node4);
        linkNodes(&node1, &node5);
        REQUIRE(find(&node4) == &node1);
        REQUIRE(node3.father == &node1);
        REQUIRE(node4.father == &node1);
        REQUIRE(node2.games_to_add == 2);
        REQUIRE(node3.games_to_add == 3);
        REQUIRE(node4.games_to_add == 3);
        REQUIRE(node5.games_to_add == 8);
        REQUIRE(find(&node5) == &node1);
        REQUIRE(node5.games_to_add == 8);
    }

    SECTION("Find ")
    {
        Player p1(1);
        Upside_Node node1(p1);
        Upside_Node node2(p1);
        linkNodes(&node1, &node2);
        node1.games_to_add++;
        REQUIRE(getGamesToAdd(&node1) == 1);
        REQUIRE(getGamesToAdd(&node2) == 1);
        node1.games_to_add++;
        REQUIRE(getGamesToAdd(&node1) == 2);
        REQUIRE(getGamesToAdd(&node2) == 2);
        Upside_Node node3(p1);
        linkNodes(&node2, &node3);
        REQUIRE(getGamesToAdd(&node2) == 2); // needs to be 0 when we put -2 in the player.games_team_played_when_added
        node1.games_to_add++;
        REQUIRE(getGamesToAdd(&node1) == 3);
        REQUIRE(getGamesToAdd(&node2) == 3);
        REQUIRE(getGamesToAdd(&node3) == 3); // needs to be 1
        REQUIRE(find(&node3) == &node1);

        // Upside_Node node3(p1);
        // Upside_Node node4(p1);
        // Upside_Node node5(p1);
        // node1.games_to_add = 3;
        // node2.games_to_add = 2;
        // node3.games_to_add = 1;
        // node4.games_to_add = 0;
        // node5.games_to_add = 8;
        // linkNodes(&node1, &node2);
        // linkNodes(&node2, &node3);
        // linkNodes(&node3, &node4);
        // linkNodes(&node1, &node5);
        // REQUIRE(find(&node4) == &node1);
        // REQUIRE(node3.father == &node1);
        // REQUIRE(node4.father == &node1);
        // REQUIRE(node2.games_to_add == 2);
        // REQUIRE(node3.games_to_add == 3);
        // REQUIRE(node4.games_to_add == 3);
        // REQUIRE(node5.games_to_add == 8);
        // REQUIRE(find(&node5) == &node1);
        // REQUIRE(node5.games_to_add == 8);
    }
}
