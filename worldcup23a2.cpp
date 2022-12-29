#include "worldcup23a2.h"

world_cup_t::world_cup_t() : hash_table(), teams_by_id(), teams_by_rank(){}

world_cup_t::~world_cup_t()= default;

StatusType world_cup_t::add_team(int teamId)
{
    if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        std::shared_ptr<Team> new_team_id(new Team(teamId));
        std::shared_ptr<TeamRank> new_team_rank(new TeamRank(*new_team_id));
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
        std::shared_ptr<Team> target(new Team(teamId));
        std::shared_ptr<Team> team_id_to_remove = teams_by_id.findInTree(target);
        std::shared_ptr<TeamRank> team_rank_to_remove(new TeamRank(*team_id_to_remove));

        teams_by_id.removeFromTree(team_id_to_remove);
        teams_by_rank.removeFromTree(team_rank_to_remove);
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

        //find rank team
        std::shared_ptr<TeamRank> rank_target(new TeamRank(*team));
        std::shared_ptr<TeamRank> rank_team = teams_by_rank.findInTree(rank_target);

        // create the player
        Upside_Node* new_player_node = hash_table.insert(Player(playerId, gamesPlayed, cards, goalKeeper,
                                       ability, spirit, games_team_played_when_added, team_spirit_when_added));

        // match the player to the team
        team->addPlayer(new_player_node);

        // remove and insert the updated team-rank
        teams_by_rank.removeFromTree(rank_team);
        rank_team->addPlayer(new_player_node);
        teams_by_rank.insertToTree(rank_team);

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
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        return getPlayerTotalGames(hash_table[playerId]);
    }
    catch (std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (...)
    {
        return StatusType::FAILURE;
    }
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        if (isTeamActive(hash_table[playerId]))
        {
            hash_table[playerId]->data->addCard(cards);
            return StatusType::SUCCESS;
        }
        else
        {
            return StatusType::FAILURE;
        }
    }
    catch (std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (...)
    {
        return StatusType::FAILURE;
    }
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if (playerId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        return hash_table[playerId]->data->getCards();
    }
    catch (std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (...)
    {
        return StatusType::FAILURE;
    }
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
    if (teamId <= 0)
    {
        return StatusType::INVALID_INPUT;
    }
    try
    {
        std::shared_ptr<Team> target(new Team(teamId));
        std::shared_ptr<Team> team = teams_by_id.findInTree(target);
        return team->getPoints();
    }
    catch (std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (...)
    {
        return StatusType::FAILURE;
    }
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{

    try
    {
        return teams_by_rank.select(i+1)->getTeamId();
    }
    catch (std::bad_alloc &e)
    {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (...)
    {
        return StatusType::FAILURE;
    }
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
