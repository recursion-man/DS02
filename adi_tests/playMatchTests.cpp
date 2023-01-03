#include "../catch.hpp"
#include "common.h"
#include <array>

constexpr const int TEAM_A = 1;
constexpr const int TEAM_B = 2;
constexpr const int TEAM_C = 3;
constexpr const int NUM_PLAYERS = 10;
constexpr const int FIRST_TEAM_BY_ABILITY = 1;
constexpr const int SECOND_TEAM_BY_ABILITY = 3;
constexpr const int TIE = 0;

constexpr const int FIRST_TEAM_BY_SPIRIT = 2;
constexpr const int SECOND_TEAM_BY_SPIRIT = 4;

TEST_CASE("playMatchSanity", "[playMatch]")
{
    world_cup_t worldCup;
    buildTeam(worldCup, TEAM_A, NUM_PLAYERS, 1);
    buildTeam(worldCup, TEAM_B, NUM_PLAYERS, 1);
    REQUIRE(TIE == worldCup.play_match(TEAM_A, TEAM_B).ans());
}

TEST_CASE("playMatch points", "[playMatch]")
{
    world_cup_t worldCup;
    buildTeam(worldCup, TEAM_A, NUM_PLAYERS, 1);
    buildTeam(worldCup, TEAM_B, NUM_PLAYERS, 1);
    buildTeam(worldCup, TEAM_C, NUM_PLAYERS, 1);
    REQUIRE(TIE == worldCup.play_match(TEAM_A, TEAM_B).ans());                    // 1-1-0
    REQUIRE(FIRST_TEAM_BY_ABILITY == worldCup.play_match(TEAM_A, TEAM_C).ans());  // 4-1-0
    REQUIRE(FIRST_TEAM_BY_ABILITY == worldCup.play_match(TEAM_A, TEAM_B).ans());  // 7-1-0
    REQUIRE(FIRST_TEAM_BY_ABILITY == worldCup.play_match(TEAM_B, TEAM_C).ans());  // 7-4-0
    REQUIRE(FIRST_TEAM_BY_ABILITY == worldCup.play_match(TEAM_B, TEAM_C).ans());  // 7-7-0
    REQUIRE(TIE == worldCup.play_match(TEAM_A, TEAM_B).ans());                    // 8-8-0
    REQUIRE(FIRST_TEAM_BY_ABILITY == worldCup.play_match(TEAM_B, TEAM_C).ans());  // 8-11-0
    REQUIRE(SECOND_TEAM_BY_ABILITY == worldCup.play_match(TEAM_A, TEAM_B).ans()); // 8 - 14 - 0
    REQUIRE(8 == worldCup.get_team_points(TEAM_A).ans());
    REQUIRE(14 == worldCup.get_team_points(TEAM_B).ans());
    REQUIRE(0 == worldCup.get_team_points(TEAM_C).ans());
}

TEST_CASE("playMatch playerAbility", "[playMatch]")
{
    world_cup_t worldCup;
    buildTeam(worldCup, TEAM_A, NUM_PLAYERS, 1);
    buildTeam(worldCup, TEAM_B, NUM_PLAYERS, 1);
    REQUIRE(TIE == worldCup.play_match(TEAM_A, TEAM_B).ans());
    worldCup.add_player(1, TEAM_A, permutation_t::neutral(), 0, 1, 0, false);
    REQUIRE(FIRST_TEAM_BY_ABILITY == worldCup.play_match(TEAM_A, TEAM_B).ans());
    worldCup.add_player(2, TEAM_B, permutation_t::neutral(), 0, 10, 0, false);
    REQUIRE(SECOND_TEAM_BY_ABILITY == worldCup.play_match(TEAM_A, TEAM_B).ans());
}

