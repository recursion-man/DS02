#include "../catch.hpp"
#include "common.h"

TEST_CASE("addPlayerCards sanity", "[addPlayerCards]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player_cards(1, 1));
    REQUIRE(1 == worldCup.get_player_cards(1).ans());
}

TEST_CASE("addPlayerCards invalid input", "[addPlayerCards]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_player_cards(-1, 1));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_player_cards(0, 1));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_player_cards(1, -1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player_cards(1, 0));
}

TEST_CASE("addPlayerCards team remove", "[addPlayerCards]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::SUCCESS == worldCup.remove_team(1));
    REQUIRE(StatusType::FAILURE == worldCup.add_player_cards(1, 1));
    REQUIRE(StatusType::SUCCESS == worldCup.get_player_cards(1).status());
}

TEST_CASE("addPlayerCards doesnt exist")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::FAILURE == worldCup.add_player_cards(1, 1));
}