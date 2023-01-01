#include "../catch.hpp"
#include "common.h"

TEST_CASE("get team points sanity", "[getTeamPoints]")
{
    world_cup_t worldCup;
    buildTeam(worldCup, 1, 1, 1);
    buildTeam(worldCup, 2, 1, 1);
    REQUIRE(0 == worldCup.get_team_points(1).ans());
    REQUIRE(0 == worldCup.get_team_points(2).ans());
    REQUIRE(StatusType::SUCCESS == worldCup.play_match(1, 2).status());
    REQUIRE(1 == worldCup.get_team_points(1).ans());
    REQUIRE(1 == worldCup.get_team_points(2).ans());
}

TEST_CASE("get team points invalid input", "[getTeamPoints]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::INVALID_INPUT == worldCup.get_team_points(-1).status());
    REQUIRE(StatusType::INVALID_INPUT == worldCup.get_team_points(0).status());
}

TEST_CASE("get team points team doesnt exist", "[getTeamPoints")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::FAILURE == worldCup.get_team_points(1).status());
}

TEST_CASE("get team points team after remove", "[getTeamPoints")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.get_team_points(1).status());
    REQUIRE(StatusType::SUCCESS == worldCup.remove_team(1));
    REQUIRE(StatusType::FAILURE == worldCup.get_team_points(1).status());
}
