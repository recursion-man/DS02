#include "../catch.hpp"
#include "common.h"

TEST_CASE("Add team sanity", "[addTeam]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
}

TEST_CASE("team already exists", "[addTeam]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::FAILURE == worldCup.add_team(1));
}

TEST_CASE("invalid input", "[addTeam]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_team(-1));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.add_team(0));
}