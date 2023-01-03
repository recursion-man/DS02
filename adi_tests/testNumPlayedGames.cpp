#include "../catch.hpp"
#include "common.h"

TEST_CASE("numPlayedGames sanity", "[NumGetPlayedGamesForPlayer]") {
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 0, 0, 0, true));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(2, 1, permutation_t::neutral(), 1, 0, 0, true));
    REQUIRE(0 == worldCup.num_played_games_for_player(1).ans());
    REQUIRE(1 == worldCup.num_played_games_for_player(2).ans());
}

TEST_CASE("numPlayedGames representative initial games dont matter", "[NumGetPlayedGamesForPlayer]") {
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 1, 0, 0, true));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(2, 1, permutation_t::neutral(), 1, 0, 0, true));
    REQUIRE(1 == worldCup.num_played_games_for_player(1).ans());
    REQUIRE(1 == worldCup.num_played_games_for_player(2).ans());
}

TEST_CASE("numPlayedGames get games after team remove", "[NumGetPlayedGamesForPlayer]") {
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 1, 0, 0, true));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(2, 1, permutation_t::neutral(), 1, 0, 0, true));
    REQUIRE(StatusType::SUCCESS == worldCup.remove_team(1));
    REQUIRE(1 == worldCup.num_played_games_for_player(1).ans());
    REQUIRE(1 == worldCup.num_played_games_for_player(2).ans());
}

TEST_CASE("numPlayedGames test input", "[NumGetPlayedGamesForPlayer]") {
    world_cup_t worldCup;
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(1));
    REQUIRE(StatusType::SUCCESS == worldCup.add_player(1, 1, permutation_t::neutral(), 1, 0, 0, true));
    REQUIRE(StatusType::INVALID_INPUT == worldCup.num_played_games_for_player(-1).status());
    REQUIRE(StatusType::INVALID_INPUT == worldCup.num_played_games_for_player(0).status());
    REQUIRE(StatusType::SUCCESS == worldCup.num_played_games_for_player(1).status());
}