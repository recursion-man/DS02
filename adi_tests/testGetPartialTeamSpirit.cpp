#include "../catch.hpp"
#include "common.h"
#include <array>

TEST_CASE("testGetPartialTeamSpirit sanity", "[GetPartialTeamSpirit]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    int n[] = {2, 3, 4, 1, 0};
    permutation_t perm{n};
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, perm, 0, 0, 0, false));
    REQUIRE(perm.strength() == worldCup.get_partial_spirit(1).ans().strength());
}

TEST_CASE("testGetPartialTeamSpirit input", "[GetPartialTeamSpirit]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::INVALID_INPUT == worldCup.get_partial_spirit(-1).status());
    REQUIRE(StatusType::INVALID_INPUT == worldCup.get_partial_spirit(0).status());
}

TEST_CASE("testGetPartialTeamSpirit no such player", "[GetPartialTeamSpirit]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::FAILURE == worldCup.get_partial_spirit(1).status());
}

TEST_CASE("testGetPartialTeamSpirit player kicked", "[GetPartialTeamSpirit]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.get_partial_spirit(1).status());
    REQUIRE(StatusType::SUCCESS == worldCup.remove_team(1));
    REQUIRE(StatusType::FAILURE == worldCup.get_partial_spirit(1).status());
}

TEST_CASE("testGetPartialTeamSpirit correct", "[GetPartialTeamSpirit]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    std::array<int, 5> s{0, 1, 2, 3, 4};
    int *s_1 = new int[5];
    s_1 = get_array(s, s_1);
    for (int i = 0; i < 10; ++i)
    {
        REQUIRE(StatusType::SUCCESS == worldCup.add_player(i + 1, 1, permutation_t{s_1}, 0, 0, 0, false));
        std::next_permutation(s.begin(), s.end());
        s_1 = get_array(s, s_1);
    }
    std::array<int, 5> s2 = {0, 1, 2, 3, 4};
    int *s_2 = new int[5];
    s_2 = get_array(s2, s_2);
    permutation_t currentPartialSpirit{s_2};
    for (int i = 0; i < 10; ++i)
    {
        REQUIRE(currentPartialSpirit.strength() == worldCup.get_partial_spirit(i + 1).ans().strength());
        std::next_permutation(s2.begin(), s2.end());
        s_2 = get_array(s2, s_2);
        currentPartialSpirit = currentPartialSpirit * permutation_t{s_2};
    }
    delete s_1;
    delete s_2;
}
