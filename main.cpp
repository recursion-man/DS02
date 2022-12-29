#define CATCH_CONFIG_MAIN

#include "Player.h"
#include "UpsideNode.h"
#include "Team.h"
#include "wet2util.h"
#include "worldcup23a2.h"

#include "catch.hpp"

TEST_CASE("world_cup")
{

    SECTION("add_team")
    {
        world_cup_t *world_cup = new world_cup_t();

        REQUIRE(world_cup->add_team(0) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_team(-3) == StatusType::INVALID_INPUT);

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_team(1) == StatusType::FAILURE);
        REQUIRE(world_cup->get_team_points(1).ans() == 0);

        REQUIRE(world_cup->add_team(2) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_team_points(2).ans() == 0);

        REQUIRE(world_cup->add_team(3) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_team_points(3).ans() == 0);
        REQUIRE(world_cup->add_team(4) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_team_points(4).ans() == 0);
        delete world_cup;
    }

    SECTION("remove_team")
    {
        world_cup_t *world_cup = new world_cup_t();

        REQUIRE(world_cup->remove_team(0) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->remove_team(-3) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->remove_team(1) == StatusType::FAILURE);

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_team_points(1).ans() == 0);

        REQUIRE(world_cup->remove_team(1) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_team_points(1).status() == StatusType::FAILURE);

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_team_points(1).ans() == 0);

        int p1[5] = {4, 2, 3, 1, 0};
        permutation_t per1(p1);
        REQUIRE(world_cup->add_player(1, 1, per1, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->remove_team(1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(1, 3) == StatusType::FAILURE);

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_team_points(1).ans() == 0);
        REQUIRE(world_cup->add_player_cards(1, 3) == StatusType::FAILURE);
        REQUIRE(world_cup->add_player(1, 1, per1, 0, 0, 0, true) == StatusType::FAILURE);

        int p4[5] = {4, 2, 3, 1, 0}, p2[5] = {0, 4, 2, 1, 3}, p3[5] = {4, 2, 3, 1, 0};
        permutation_t per4(p4), per2(p2), per3(p3);
        REQUIRE(world_cup->add_player(2, 1, per2, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(3, 1, per3, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(4, 1, per4, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(isSame(world_cup->get_partial_spirit(2).ans(), per2));
        REQUIRE(isSame(world_cup->get_partial_spirit(3).ans(), per2 * per3));
        REQUIRE(isSame(world_cup->get_partial_spirit(4).ans(), per2 * per3 * per4));

        REQUIRE(world_cup->remove_team(1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(2, 3) == StatusType::FAILURE);
        REQUIRE(world_cup->add_player_cards(3, 3) == StatusType::FAILURE);
        REQUIRE(world_cup->add_player_cards(4, 3) == StatusType::FAILURE);

        delete world_cup;
    }

    SECTION("add_player")
    {
        world_cup_t *world_cup = new world_cup_t();

        int p1[5] = {4, 2, 3, 1, 0}, p2[5] = {0, 4, 2, 1, 3}, p3[5] = {4, 2, 3, 1, 0}, invalid_per[5]{1, 12, 4, 1, -100};
        permutation_t per1(p1), per2(p2), per3(p3);
        REQUIRE(world_cup->add_player(0, 1, per1, 4, 8, 2, true) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player(-2, 1, per1, 0, 0, 0, true) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player(1, -3, per1, 0, 0, 0, true) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player(1, 0, per1, 0, 0, 0, true) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player(1, 0, invalid_per, 0, 0, 0, true) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player(1, 0, per1, -3, 0, 0, true) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player(1, 0, per1, 0, 0, -2, true) == StatusType::INVALID_INPUT);

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_team_points(1).ans() == 0);
        REQUIRE(world_cup->add_player(1, 1, per1, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_player_cards(1).ans() == 0);
        REQUIRE(world_cup->add_player(2, 1, per2, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_player_cards(2).ans() == 0);

        REQUIRE(world_cup->get_partial_spirit(1).status() == StatusType::SUCCESS);
        REQUIRE(isSame(world_cup->get_partial_spirit(1).ans(), per1));
        REQUIRE(isSame(world_cup->get_partial_spirit(2).ans(), per1 * per2));

        REQUIRE(world_cup->add_player(3, 1, per3, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(isSame(world_cup->get_partial_spirit(3).ans(), per1 * per2 * per3));

        REQUIRE(world_cup->add_player(4, 1, per1, 3, -2, 1, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_player_cards(4).ans() == 1);
        REQUIRE(world_cup->get_player_cards(3).ans() == 0);
        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 0);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 0);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 0);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 3);

        REQUIRE(world_cup->add_team(2) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(1, 2, per1, 0, 0, 0, true) == StatusType::FAILURE);
        REQUIRE(world_cup->add_player(5, 2, per3, 7, 2, 1, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(6, 2, per3, 5, 2, 5, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(7, 2, per3, 3, 0, 3, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(8, 2, per3, 6, -10, 4, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 7);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 5);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 3);
        REQUIRE(world_cup->num_played_games_for_player(8).ans() == 6);
        REQUIRE(world_cup->get_player_cards(5).ans() == 1);
        REQUIRE(world_cup->get_player_cards(6).ans() == 5);
        REQUIRE(world_cup->get_player_cards(7).ans() == 3);
        REQUIRE(world_cup->get_player_cards(8).ans() == 4);

        delete world_cup;
    }

    SECTION("play_match")
    {
        world_cup_t *world_cup = new world_cup_t();

        REQUIRE(world_cup->play_match(2, 0).status() == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->play_match(-3, 3).status() == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->play_match(1, 1).status() == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->play_match(1, 2).status() == StatusType::FAILURE);

        int p1[5] = {4, 2, 3, 1, 0}, p2[5] = {0, 4, 2, 1, 3}, p3[5] = {4, 2, 3, 1, 0}, p4[5] = {2, 4, 3, 1, 0};
        permutation_t per1(p1), per2(p2), per3(p3), per4(p4);

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);

        REQUIRE(world_cup->add_player(1, 1, per1, 2, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(2, 1, per2, 3, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(3, 1, per3, 0, 0, 0, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 2);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 3);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 0);

        REQUIRE(world_cup->add_team(2) == StatusType::SUCCESS);
        REQUIRE(world_cup->play_match(1, 2).status() == StatusType::FAILURE);

        REQUIRE(world_cup->add_player(4, 2, per4, 2, 4, 0, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 2);

        // team1 has 0 abiliy team 2 has 4 ability
        output_t<int> match = world_cup->play_match(1, 2);
        REQUIRE(match.status() == StatusType::SUCCESS);
        REQUIRE(match.ans() == 3);
        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 3);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 4);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 1);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 3);
        REQUIRE(world_cup->get_team_points(1).ans() == 0);
        REQUIRE(world_cup->get_team_points(2).ans() == 3);

        REQUIRE(world_cup->add_player(5, 2, per4, 0, -7, 0, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 0);
        // both tean has same score
        output_t<int> match2 = world_cup->play_match(1, 2);
        REQUIRE(match2.status() == StatusType::SUCCESS);
        REQUIRE(match2.ans() == 2);
        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 4);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 5);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 2);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 4);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 1);
        REQUIRE(world_cup->get_team_points(1).ans() == 3);
        REQUIRE(world_cup->get_team_points(2).ans() == 3);

        REQUIRE(world_cup->add_player(6, 2, per2, 6, 3, 0, true) == StatusType::SUCCESS);
        // both team has same score
        REQUIRE(world_cup->add_player(7, 2, per2, 7, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(8, 2, per2, 8, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(9, 2, per2, 9, -1, 0, true) == StatusType::SUCCESS);

        // team 1 has +1 score than team 2
        output_t<int> match3 = world_cup->play_match(1, 2);
        REQUIRE(match3.status() == StatusType::SUCCESS);
        REQUIRE(match3.ans() == 1);
        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 5);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 6);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 3);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 5);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 2);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 7);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 8);
        REQUIRE(world_cup->num_played_games_for_player(8).ans() == 9);
        REQUIRE(world_cup->num_played_games_for_player(9).ans() == 10);

        REQUIRE(world_cup->get_team_points(1).ans() == 6);
        REQUIRE(world_cup->get_team_points(2).ans() == 3);
    }

    SECTION("num_played_games_for_player")
    {
        world_cup_t *world_cup = new world_cup_t();

        REQUIRE(world_cup->num_played_games_for_player(-3).status() == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->num_played_games_for_player(0).status() == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->num_played_games_for_player(-102).status() == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->num_played_games_for_player(1).status() == StatusType::FAILURE);
        REQUIRE(world_cup->num_played_games_for_player(17).status() == StatusType::FAILURE);

        int p1[5] = {4, 2, 3, 1, 0}, p2[5] = {0, 4, 2, 1, 3}, p3[5] = {4, 2, 3, 1, 0};
        int p4[5] = {2, 4, 3, 1, 0}, p5[5] = {0, 2, 1, 4, 3}, p6[5] = {1, 2, 3, 4, 0}, p7[5] = {1, 3, 2, 4, 0};
        int p8[5] = {1, 4, 0, 2, 3}, p9[5] = {1, 0, 4, 2, 3}, p10[5] = {3, 2, 4, 1, 0}, p11[5] = {3, 1, 2, 4, 0};
        int p12[5] = {3, 0, 2, 1, 4}, p13[5] = {3, 0, 1, 4, 2}, p14[5] = {1, 2, 0, 3, 4};
        permutation_t per1(p1), per2(p2), per3(p3), per4(p4), per5(p5), per6(p6), per7(p7), per8(p8), per9(p9), per10(p10), per11(p11), per12(p12), per13(p13), per14(p14);
        // permutation_t pers[15] = {per1, per1, per2, per3, per4, per5, per6, per7, per8, per9, per10, per11, per12, per13, per14};

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);

        REQUIRE(world_cup->add_player(1, 1, per1, 1, 1, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(2, 1, per2, 2, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(3, 1, per3, 3, 0, 0, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 1);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 2);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 3);

        REQUIRE(world_cup->add_team(2) == StatusType::SUCCESS);

        REQUIRE(world_cup->add_player(4, 2, per4, 4, 2, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(5, 2, per5, 5, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(6, 2, per6, 6, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(7, 2, per7, 7, 0, 0, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 4);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 5);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 6);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 7);

        // match 1

        REQUIRE(world_cup->play_match(1, 2).status() == StatusType::SUCCESS);

        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 2);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 3);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 4);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 5);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 6);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 7);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 8);

        REQUIRE(world_cup->add_player(8, 1, per8, 8, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 2);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 3);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 4);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 5);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 6);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 7);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 8);
        REQUIRE(world_cup->num_played_games_for_player(8).ans() == 8);

        REQUIRE(world_cup->play_match(1, 2).status() == StatusType::SUCCESS);
        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 3);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 4);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 5);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 6);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 7);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 8);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 9);
        REQUIRE(world_cup->num_played_games_for_player(8).ans() == 9);

        // team 2 buys team 1
        REQUIRE(world_cup->buy_team(2, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 3);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 4);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 5);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 6);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 7);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 8);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 9);
        REQUIRE(world_cup->num_played_games_for_player(8).ans() == 9);

        REQUIRE(world_cup->add_player(9, 2, per9, 9, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->num_played_games_for_player(9).ans() == 9);

        REQUIRE(world_cup->add_team(3) == StatusType::SUCCESS);

        REQUIRE(world_cup->add_player(10, 3, per10, 10, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(11, 3, per11, 11, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(12, 3, per12, 12, 0, 0, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->num_played_games_for_player(10).ans() == 10);
        REQUIRE(world_cup->num_played_games_for_player(11).ans() == 11);
        REQUIRE(world_cup->num_played_games_for_player(12).ans() == 12);

        // third match for team 1 players, second match for team 2 players, first match for team 3
        REQUIRE(world_cup->play_match(3, 2).status() == StatusType::SUCCESS);
        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 4);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 5);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 6);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 7);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 8);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 9);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 10);
        REQUIRE(world_cup->num_played_games_for_player(8).ans() == 10);
        REQUIRE(world_cup->num_played_games_for_player(9).ans() == 10);
        REQUIRE(world_cup->num_played_games_for_player(10).ans() == 11);
        REQUIRE(world_cup->num_played_games_for_player(11).ans() == 12);
        REQUIRE(world_cup->num_played_games_for_player(12).ans() == 13);

        REQUIRE(world_cup->play_match(3, 2).status() == StatusType::SUCCESS);
        REQUIRE(world_cup->play_match(3, 2).status() == StatusType::SUCCESS);
        REQUIRE(world_cup->play_match(3, 2).status() == StatusType::SUCCESS);

        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 7);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 8);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 9);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 10);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 11);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 12);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(8).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(9).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(10).ans() == 14);
        REQUIRE(world_cup->num_played_games_for_player(11).ans() == 15);
        REQUIRE(world_cup->num_played_games_for_player(12).ans() == 16);

        REQUIRE(world_cup->add_player(19, 2, per1, 19, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->num_played_games_for_player(19).ans() == 19);

        // demi players for team 3 to be bigger than team 2
        REQUIRE(world_cup->add_player(13, 3, per13, 13, 3, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(14, 3, per14, 14, 1, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(15, 3, per13, 15, 6, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(16, 3, per13, 16, 5, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(17, 3, per13, 17, 2, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(18, 3, per13, 18, 8, 0, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->num_played_games_for_player(13).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(14).ans() == 14);
        REQUIRE(world_cup->num_played_games_for_player(15).ans() == 15);
        REQUIRE(world_cup->num_played_games_for_player(16).ans() == 16);
        REQUIRE(world_cup->num_played_games_for_player(17).ans() == 17);
        REQUIRE(world_cup->num_played_games_for_player(18).ans() == 18);

        // team 2 is the bigger one
        REQUIRE(world_cup->buy_team(3, 2) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(20, 3, per1, 20, 1, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 7);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 8);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 9);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 10);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 11);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 12);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(8).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(9).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(10).ans() == 14);
        REQUIRE(world_cup->num_played_games_for_player(11).ans() == 15);
        REQUIRE(world_cup->num_played_games_for_player(12).ans() == 16);
        REQUIRE(world_cup->num_played_games_for_player(13).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(14).ans() == 14);
        REQUIRE(world_cup->num_played_games_for_player(15).ans() == 15);
        REQUIRE(world_cup->num_played_games_for_player(16).ans() == 16);
        REQUIRE(world_cup->num_played_games_for_player(17).ans() == 17);
        REQUIRE(world_cup->num_played_games_for_player(18).ans() == 18);
        REQUIRE(world_cup->num_played_games_for_player(19).ans() == 19);

        REQUIRE(world_cup->num_played_games_for_player(20).ans() == 20);

        REQUIRE(world_cup->remove_team(3) == StatusType::SUCCESS);
        REQUIRE(world_cup->num_played_games_for_player(1).ans() == 7);
        REQUIRE(world_cup->num_played_games_for_player(2).ans() == 8);
        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 9);
        REQUIRE(world_cup->num_played_games_for_player(4).ans() == 10);
        REQUIRE(world_cup->num_played_games_for_player(5).ans() == 11);
        REQUIRE(world_cup->num_played_games_for_player(6).ans() == 12);
        REQUIRE(world_cup->num_played_games_for_player(7).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(8).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(9).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(10).ans() == 14);
        REQUIRE(world_cup->num_played_games_for_player(11).ans() == 15);
        REQUIRE(world_cup->num_played_games_for_player(12).ans() == 16);
        REQUIRE(world_cup->num_played_games_for_player(13).ans() == 13);
        REQUIRE(world_cup->num_played_games_for_player(14).ans() == 14);
        REQUIRE(world_cup->num_played_games_for_player(15).ans() == 15);
        REQUIRE(world_cup->num_played_games_for_player(16).ans() == 16);
        REQUIRE(world_cup->num_played_games_for_player(17).ans() == 17);
        REQUIRE(world_cup->num_played_games_for_player(18).ans() == 18);
        REQUIRE(world_cup->num_played_games_for_player(19).ans() == 19);
        REQUIRE(world_cup->num_played_games_for_player(20).ans() == 20);

        delete world_cup;
    }

    SECTION("get_player_cards & add_player_cards")
    {
        world_cup_t *world_cup = new world_cup_t();

        REQUIRE(world_cup->add_player_cards(-2, 0) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player_cards(-3, 3) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player_cards(1, -1) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player_cards(1, 2) == StatusType::FAILURE);

        int p1[5] = {4, 2, 3, 1, 0}, p2[5] = {0, 4, 2, 1, 3}, p3[5] = {4, 2, 3, 1, 0};
        int p4[5] = {2, 4, 3, 1, 0}, p5[5] = {0, 2, 1, 4, 3}, p6[5] = {1, 2, 3, 4, 0}, p7[5] = {1, 3, 2, 4, 0};
        int p8[5] = {1, 4, 0, 2, 3}, p9[5] = {1, 0, 4, 2, 3}, p10[5] = {3, 2, 4, 1, 0}, p11[5] = {3, 1, 2, 4, 0};
        int p12[5] = {3, 0, 2, 1, 4}, p13[5] = {3, 0, 1, 4, 2}, p14[5] = {1, 2, 0, 3, 4};
        permutation_t per1(p1), per2(p2), per3(p3), per4(p4), per5(p5), per6(p6), per7(p7), per8(p8), per9(p9), per10(p10), per11(p11), per12(p12), per13(p13), per14(p14);

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);

        REQUIRE(world_cup->add_player(1, 1, per1, 0, 0, 1, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(2, 1, per2, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(3, 1, per3, 0, 0, 0, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_player_cards(1).ans() == 1);
        REQUIRE(world_cup->get_player_cards(2).ans() == 0);
        REQUIRE(world_cup->get_player_cards(3).ans() == 0);

        REQUIRE(world_cup->add_player_cards(1, 2) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(2, 2) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(3, 2) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_player_cards(1).ans() == 3);
        REQUIRE(world_cup->get_player_cards(2).ans() == 2);
        REQUIRE(world_cup->get_player_cards(3).ans() == 2);

        REQUIRE(world_cup->num_played_games_for_player(3).ans() == 0);
        REQUIRE(world_cup->get_player_cards(3).ans() == 2);

        REQUIRE(world_cup->add_team(2) == StatusType::SUCCESS);

        REQUIRE(world_cup->add_player(4, 2, per4, 0, 0, 4, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(5, 2, per5, 0, 0, 5, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(6, 2, per6, 0, 0, 6, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(7, 2, per7, 0, 0, 7, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_player_cards(4).ans() == 4);
        REQUIRE(world_cup->get_player_cards(5).ans() == 5);
        REQUIRE(world_cup->get_player_cards(6).ans() == 6);
        REQUIRE(world_cup->get_player_cards(7).ans() == 7);

        REQUIRE(world_cup->add_player_cards(4, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(5, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(6, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(7, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_player_cards(4).ans() == 5);
        REQUIRE(world_cup->get_player_cards(5).ans() == 6);
        REQUIRE(world_cup->get_player_cards(6).ans() == 7);
        REQUIRE(world_cup->get_player_cards(7).ans() == 8);

        REQUIRE(world_cup->play_match(1, 2).status() == StatusType::SUCCESS);

        REQUIRE(world_cup->get_player_cards(1).ans() == 3);
        REQUIRE(world_cup->get_player_cards(2).ans() == 2);
        REQUIRE(world_cup->get_player_cards(3).ans() == 2);
        REQUIRE(world_cup->get_player_cards(4).ans() == 5);
        REQUIRE(world_cup->get_player_cards(5).ans() == 6);
        REQUIRE(world_cup->get_player_cards(6).ans() == 7);
        REQUIRE(world_cup->get_player_cards(7).ans() == 8);

        REQUIRE(world_cup->buy_team(1, 2) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_player_cards(1).ans() == 3);
        REQUIRE(world_cup->get_player_cards(2).ans() == 2);
        REQUIRE(world_cup->get_player_cards(3).ans() == 2);
        REQUIRE(world_cup->get_player_cards(4).ans() == 5);
        REQUIRE(world_cup->get_player_cards(5).ans() == 6);
        REQUIRE(world_cup->get_player_cards(6).ans() == 7);
        REQUIRE(world_cup->get_player_cards(7).ans() == 8);

        REQUIRE(world_cup->add_player_cards(1, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(2, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(3, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(4, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(5, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(6, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(7, 1) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_player_cards(1).ans() == 4);
        REQUIRE(world_cup->get_player_cards(2).ans() == 3);
        REQUIRE(world_cup->get_player_cards(3).ans() == 3);
        REQUIRE(world_cup->get_player_cards(4).ans() == 6);
        REQUIRE(world_cup->get_player_cards(5).ans() == 7);
        REQUIRE(world_cup->get_player_cards(6).ans() == 8);
        REQUIRE(world_cup->get_player_cards(7).ans() == 9);

        REQUIRE(world_cup->add_player(8, 1, per8, 0, 0, 8, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_player_cards(8).ans() == 8);
        REQUIRE(world_cup->add_player_cards(8, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->get_player_cards(8).ans() == 9);

        REQUIRE(world_cup->add_team(3) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(9, 3, per9, 0, 0, 9, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(10, 3, per10, 0, 0, 10, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_player_cards(9).ans() == 9);
        REQUIRE(world_cup->get_player_cards(10).ans() == 10);
        REQUIRE(world_cup->add_player_cards(9, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(10, 1) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_player_cards(9).ans() == 10);
        REQUIRE(world_cup->get_player_cards(10).ans() == 11);

        REQUIRE(world_cup->buy_team(1, 3) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_player_cards(1).ans() == 4);
        REQUIRE(world_cup->get_player_cards(2).ans() == 3);
        REQUIRE(world_cup->get_player_cards(3).ans() == 3);
        REQUIRE(world_cup->get_player_cards(4).ans() == 6);
        REQUIRE(world_cup->get_player_cards(5).ans() == 7);
        REQUIRE(world_cup->get_player_cards(6).ans() == 8);
        REQUIRE(world_cup->get_player_cards(7).ans() == 9);
        REQUIRE(world_cup->get_player_cards(8).ans() == 9);
        REQUIRE(world_cup->get_player_cards(9).ans() == 10);
        REQUIRE(world_cup->get_player_cards(10).ans() == 11);

        REQUIRE(world_cup->add_player_cards(1, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(2, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(3, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(4, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(5, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(6, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(7, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(8, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(9, 1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player_cards(10, 1) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_player_cards(1).ans() == 5);
        REQUIRE(world_cup->get_player_cards(2).ans() == 4);
        REQUIRE(world_cup->get_player_cards(3).ans() == 4);
        REQUIRE(world_cup->get_player_cards(4).ans() == 7);
        REQUIRE(world_cup->get_player_cards(5).ans() == 8);
        REQUIRE(world_cup->get_player_cards(6).ans() == 9);
        REQUIRE(world_cup->get_player_cards(7).ans() == 10);
        REQUIRE(world_cup->get_player_cards(8).ans() == 10);
        REQUIRE(world_cup->get_player_cards(9).ans() == 11);
        REQUIRE(world_cup->get_player_cards(10).ans() == 12);

        delete world_cup;
    }

    SECTION("get_team_points")
    {
        world_cup_t *world_cup = new world_cup_t();

        REQUIRE(world_cup->add_player_cards(-2, 0) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player_cards(-3, 3) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player_cards(1, -1) == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->add_player_cards(1, 2) == StatusType::FAILURE);

        int p1[5] = {4, 2, 3, 1, 0}, p2[5] = {0, 4, 2, 1, 3}, p3[5] = {4, 2, 3, 1, 0};
        int p4[5] = {2, 4, 3, 1, 0}, p5[5] = {0, 2, 1, 4, 3}, p6[5] = {1, 2, 3, 4, 0}, p7[5] = {1, 3, 2, 4, 0};
        int p8[5] = {1, 4, 0, 2, 3}, p9[5] = {1, 0, 4, 2, 3}, p10[5] = {3, 2, 4, 1, 0}, p11[5] = {3, 1, 2, 4, 0};
        int p12[5] = {3, 0, 2, 1, 4}, p13[5] = {3, 0, 1, 4, 2}, p14[5] = {1, 2, 0, 3, 4};
        permutation_t per1(p1), per2(p2), per3(p3), per4(p4), per5(p5), per6(p6), per7(p7), per8(p8), per9(p9), per10(p10), per11(p11), per12(p12), per13(p13), per14(p14);

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);

        REQUIRE(world_cup->add_player(1, 1, per1, 0, 0, 1, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(2, 1, per2, 0, 1, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(3, 1, per3, 1, 0, 0, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_team_points(1).ans() == 0);

        REQUIRE(world_cup->add_team(2) == StatusType::SUCCESS);

        REQUIRE(world_cup->add_player(4, 2, per4, 0, 0, 4, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(5, 2, per5, 0, 2, 5, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(6, 2, per6, 1, -4, 6, true) == StatusType::SUCCESS);

        // team 1 wins
        REQUIRE(world_cup->play_match(1, 2).status() == StatusType::SUCCESS);

        REQUIRE(world_cup->get_team_points(1).ans() == 3);
        REQUIRE(world_cup->get_team_points(2).ans() == 0);

        REQUIRE(world_cup->add_player(7, 2, per7, 0, 10, 7, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_team_points(1).ans() == 3);
        REQUIRE(world_cup->get_team_points(2).ans() == 0);

        // team 2 wins
        REQUIRE(world_cup->play_match(1, 2).status() == StatusType::SUCCESS);

        REQUIRE(world_cup->get_team_points(1).ans() == 3);
        REQUIRE(world_cup->get_team_points(2).ans() == 3);

        REQUIRE(world_cup->play_match(1, 2).status() == StatusType::SUCCESS);
        REQUIRE(world_cup->play_match(1, 2).status() == StatusType::SUCCESS);
        REQUIRE(world_cup->play_match(1, 2).status() == StatusType::SUCCESS);

        REQUIRE(world_cup->get_team_points(1).ans() == 3);
        REQUIRE(world_cup->get_team_points(2).ans() == 12);

        REQUIRE(world_cup->buy_team(2, 1) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_team_points(1).status() == StatusType::FAILURE);
        REQUIRE(world_cup->get_team_points(2).ans() == 15);

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(9, 1, per9, 0, 0, 9, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(10, 1, per10, 0, -3, 10, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_team_points(1).ans() == 0);

        REQUIRE(world_cup->buy_team(2, 1) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_team_points(2).ans() == 15);
        REQUIRE(world_cup->get_team_points(1).status() == StatusType::FAILURE);

        REQUIRE(world_cup->add_team(3) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(11, 3, per11, 0, 100, 9, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(12, 3, per12, 0, 100, 10, true) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_team_points(3).ans() == 0);

        // team 3 wins
        REQUIRE(world_cup->play_match(2, 3).status() == StatusType::SUCCESS);
        REQUIRE(world_cup->get_team_points(2).ans() == 15);
        REQUIRE(world_cup->get_team_points(3).ans() == 3);

        REQUIRE(world_cup->buy_team(3, 2) == StatusType::SUCCESS);

        REQUIRE(world_cup->get_team_points(2).status() == StatusType::FAILURE);
        REQUIRE(world_cup->get_team_points(3).ans() == 18);

        delete world_cup;
    }

    SECTION("get_ith_pointless_ability")
    {
    }

    SECTION("get_partial_spirit")
    {
        world_cup_t *world_cup = new world_cup_t();

        REQUIRE(world_cup->get_partial_spirit(-2).status() == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->get_partial_spirit(-3).status() == StatusType::INVALID_INPUT);
        REQUIRE(world_cup->get_partial_spirit(1).status() == StatusType::FAILURE);

        int p1[5] = {4, 2, 3, 1, 0}, p2[5] = {0, 4, 2, 1, 3}, p3[5] = {4, 2, 3, 1, 0};
        int p4[5] = {2, 4, 3, 1, 0}, p5[5] = {0, 2, 1, 4, 3}, p6[5] = {1, 2, 3, 4, 0}, p7[5] = {1, 3, 2, 4, 0};
        int p8[5] = {1, 4, 0, 2, 3}, p9[5] = {1, 0, 4, 2, 3}, p10[5] = {3, 2, 4, 1, 0}, p11[5] = {3, 1, 2, 4, 0};
        int p12[5] = {3, 0, 2, 1, 4}, p13[5] = {3, 0, 1, 4, 2}, p14[5] = {1, 2, 0, 3, 4};
        permutation_t per1(p1), per2(p2), per3(p3), per4(p4), per5(p5), per6(p6), per7(p7), per8(p8), per9(p9), per10(p10), per11(p11), per12(p12), per13(p13), per14(p14);

        REQUIRE(world_cup->add_team(1) == StatusType::SUCCESS);

        REQUIRE(world_cup->add_player(1, 1, per1, 0, 0, 1, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(2, 1, per2, 0, 1, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(3, 1, per3, 1, 0, 0, true) == StatusType::SUCCESS);

        REQUIRE(isSame(world_cup->get_partial_spirit(1).ans(), per1) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(2).ans(), per1 * per2) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(3).ans(), per1 * per2 * per3) == true);

        REQUIRE(world_cup->add_team(2) == StatusType::SUCCESS);

        REQUIRE(world_cup->add_player(4, 2, per4, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(5, 2, per5, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(6, 2, per6, 0, 0, 0, true) == StatusType::SUCCESS);
        REQUIRE(world_cup->add_player(7, 2, per7, 0, 0, 0, true) == StatusType::SUCCESS);

        REQUIRE(isSame(world_cup->get_partial_spirit(4).ans(), per4) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(5).ans(), per4 * per5) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(6).ans(), per4 * per5 * per6) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(7).ans(), per4 * per5 * per6 * per7) == true);

        REQUIRE(world_cup->buy_team(1, 2) == StatusType::SUCCESS);
        REQUIRE(isSame(world_cup->get_partial_spirit(1).ans(), per1) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(2).ans(), per1 * per2) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(3).ans(), per1 * per2 * per3) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(4).ans(), per1 * per2 * per3 * per4) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(5).ans(), per1 * per2 * per3 * per4 * per5) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(6).ans(), per1 * per2 * per3 * per4 * per5 * per6) == true);
        REQUIRE(isSame(world_cup->get_partial_spirit(7).ans(), per1 * per2 * per3 * per4 * per5 * per6 * per7) == true);
    }

    SECTION("buy_team")
    {
    }
}

TEST_CASE("upside_node")
{
    SECTION("Size")
    {
        std::shared_ptr<Player> p1(new Player(1));
        Upside_Node n1(p1);
        Upside_Node n2(p1);
        REQUIRE(n1.size == 1);
        REQUIRE(n2.size == 1);
        linkNodes(&n1, &n2);
        REQUIRE(n1.size == 2);
        REQUIRE(n2.size == 1);
        Upside_Node n3(p1);
        linkNodes(&n2, &n3);
        REQUIRE(n1.size == 3);
        REQUIRE(n2.size == 2);
        REQUIRE(n3.size == 1);
        Upside_Node n4(p1);
        linkNodes(&n2, &n4);
        REQUIRE(n1.size == 4);
        REQUIRE(n2.size == 3);
        REQUIRE(n3.size == 1);
        REQUIRE(n4.size == 1);
        Upside_Node n5(p1);
        linkNodes(&n4, &n5);
        Upside_Node n6(p1);
        linkNodes(&n4, &n6);
        REQUIRE(n1.size == 6);
        REQUIRE(n2.size == 5);
        REQUIRE(n3.size == 1);
        REQUIRE(n4.size == 3);
        REQUIRE(n5.size == 1);
        REQUIRE(n6.size == 1);
        Upside_Node n7(p1);
        linkNodes(&n3, &n7);
        REQUIRE(n1.size == 7);
        REQUIRE(n2.size == 6);
        REQUIRE(n3.size == 2);
        REQUIRE(n4.size == 3);
        REQUIRE(n5.size == 1);
        REQUIRE(n6.size == 1);
        REQUIRE(n7.size == 1);

        REQUIRE(find(&n3) == &n1);
        REQUIRE(n1.size == 7);
        REQUIRE(n2.size == 4);
        REQUIRE(n3.size == 2);
        REQUIRE(n4.size == 3);
        REQUIRE(n5.size == 1);
        REQUIRE(n6.size == 1);
        REQUIRE(n7.size == 1);

        REQUIRE(find(&n7) == &n1);
        REQUIRE(n1.size == 7);
        REQUIRE(n2.size == 4);
        REQUIRE(n3.size == 1);
        REQUIRE(n4.size == 3);
        REQUIRE(n5.size == 1);
        REQUIRE(n6.size == 1);
        REQUIRE(n7.size == 1);

        REQUIRE(find(&n5) == &n1);
        REQUIRE(n1.size == 7);
        REQUIRE(n2.size == 1);
        REQUIRE(n3.size == 1);
        REQUIRE(n4.size == 2);
        REQUIRE(n5.size == 1);
        REQUIRE(n6.size == 1);
        REQUIRE(n7.size == 1);

        REQUIRE(find(&n6) == &n1);
        REQUIRE(n1.size == 7);
        REQUIRE(n2.size == 1);
        REQUIRE(n3.size == 1);
        REQUIRE(n4.size == 1);
        REQUIRE(n5.size == 1);
        REQUIRE(n6.size == 1);
        REQUIRE(n7.size == 1);

        Upside_Node node11(p1);
        Upside_Node node12(p1);
        Upside_Node node13(p1);
        linkNodes(&node11, &node12);
        linkNodes(&node11, &node13);
        REQUIRE(node11.size == 3);
        REQUIRE(node12.size == 1);
        REQUIRE(node13.size == 1);

        union_tree(&n1, &node11);
        REQUIRE(n1.size == 10);
        REQUIRE(n2.size == 1);
        REQUIRE(n3.size == 1);
        REQUIRE(n4.size == 1);
        REQUIRE(n5.size == 1);
        REQUIRE(n6.size == 1);
        REQUIRE(n7.size == 1);
        REQUIRE(node11.size == 3);
        REQUIRE(node12.size == 1);
        REQUIRE(node13.size == 1);
    }

    SECTION("Is Root")
    {
        std::shared_ptr<Player> p1(new Player(1));
        Upside_Node n1(p1);
        Upside_Node n2(p1);
        REQUIRE(n1.isRoot == true);
        REQUIRE(n2.isRoot == true);
        linkNodes(&n1, &n2);
        REQUIRE(n1.isRoot == true);
        REQUIRE(n2.isRoot == false);
        Upside_Node n3(p1);
        linkNodes(&n2, &n3);
        REQUIRE(n1.isRoot == true);
        REQUIRE(n2.isRoot == false);
        REQUIRE(n3.isRoot == false);
        Upside_Node n4(p1);
        linkNodes(&n2, &n4);
        REQUIRE(n1.isRoot == true);
        REQUIRE(n2.isRoot == false);
        REQUIRE(n3.isRoot == false);
        REQUIRE(n4.isRoot == false);
        Upside_Node n5(p1);
        linkNodes(&n4, &n5);
        Upside_Node n6(p1);
        linkNodes(&n4, &n6);
        REQUIRE(n1.isRoot == true);
        REQUIRE(n2.isRoot == false);
        REQUIRE(n3.isRoot == false);
        REQUIRE(n4.isRoot == false);
        REQUIRE(n5.isRoot == false);
        REQUIRE(n6.isRoot == false);

        REQUIRE(find(&n3) == &n1);
        REQUIRE(n1.isRoot == true);
        REQUIRE(n2.isRoot == false);
        REQUIRE(n3.isRoot == false);
        REQUIRE(n4.isRoot == false);
        REQUIRE(n5.isRoot == false);
        REQUIRE(n6.isRoot == false);

        REQUIRE(find(&n5) == &n1);
        REQUIRE(n1.isRoot == true);
        REQUIRE(n2.isRoot == false);
        REQUIRE(n3.isRoot == false);
        REQUIRE(n4.isRoot == false);
        REQUIRE(n5.isRoot == false);
        REQUIRE(n6.isRoot == false);

        Upside_Node node11(p1);
        Upside_Node node12(p1);
        Upside_Node node13(p1);
        linkNodes(&node11, &node12);
        linkNodes(&node11, &node13);
        REQUIRE(node11.isRoot == true);
        REQUIRE(node12.isRoot == false);
        REQUIRE(node13.isRoot == false);

        union_tree(&n1, &node11);
        REQUIRE(n1.isRoot == true);
        REQUIRE(n2.isRoot == false);
        REQUIRE(n3.isRoot == false);
        REQUIRE(n4.isRoot == false);
        REQUIRE(n5.isRoot == false);
        REQUIRE(n6.isRoot == false);
        REQUIRE(node11.isRoot == false);
        REQUIRE(node12.isRoot == false);
        REQUIRE(node13.isRoot == false);
    }
}

TEST_CASE("Find ")
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

    SECTION(" find with union")
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
        std::shared_ptr<Player> p1(new Player(1, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));
        std::shared_ptr<Player> p2(new Player(2, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));
        std::shared_ptr<Player> p3(new Player(3, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));

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
        std::shared_ptr<Player> p4(new Player(4, 0, 0, true, 0, demi_per, 1, team1->getTeamSpirit(), team1.get()));
        Upside_Node node4(p4);
        linkNodes(&node1, &node4);
        REQUIRE(getPlayerTotalGames(&node4) == 0);

        // team played 2 games
        node1.games_to_add++;
        REQUIRE(getPlayerTotalGames(&node1) == 2);
        REQUIRE(getPlayerTotalGames(&node2) == 2);
        REQUIRE(getPlayerTotalGames(&node3) == 2);
        REQUIRE(getPlayerTotalGames(&node4) == 1);

        std::shared_ptr<Player> p5(new Player(5, 0, 0, true, 0, demi_per, 2, team1->getTeamSpirit(), team1.get()));
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

        std::shared_ptr<Player> p6(new Player(6, 0, 0, true, 0, demi_per, 4, team1->getTeamSpirit(), team1.get()));
        Upside_Node node6(p6);
        linkNodes(&node1, &node6);
        REQUIRE(getPlayerTotalGames(&node6) == 0);

        // team played 5 games
        node1.games_to_add++;
        std::shared_ptr<Player> p7(new Player(7, 0, 0, true, 0, demi_per, 5, team1->getTeamSpirit(), team1.get()));
        Upside_Node node7(p7);
        std::shared_ptr<Player> p8(new Player(8, 0, 0, true, 0, demi_per, 5, team1->getTeamSpirit(), team1.get()));
        Upside_Node node8(p8);

        // team played 6 games
        node1.games_to_add++;

        std::shared_ptr<Player> p9(new Player(9, 0, 0, true, 0, demi_per, 6, team1->getTeamSpirit(), team1.get()));
        Upside_Node node9(p9);
        std::shared_ptr<Player> p10(new Player(10, 1, 0, true, 0, demi_per, 6, team1->getTeamSpirit(), team1.get()));
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

    // SECTION("Find - spirit updates")
    // {
    //     std::shared_ptr<Team> team1(new Team(1));
    //     permutation_t per1, per2, per3;
    //     std::shared_ptr<Player> p1(new Player(1, 0, 0, true, 0, per1, 0, team1->getTeamSpirit(), team1.get()));
    //     team1->handlePlayerAdded(p1.get());
    //     std::shared_ptr<Player> p2(new Player(2, 0, 0, true, 0, per2, 0, team1->getTeamSpirit(), team1.get()));
    //     team1->handlePlayerAdded(p2.get());
    //     std::shared_ptr<Player> p3(new Player(3, 0, 0, true, 0, per3, 0, team1->getTeamSpirit(), team1.get()));
    //     Upside_Node node1(p1);
    //     Upside_Node node2(p2);
    //     Upside_Node node3(p3);
    //     linkNodes(&node1, &node2);
    //     linkNodes(&node2, &node3);
    //     REQUIRE(isSame(per2, per2) == true);

    //     REQUIRE(isSame(getPlayerTotalSpirit(&node1), per1) == true);
    //     REQUIRE(isSame(getPlayerTotalSpirit(&node2), per1 * per2) == true);
    //     REQUIRE(isSame(getPlayerTotalSpirit(&node3), per1 * per2 * per3) == true);
    // }
}

TEST_CASE("Union")
{

    SECTION("union by size")
    {
        std::shared_ptr<Player> p1(new Player(1));
        Upside_Node node5(p1);
        Upside_Node node6(p1);
        Upside_Node node7(p1);
        Upside_Node node8(p1);

        REQUIRE(union_tree(&node5, &node6) == &node5);
        REQUIRE(node5.size == 2);
        REQUIRE(node6.size == 1);
        REQUIRE(union_tree(&node5, &node7) == &node5);
        REQUIRE(node5.size == 3);
        REQUIRE(node6.size == 1);
        REQUIRE(node7.size == 1);

        REQUIRE(find(&node7) == &node5);
        REQUIRE(union_tree(&node8, &node5) == &node5);
        REQUIRE(node8.father == &node5);
        REQUIRE(node7.father == &node5);
        REQUIRE(node5.size == 4);
        REQUIRE(node8.size == 1);

        Upside_Node node1(p1);
        Upside_Node node2(p1);
        Upside_Node node3(p1);
        linkNodes(&node1, &node2);
        linkNodes(&node1, &node3);
        REQUIRE(union_tree(&node1, &node5) == &node5);
        REQUIRE(node5.size == 7);
        REQUIRE(node1.size == 3);
        REQUIRE(node1.isRoot == false);
        REQUIRE(node5.isRoot == true);

        Upside_Node node11(p1);
        Upside_Node node12(p1);
        Upside_Node node13(p1);
        linkNodes(&node11, &node12);
        linkNodes(&node11, &node13);
        REQUIRE(union_tree(&node5, &node11) == &node5);
        REQUIRE(node5.size == 10);
        REQUIRE(node11.size == 3);
        REQUIRE(node11.isRoot == false);
        REQUIRE(node5.isRoot == true);
    }

    SECTION("union - Games Update")
    {
        std::shared_ptr<Team> team1(new Team(1));
        permutation_t demi_per;
        std::shared_ptr<Player> p1(new Player(1, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));
        std::shared_ptr<Player> p2(new Player(2, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));
        std::shared_ptr<Player> p3(new Player(3, 0, 0, true, 0, demi_per, 0, team1->getTeamSpirit(), team1.get()));

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
        std::shared_ptr<Player> p4(new Player(4, 0, 0, true, 0, demi_per, 1, team1->getTeamSpirit(), team1.get()));
        Upside_Node node4(p4);
        linkNodes(&node1, &node4);
        REQUIRE(getPlayerTotalGames(&node4) == 0);

        std::shared_ptr<Team> team2(new Team(2));
        std::shared_ptr<Player> p11(new Player(1, 0, 0, true, 0, demi_per, 0, team2->getTeamSpirit(), team2.get()));
        std::shared_ptr<Player> p12(new Player(2, 0, 0, true, 0, demi_per, 0, team2->getTeamSpirit(), team2.get()));
        std::shared_ptr<Player> p13(new Player(3, 1, 0, true, 0, demi_per, 0, team2->getTeamSpirit(), team2.get()));

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

        REQUIRE(node1.size == 4);
        REQUIRE(node2.size == 1);
        REQUIRE(node3.size == 1);
        REQUIRE(node11.size == 3);
        REQUIRE(node12.size == 1);

        // unite when first root is bigger than second size
        REQUIRE(union_tree(&node1, &node11) == &node1);
        REQUIRE(node1.size == 7);
        REQUIRE(node11.size == 3);
        REQUIRE(getPlayerTotalGames(&node1) == 1);
        REQUIRE(getPlayerTotalGames(&node2) == 1);
        REQUIRE(getPlayerTotalGames(&node3) == 1);
        REQUIRE(getPlayerTotalGames(&node4) == 0);
        REQUIRE(getPlayerTotalGames(&node11) == 1);
        REQUIRE(getPlayerTotalGames(&node12) == 1);
        REQUIRE(node11.size == 2);
        REQUIRE(getPlayerTotalGames(&node13) == 2);
        REQUIRE(node11.size == 1);
        REQUIRE(find(&node11) == &node1);
        REQUIRE(find(&node3) == &node1);
        REQUIRE(find(&node13) == &node1);
        REQUIRE(getPlayerTotalGames(&node1) == 1);
        REQUIRE(getPlayerTotalGames(&node2) == 1);
        REQUIRE(getPlayerTotalGames(&node3) == 1);
        REQUIRE(getPlayerTotalGames(&node4) == 0);
        REQUIRE(getPlayerTotalGames(&node11) == 1);
        REQUIRE(getPlayerTotalGames(&node12) == 1);
        REQUIRE(getPlayerTotalGames(&node13) == 2);
        REQUIRE(node12.father == &node1);
        REQUIRE(node11.size == 1);
        REQUIRE(node2.size == 1);

        // united team play 1 games
        node1.games_to_add++;
        REQUIRE(getPlayerTotalGames(&node1) == 2);
        REQUIRE(getPlayerTotalGames(&node2) == 2);
        REQUIRE(getPlayerTotalGames(&node3) == 2);
        REQUIRE(getPlayerTotalGames(&node4) == 1);
        REQUIRE(getPlayerTotalGames(&node11) == 2);
        REQUIRE(getPlayerTotalGames(&node12) == 2);
        REQUIRE(getPlayerTotalGames(&node13) == 3);
    }
}