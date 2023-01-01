#include "../catch.hpp"
#include "common.h"

TEST_CASE("addPlayer sanity", "[addPlayer]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
}

TEST_CASE("addPlayer already exists", "[addPlayer]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(2));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::FAILURE == worldCup.add_player(1, 2, permutation_t::neutral(), 0, 0, 0, true));
}

TEST_CASE("addPlayer invalid input", "[addPlayer]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_player(-1, 1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_player(0, 1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_player(1, -1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_player(1, 0, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_player(1, 1, permutation_t::invalid(), 0, 0, 0, true));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_player(1, 1, permutation_t::neutral(), -1, 0, 0, true));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, -1, true));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
}

TEST_CASE("player doesnt affect team remove", "[addPlayer]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::SUCCESS == worldCup.remove_team(1));
    REQUIRE(StatusType::FAILURE == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
}

TEST_CASE("spirit can be negative", "[addPlayer]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, -1, 0, true));
}
