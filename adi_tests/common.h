#pragma once

#include "config.h"
#include <array>
#include "../worldcup23a2.h"

inline std::vector<int> buildTeam(world_cup_t &worldCup, int teamId, int numPlayers, int numGoalKeepers)
{
    REQUIRE(StatusType::SUCCESS == worldCup.add_team(teamId));
    std::vector<int> players{};
    players.reserve(numPlayers);
    for (int i = 0; i < numPlayers; i++)
    {
        int playerId = 100 * teamId + i;
        if (numGoalKeepers > 0)
        {
            numGoalKeepers--;
            REQUIRE(StatusType::SUCCESS == worldCup.add_player(playerId, teamId, permutation_t::neutral(), 0, 0, 0, true));
        }
        else
        {
            REQUIRE(StatusType::SUCCESS == worldCup.add_player(playerId, teamId, permutation_t::neutral(), 0, 0, 0, false));
        }
        players.push_back(playerId);
    }
    return players;
}

inline int *get_array(std::array<int, 5> p, int p_regular[5])
{
    for (int i = 0; i < 5; i++)
    {
        p_regular[i] = p[i];
    }
    return p_regular;
}