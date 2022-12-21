#ifndef TEAM
#define TEAM

#include "AVLTree.h"
#include "Player.h"
#include "wet2util.h"
#include "UpsideNode.h"

#define MIN_PLAYERS_IN_TEAM 11

class Team
{
    int teamId, points, num_of_players, num_of_goal_keepers, games_played, sum_of_player_abilities;
    permutation_t team_spirit;
    Upside_Node<std::shared_ptr<Player>> *root_player_node;

public:
    //  C'tor
    explicit Team(int teamId, int points = 0) : teamId{teamId}, points{points}, num_of_players{0},
                                                num_of_goal_keepers{0}, games_played{0}, sum_of_player_abilities{0}, team_spirit{}, root_player_node{
                                                                                                                                        nullptr} {};
    ~Team(){};
    //  getters
    int getNumOfPlayers() const;
    int getPoints() const;
    int getNumOfGoalKeepers() const;
    permutation_t getTeamSpirit() const;
    int getTeamId() const;
    Upside_Node<std::shared_ptr<Player>> *getRootPlayerNode();
    int getGamesTeamPlayed() const;
    int getTeamStrength() const;
    int getTeamAbility() const;

    //  setters
    void setTeamId(int teamId);
    void setNumOfPlayers(int new_num_of_players);
    void setNumOfGoalKeepers(int new_goalkeepers);
    void setPoints(int new_points);

    bool isEmpty() const;
    bool isValidTeam() const;

    void handlePlayerAdded(std::shared_ptr<Player> player);
    void handleTeamBought(Team *source_team);
    void handleTeamRemoved();

    void applyMatch(int point_to_add);
};

// operations
bool operator<(const std::shared_ptr<Team> a, const std::shared_ptr<Team> b);
bool operator>(const std::shared_ptr<Team> a, const std::shared_ptr<Team> b);

#endif