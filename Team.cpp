#include "Team.h"

//  getters

bool Team::isEmpty() const
{
    return (this->num_of_players == 0);
}

permutation_t Team::getTeamSpirit() const
{
    return team_spirit;
}

int Team::getPoints() const
{
    return points;
}

int Team::getNumOfPlayers() const
{
    return num_of_players;
}

int Team::getNumOfGoalKeepers() const
{
    return num_of_goal_keepers;
}

int Team::getTeamId() const
{
    return this->teamId;
}

int Team::getGamesTeamPlayed() const
{
    return games_played;
}

// int getNewTotalGames(std::shared_ptr<Player> player, int games_team_played)
//{
//     return player->getGamesPlayed() + games_team_played - player->getGamesTeamPlayedWhenAdded();
// }

Upside_Node *Team::getRootPlayerNode()
{
    return root_player_node;
}

int Team::getTeamStrength() const
{
    return this->team_spirit.strength();
}

int Team::getTeamAbility() const
{
    return this->sum_of_player_abilities;
}

//  setters

void Team::setTeamId(int teamId)
{
    this->teamId = teamId;
}

void Team::setNumOfPlayers(int new_num_of_players)
{
    this->num_of_players = new_num_of_players;
}
void Team::setPoints(int new_points)
{
    this->points = new_points;
}
void Team::setNumOfGoalKeepers(int new_goalkeepers)
{
    this->num_of_goal_keepers = new_goalkeepers;
}

//<---------->

bool Team::isValidTeam() const
{
    return (num_of_players >= MIN_PLAYERS_IN_TEAM && num_of_goal_keepers > 0);
}

void Team::handlePlayerAdded(std::shared_ptr<Player> player)
{
    if (num_of_players == 0)
    {
        team_spirit = player->getPlayerSpirit();
    }
    else
    {
        team_spirit = team_spirit * player->getPlayerSpirit();
    }
    sum_of_player_abilities += player->getAbility();
    num_of_players++;
    if (player->isGoalKeeper())
    {
        num_of_goal_keepers++;
    }
}

void Team::handleTeamBought(Team *source_team)
{
    if (source_team == this)
    {
        return;
    }
    this->points += source_team->getPoints();
    this->num_of_goal_keepers += source_team->getNumOfGoalKeepers();
    this->num_of_players += source_team->getNumOfPlayers();
    this->sum_of_player_abilities += source_team->getTeamAbility();
    this->team_spirit = this->team_spirit * source_team->getTeamSpirit();
    if (source_team->getRootPlayerNode() != nullptr)
        union_tree(this->root_player_node, source_team->root_player_node);
}

void Team::handleTeamRemoved()
{
    root_player_node->data.setTeam(nullptr);
}

void Team::applyMatch(int points_to_add)
{
    points += points_to_add;
    games_played++;
}

bool operator<(const std::shared_ptr<Team> a, const std::shared_ptr<Team> b)
{
    return a->getTeamId() < b->getTeamId();
}

bool operator>(const std::shared_ptr<Team> a, const std::shared_ptr<Team> b)
{
    return a->getTeamId() > b->getTeamId();
}

bool operator<(std::shared_ptr<TeamRank> a,  std::shared_ptr<TeamRank> b)
{
    return a->getTeamAbility() < b->getTeamAbility();
}

bool operator>(std::shared_ptr<TeamRank> a,  std::shared_ptr<TeamRank> b)
{
    return a->getTeamAbility() > b->getTeamAbility();
}