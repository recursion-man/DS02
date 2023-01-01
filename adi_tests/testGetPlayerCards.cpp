#include "../catch.hpp"
#include "common.h"

TEST_CASE("getPlayerCards sanity", "[getPlayerCards]") {
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player_cards(1, 1));
    REQUIRE(1 == worldCup.get_player_cards(1).ans());
}

TEST_CASE("getPlayerCards invalid input", "[getPlayerCards]") {
    world_cup_t worldCup;
    REQUIRE(StatusType::INVALID_INPUT == worldCup.get_player_cards(-1).status());
    REQUIRE(StatusType::INVALID_INPUT == worldCup.get_player_cards(0).status());
}

TEST_CASE("getPlayerCards team remove", "[getPlayerCards]") {
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::SUCCESS == worldCup.remove_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.get_player_cards(1).status());
}

TEST_CASE("getPlayerCards doesnt exist") {
    world_cup_t worldCup;
    REQUIRE(StatusType::FAILURE == worldCup.get_player_cards(1).status());
}