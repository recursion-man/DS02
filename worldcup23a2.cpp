#include "worldcup23a2.h"

world_cup_t::world_cup_t() : hash_table(), teams_by_id(), teams_by_rank(){}

world_cup_t::~world_cup_t(){}

StatusType world_cup_t::add_team(int teamId)
{
    if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        std::shared_ptr<Team> new_team_id(new Team(teamId));
        std::shared_ptr<TeamRank> new_team_rank(new TeamRank(teamId));
        teams_by_id.insertToTree(new_team_id);
        teams_by_rank.insertToTree(new_team_rank);
    }
    catch (std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (...)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        std::shared_ptr<Team> new_team_id(new Team(teamId));
        std::shared_ptr<TeamRank> new_team_rank(new TeamRank(teamId));


        teams_by_id.removeFromTree(new_team_id);
        teams_by_rank.removeFromTree(new_team_rank);
    }
    catch (std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (...)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if (teamId <= 0 || playerId <= 0 || gamesPlayed < 0 || cards < 0 || !spirit.isvalid())
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        // find the team
        std::shared_ptr<Team> target(new Team(teamId));
        std::shared_ptr<Team> team = teams_by_id.findInTree(target);
        permutation_t team_spirit_when_added = team->getTeamSpirit();
        int games_team_played_when_added = team->getGamesTeamPlayed();

        // create the player
        Upside_Node* new_player_node = hash_table.insert(Player(playerId, gamesPlayed, cards, goalKeeper,
                                       ability, spirit, games_team_played_when_added, team_spirit_when_added));

        // match the player to the team
        team->addPlayer(new_player_node);

    }
    catch (std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (...)
    {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
