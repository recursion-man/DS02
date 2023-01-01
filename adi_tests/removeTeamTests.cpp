#include "../catch.hpp"
#include "common.h"

TEST_CASE("remove team sanity", "[removeTeam]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.remove_team(1));
}

TEST_CASE("remove team doesnt exist", "[removeTeam]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::FAILURE == worldCup.remove_team(1));
}

TEST_CASE("remove team invalid input", "[removeTeam]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::INVALID_INPUT == worldCup.remove_team(-1));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.remove_team(0));
}

TEST_CASE("add after remove", "[removeTeam]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::FAILURE == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.remove_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
}
