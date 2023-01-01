#include "../catch.hpp"
#include "common.h"
#include <array>

TEST_CASE("get ith pointless ability sanity", "[getIthPointlessAbility]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(2));
    REQUIRE(2 == worldCup.get_ith_pointless_ability(0).ans());
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(1 == worldCup.get_ith_pointless_ability(0).ans());
}

TEST_CASE("get ith pointless ability input", "[getIthPointlessAbility]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::FAILURE == worldCup.get_ith_pointless_ability(0).status());
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::FAILURE == worldCup.get_ith_pointless_ability(-1).status());
    REQUIRE(StatusType::FAILURE == worldCup.get_ith_pointless_ability(1).status());
    REQUIRE(StatusType::SUCCESS == worldCup.get_ith_pointless_ability(0).status());
}

TEST_CASE("get ith pointless ability order", "[getIthPointlessAbility]")
{
    std::array<int, 6> team_ids{1, 2, 3, 4, 5, 6};
    do
    {
        world_cup_t worldCup;
        for (int i = 0; i < 6; ++i)
        {
            REQUIRE(StatusType::SUCCESS == worldCup.add_team(team_ids[i]));
            REQUIRE(StatusType::SUCCESS ==
                    worldCup.add_player(team_ids[i], team_ids[i], permutation_t::neutral(), 0, i, 0, false));
        }
        for (int i = 0; i < 6; ++i)
        {
            REQUIRE(team_ids[i] == worldCup.get_ith_pointless_ability(i).ans());
        }
    } while (std::next_permutation(team_ids.begin(), team_ids.end()));
}