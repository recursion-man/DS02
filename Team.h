#ifndef TEAM
#define TEAM

#include "AVLTree.h"
#include "Player.h"
#include "UpsideNode.h"

#define MIN_PLAYERS_IN_TEAM 11

class Team
{
    int teamId, points, team_spirit, num_of_players, num_of_goal_keepers, games_played;
    Upside_Node<std::shared_ptr<Player>> *root_player_node;

public:
    //  C'tor
    explicit Team(int teamId, int points = 0) : teamId{teamId}, points{points}, team_spirit{0}, num_of_players{0},
                                                num_of_goal_keepers{0}, games_played{0}, root_player_node{
                                                                                             nullptr} {};
    ~Team(){};
    //  getters
    int getNumOfPlayers() const;
    int getPoints() const;
    int getNumOfGoalKeepers() const;
    int getTeamSpirit() const;
    int getTeamId() const;
    Upside_Node<std::shared_ptr<Player>> *getRootPlayerNode();
    int getGamesTeamPlayed() const;

    //  setters
    void setTeamId(int teamId);
    void setNumOfPlayers(int new_num_of_players);
    void setNumOfGoalKeepers(int new_goalkeepers);
    void setPoints(int new_points);

    bool isEmpty() const;
    bool isValidTeam() const;

    void playerAdded(bool isGoalKeeper, int player_spirit);
    void handleTeamBought(Team *source_team);

    void applyWinInMatch();
    void applyDrawInMatch();
    void applyLostInMatch();
};

// operations
bool operator<(const std::shared_ptr<Team> a, const std::shared_ptr<Team> b);
bool operator>(const std::shared_ptr<Team> a, const std::shared_ptr<Team> b);

#endif