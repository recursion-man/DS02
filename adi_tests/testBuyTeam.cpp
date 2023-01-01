#include "../catch.hpp"
#include "common.h"
#include <array>

constexpr const int teamA = 1;
constexpr const int teamB = 2;
constexpr const int teamC = 3;
constexpr const int teamD = 4;

TEST_CASE("buyTeam sanity", "[buyTeam]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamA));
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamB));
}

TEST_CASE("buyTeam input", "[buyTeam]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamA));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.buy_team(-1, teamB));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.buy_team(0, teamB));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.buy_team(teamA, -1));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.buy_team(teamA, 0));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.buy_team(teamA, teamA));
}

TEST_CASE("buyTeam team not exist", "[buyTeam]")
{
    world_cup_t worldCup;
    REQUIRE(StatusType::FAILURE == worldCup.buy_team(teamA, teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamA));
    REQUIRE(StatusType::FAILURE == worldCup.buy_team(teamA, teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamB));
}

TEST_CASE("buy team gamesPlayed correctness")
{

    world_cup_t worldCup;
    auto players_teamA = buildTeam(worldCup, teamA, 10, 1);
    auto players_teamB = buildTeam(worldCup, teamB, 50, 1);
    auto players_teamC = buildTeam(worldCup, teamC, 60, 1);
    auto players_teamD = buildTeam(worldCup, teamD, 60, 1);
    REQUIRE(StatusType::SUCCESS == worldCup.play_match(teamA, teamB).status());
    REQUIRE(StatusType::SUCCESS == worldCup.play_match(teamC, teamD).status());
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamD, teamC));
    for (auto player : players_teamA)
    {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    for (auto player : players_teamB)
    {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamD, teamA));
    for (auto player : players_teamA)
    {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    for (auto player : players_teamB)
    {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    for (auto player : players_teamC)
    {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
    for (auto player : players_teamD)
    {
        REQUIRE(1 == worldCup.num_played_games_for_player(player).ans());
    }
}

TEST_CASE("buy team points are combined and bought team is gone", "[buyTeam]")
{
    world_cup_t worldCup;
    buildTeam(worldCup, teamA, 10, 1);
    buildTeam(worldCup, teamB, 50, 1);
    REQUIRE(StatusType::SUCCESS == worldCup.play_match(teamA, teamB).status());
    REQUIRE(StatusType::FAILURE == worldCup.add_team(teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamB));
    REQUIRE(2 == worldCup.get_team_points(teamA).ans());
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamB));
}

TEST_CASE("buy team team spirit is correct")
{
    world_cup_t worldCup;
    auto players_teamA = buildTeam(worldCup, teamA, 10, 1);
    auto players_teamB = buildTeam(worldCup, teamB, 60, 1);
    auto players_teamC = buildTeam(worldCup, teamC, 30, 1);
    auto players_teamD = buildTeam(worldCup, teamD, 31, 1);
    std::array<int, 5> p{0, 2, 1, 3, 4};
    int *p1 = new int[5];
    p1 = get_array(p, p1);
    permutation_t permA{p1};
    std::next_permutation(p.begin(), p.end());
    p1 = get_array(p, p1);
    permutation_t permAAfter{p1};
    std::next_permutation(p.begin(), p.end());
    p1 = get_array(p, p1);
    permutation_t permB{p1};
    std::next_permutation(p.begin(), p.end());
    p1 = get_array(p, p1);
    permutation_t permC{p1};
    std::next_permutation(p.begin(), p.end());
    p1 = get_array(p, p1);

    permutation_t permD{p1};
    permutation_t permDAfter{p1};

    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, teamA, permA, 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(2, teamB, permB, 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamB));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(3, teamA, permAAfter, 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(5, teamD, permD, 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(4, teamC, permC, 0, 0, 0, false));
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamD, teamC));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(6, teamD, permDAfter, 0, 0, 0, false));

    for (auto player : players_teamA)
    {
        REQUIRE(permutation_t::neutral().strength() == worldCup.get_partial_spirit(player).ans().strength());
    }
    for (auto player : players_teamB)
    {
        REQUIRE(permA.strength() == worldCup.get_partial_spirit(player).ans().strength());
    }

    REQUIRE(permA.strength() == worldCup.get_partial_spirit(1).ans().strength());
    REQUIRE((permA * permB).strength() == worldCup.get_partial_spirit(2).ans().strength());
    REQUIRE((permA * permB * permAAfter).strength() == worldCup.get_partial_spirit(3).ans().strength());
    REQUIRE(StatusType::SUCCESS == worldCup.buy_team(teamA, teamD));

    for (auto player : players_teamA)
    {
        REQUIRE(permutation_t::neutral().strength() == worldCup.get_partial_spirit(player).ans().strength());
    }
    for (auto player : players_teamB)
    {
        REQUIRE(permA.strength() == worldCup.get_partial_spirit(player).ans().strength());
    }

    for (auto player : players_teamC)
    {

        REQUIRE((permA * permB * permAAfter * permD).strength() == worldCup.get_partial_spirit(player).ans().strength());
    }
    for (auto player : players_teamD)
    {
        REQUIRE((permA * permB * permAAfter).strength() == worldCup.get_partial_spirit(player).ans().strength());
    }

    REQUIRE((permA * permB * permAAfter * permD).strength() == worldCup.get_partial_spirit(5).ans().strength());
    REQUIRE((permA * permB * permAAfter * permD * permC).strength() == worldCup.get_partial_spirit(4).ans().strength());
    REQUIRE((permA * permB * permAAfter * permD * permC * permDAfter).strength() == worldCup.get_partial_spirit(6).ans().strength());

    delete p1;
}