TEST_CASE("playMatch getGamesPlayed", "[playMatch]")
{
    world_cup_t worldCup;
    auto players_A = buildTeam(worldCup, TEAM_A, NUM_PLAYERS, 1);
    worldCup.add_player(1, TEAM_A, permutation_t::neutral(), 3, 0, 0, false);
    auto players_B = buildTeam(worldCup, TEAM_B, NUM_PLAYERS, 1);
    REQUIRE(TIE == worldCup.play_match(TEAM_A, TEAM_B).ans());
    worldCup.add_player(2, TEAM_A, permutation_t::neutral(), 3, 0, 0, false);
    for (auto player : players_A)
    {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    for (auto player : players_B)
    {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    REQUIRE(4 == worldCup.num_played_games_for_player(1).ans());
    REQUIRE(3 == worldCup.num_played_games_for_player(2).ans());
}

TEST_CASE("playMatch by spirit", "[playMatch]")
{
    std::array<int, 5> team_A_spirit{0, 1, 2, 3, 4};
    int team_A_spirit1[5] = {0, 1, 2, 3, 4};

    do
    {
        std::array<int, 5> team_B_spirit{0, 1, 2, 3, 4};
        int team_B_spirit1[5] = {0, 1, 2, 3, 4};

        do
        {
            world_cup_t worldCup;
            auto players_A = buildTeam(worldCup, TEAM_A, NUM_PLAYERS, 1);
            auto players_B = buildTeam(worldCup, TEAM_B, NUM_PLAYERS, 1);
            auto permA = permutation_t{team_A_spirit1};
            auto permB = permutation_t{team_B_spirit1};
            REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, TEAM_A, permA, 0, 0, 0, false));
            REQUIRE(StatusType::SUCCESS == worldCup.add_player(2, TEAM_B, permB, 0, 0, 0, false));
            if (permA.strength() > permB.strength())
            {
                REQUIRE(FIRST_TEAM_BY_SPIRIT == worldCup.play_match(TEAM_A, TEAM_B).ans());
            }
            else if (permA.strength() < permB.strength())
            {
                REQUIRE(SECOND_TEAM_BY_SPIRIT == worldCup.play_match(TEAM_A, TEAM_B).ans());
            }
            else
            {
                REQUIRE(TIE == worldCup.play_match(TEAM_A, TEAM_B).ans());
            }

        } while (std::next_permutation(team_B_spirit.begin(), team_B_spirit.end()));
    } while (std::next_permutation(team_A_spirit.begin(), team_A_spirit.end()));
}

TEST_CASE("playMatch input", "[playMatch]")
{
    world_cup_t worldCup;
    buildTeam(worldCup, TEAM_A, NUM_PLAYERS, 1);
    buildTeam(worldCup, TEAM_B, NUM_PLAYERS, 1);
    REQUIRE(StatusType::INVALID_INPUT == worldCup.play_match(-1, TEAM_A).status());
    REQUIRE(StatusType::INVALID_INPUT == worldCup.play_match(0, TEAM_A).status());
    REQUIRE(StatusType::INVALID_INPUT == worldCup.play_match(TEAM_A, -1).status());
    REQUIRE(StatusType::INVALID_INPUT == worldCup.play_match(TEAM_A, 0).status());
    REQUIRE(StatusType::INVALID_INPUT == worldCup.play_match(TEAM_A, 1).status());
    REQUIRE(StatusType::SUCCESS == worldCup.play_match(TEAM_A, TEAM_B).status());
}

TEST_CASE("playMatch team doesnt exist", "[playMatch]")
{
    world_cup_t worldCup;
    buildTeam(worldCup, TEAM_A, NUM_PLAYERS, 1);
    REQUIRE(StatusType::FAILURE == worldCup.play_match(TEAM_A, TEAM_B).status());
    REQUIRE(StatusType::FAILURE == worldCup.play_match(TEAM_B, TEAM_A).status());
    buildTeam(worldCup, TEAM_B, NUM_PLAYERS, 1);
    REQUIRE(StatusType::SUCCESS == worldCup.play_match(TEAM_A, TEAM_B).status());
}

TEST_CASE("playMatch team not eligible", "[playMatch]")
{
    world_cup_t worldCup;
    buildTeam(worldCup, TEAM_A, NUM_PLAYERS, 0);
    buildTeam(worldCup, TEAM_B, NUM_PLAYERS, 2);
    buildTeam(worldCup, TEAM_C, NUM_PLAYERS, 1);
    REQUIRE(StatusType::FAILURE == worldCup.play_match(TEAM_A, TEAM_B).status());
    REQUIRE(StatusType::FAILURE == worldCup.play_match(TEAM_B, TEAM_A).status());
    REQUIRE(StatusType::SUCCESS == worldCup.play_match(TEAM_C, TEAM_B).status());
}