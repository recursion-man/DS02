#define CATCH_CONFIG_MAIN

#include "Player.h"
#include "UpsideNode.h"
#include "Team.h"

#include "catch.hpp"

TEST_CASE("Find and union", "find")
{

    SECTION("simple find ")
    {
        std::shared_ptr<Player> p1(new Player(1));
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

        std::shared_ptr<Player> p1(new Player(1));
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
        std::shared_ptr<Player> p1(new Player(1));
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
        std::shared_ptr<Player> p1(new Player(1));
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
        std::shared_ptr<Player> p1(new Player(1));
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
        std::shared_ptr<Player> p1(new Player(1));
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
    }

    SECTION("Find - Games Update")
    {
        std::shared_ptr<Team> team1(new Team(1));
        permutation_t demi_per;
        std::shared_ptr<Player> p1(new Player(1, 1, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));
        std::shared_ptr<Player> p2(new Player(2, 1, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));
        std::shared_ptr<Player> p3(new Player(3, 1, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));

        Upside_Node node1(p1);
        Upside_Node node2(p2);
        Upside_Node node3(p3);

        linkNodes(&node1, &node2);
        linkNodes(&node2, &node3);
        REQUIRE(getPlayerTotalGames(&node1) == 0);
        REQUIRE(getPlayerTotalGames(&node2) == 0);
        REQUIRE(getPlayerTotalGames(&node3) == 0);
        // team played 1 game
        node1.games_to_add++;
        REQUIRE(getPlayerTotalGames(&node1) == 1);
        REQUIRE(getPlayerTotalGames(&node2) == 1);
        REQUIRE(getPlayerTotalGames(&node3) == 1);
        std::shared_ptr<Player> p4(new Player(4, 1, 0, 0, true, 0, demi_per, -1, team1->getTeamSpirit(), team1.get()));
        Upside_Node node4(p4);
        linkNodes(&node1, &node4);
        REQUIRE(getPlayerTotalGames(&node4) == 0);

        // team played 2 games
        node1.games_to_add++;
        REQUIRE(getPlayerTotalGames(&node1) == 2);
        REQUIRE(getPlayerTotalGames(&node2) == 2);
        REQUIRE(getPlayerTotalGames(&node3) == 2);
        REQUIRE(getPlayerTotalGames(&node4) == 1);

        std::shared_ptr<Player> p5(new Player(5, 1, 0, 0, true, 0, demi_per, -2, team1->getTeamSpirit(), team1.get()));
        Upside_Node node5(p5);
        linkNodes(&node1, &node5);

        // team played 3 games
        node1.games_to_add++;
        REQUIRE(getPlayerTotalGames(&node1) == 3);
        REQUIRE(getPlayerTotalGames(&node2) == 3);
        REQUIRE(getPlayerTotalGames(&node3) == 3);
        REQUIRE(getPlayerTotalGames(&node4) == 2);
        REQUIRE(getPlayerTotalGames(&node5) == 1);
        REQUIRE(find(&node4) == &node1);
        REQUIRE(getPlayerTotalGames(&node4) == 2);
        REQUIRE(find(&node2) == &node1);
        REQUIRE(getPlayerTotalGames(&node2) == 3);
        REQUIRE(getPlayerTotalGames(&node3) == 3);
        REQUIRE(find(&node3) == &node1);
        REQUIRE(getPlayerTotalGames(&node2) == 3);
        REQUIRE(getPlayerTotalGames(&node3) == 3);

        // team played 4 games
        node1.games_to_add++;
        REQUIRE(getPlayerTotalGames(&node1) == 4);
        REQUIRE(getPlayerTotalGames(&node2) == 4);
        REQUIRE(getPlayerTotalGames(&node3) == 4);
        REQUIRE(getPlayerTotalGames(&node4) == 3);
        REQUIRE(getPlayerTotalGames(&node5) == 2);

        std::shared_ptr<Player> p6(new Player(6, 1, 0, 0, true, 0, demi_per, -4, team1->getTeamSpirit(), team1.get()));
        Upside_Node node6(p6);
        linkNodes(&node1, &node6);
        REQUIRE(getPlayerTotalGames(&node6) == 0);

        // team played 5 games
        node1.games_to_add++;
        std::shared_ptr<Player> p7(new Player(7, 1, 0, 0, true, 0, demi_per, -5, team1->getTeamSpirit(), team1.get()));
        Upside_Node node7(p7);
        std::shared_ptr<Player> p8(new Player(8, 1, 0, 0, true, 0, demi_per, -5, team1->getTeamSpirit(), team1.get()));
        Upside_Node node8(p8);

        // team played 6 games
        node1.games_to_add++;

        std::shared_ptr<Player> p9(new Player(9, 1, 0, 0, true, 0, demi_per, -6, team1->getTeamSpirit(), team1.get()));
        Upside_Node node9(p9);
        std::shared_ptr<Player> p10(new Player(10, 1, 1, 0, true, 0, demi_per, -6, team1->getTeamSpirit(), team1.get()));
        Upside_Node node10(p10);

        linkNodes(&node6, &node7);
        linkNodes(&node7, &node8);
        linkNodes(&node8, &node9);
        linkNodes(&node9, &node10);

        REQUIRE(getPlayerTotalGames(&node6) == 2);
        REQUIRE(getPlayerTotalGames(&node7) == 1);
        REQUIRE(getPlayerTotalGames(&node8) == 1);
        REQUIRE(getPlayerTotalGames(&node9) == 0);
        REQUIRE(getPlayerTotalGames(&node10) == 1);
        REQUIRE(find(&node10) == &node1);
        REQUIRE(getPlayerTotalGames(&node6) == 2);
        REQUIRE(getPlayerTotalGames(&node7) == 1);
        REQUIRE(getPlayerTotalGames(&node8) == 1);
        REQUIRE(getPlayerTotalGames(&node9) == 0);
        REQUIRE(getPlayerTotalGames(&node10) == 1);
    }
    SECTION("union - Games Update")
    {
        std::shared_ptr<Team> team1(new Team(1));
        permutation_t demi_per;
        std::shared_ptr<Player> p1(new Player(1, 1, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));
        std::shared_ptr<Player> p2(new Player(2, 1, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));
        std::shared_ptr<Player> p3(new Player(3, 1, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));

        Upside_Node node1(p1);
        Upside_Node node2(p2);
        Upside_Node node3(p3);

        linkNodes(&node1, &node2);
        linkNodes(&node2, &node3);
        REQUIRE(getPlayerTotalGames(&node1) == 0);
        REQUIRE(getPlayerTotalGames(&node2) == 0);
        REQUIRE(getPlayerTotalGames(&node3) == 0);

        // team played 1 game
        node1.games_to_add++;
        REQUIRE(getPlayerTotalGames(&node1) == 1);
        REQUIRE(getPlayerTotalGames(&node2) == 1);
        REQUIRE(getPlayerTotalGames(&node3) == 1);
        std::shared_ptr<Player> p4(new Player(4, 1, 0, 0, true, 0, demi_per, -1, team1->getTeamSpirit(), team1.get()));
        Upside_Node node4(p4);
        linkNodes(&node1, &node4);
        REQUIRE(getPlayerTotalGames(&node4) == 0);

        std::shared_ptr<Team> team2(new Team(2));
        std::shared_ptr<Player> p11(new Player(1, 2, 0, 0, true, 0, demi_per, 0, team2->getTeamSpirit(), team2.get()));
        std::shared_ptr<Player> p12(new Player(2, 2, 0, 0, true, 0, demi_per, 0, team2->getTeamSpirit(), team2.get()));
        std::shared_ptr<Player> p13(new Player(3, 2, 1, 0, true, 0, demi_per, 0, team2->getTeamSpirit(), team2.get()));

        Upside_Node node11(p11);
        Upside_Node node12(p12);
        Upside_Node node13(p13);
        linkNodes(&node11, &node12);
        linkNodes(&node11, &node13);

        // team2 played 1 game
        node11.games_to_add++;
        REQUIRE(getPlayerTotalGames(&node11) == 1);
        REQUIRE(getPlayerTotalGames(&node12) == 1);
        REQUIRE(getPlayerTotalGames(&node13) == 2); // node13 reseted with 1 gamesPlayed

        // unite when same size
        REQUIRE(union_tree(&node1, &node11) == &node1);
        REQUIRE(getPlayerTotalGames(&node1) == 1);
        REQUIRE(getPlayerTotalGames(&node2) == 1);
        REQUIRE(getPlayerTotalGames(&node3) == 1);
        REQUIRE(getPlayerTotalGames(&node11) == 1);
        REQUIRE(getPlayerTotalGames(&node12) == 1);
        REQUIRE(getPlayerTotalGames(&node13) == 2);
        REQUIRE(find(&node11) == &node1);
        REQUIRE(find(&node3) == &node1);
        REQUIRE(find(&node13) == &node1);
        REQUIRE(getPlayerTotalGames(&node1) == 1);
        REQUIRE(getPlayerTotalGames(&node2) == 1);
        REQUIRE(getPlayerTotalGames(&node3) == 1);
        REQUIRE(getPlayerTotalGames(&node11) == 1);
        REQUIRE(getPlayerTotalGames(&node12) == 1);
        REQUIRE(getPlayerTotalGames(&node13) == 2);
        REQUIRE(node1.size == 6);
        REQUIRE(node11.size == 3);

        // united team play 1 games
        node1.games_to_add++;
        REQUIRE(getPlayerTotalGames(&node1) == 2);
        REQUIRE(getPlayerTotalGames(&node2) == 2);
        REQUIRE(getPlayerTotalGames(&node3) == 2);
        REQUIRE(getPlayerTotalGames(&node11) == 2);
        REQUIRE(getPlayerTotalGames(&node12) == 2);
        REQUIRE(getPlayerTotalGames(&node13) == 3);
    }
}