#ifndef TEAM
#define TEAM

#include "AVLTree.h"
#include "UpsideNode.h"
#include "Player.h"
#include "wet2util.h"

#define MIN_PLAYERS_IN_TEAM 11
class Player;
class Upside_Node;

class Team
{
protected:
    int teamId, points, num_of_players, num_of_goal_keepers, games_played, sum_of_player_abilities;
    permutation_t team_spirit;
    Upside_Node *root_player_node;

public:
    //  C'tor
    explicit Team(int teamId) : teamId{teamId}, points{0}, num_of_players{0},
                                num_of_goal_keepers{0}, games_played{0}, sum_of_player_abilities{0},
                                team_spirit{permutation_t::neutral()}, root_player_node{nullptr} {};
    virtual ~Team();
    //  getters
    int getNumOfPlayers() const;
    int getPoints() const;
    int getNumOfGoalKeepers() const;
    permutation_t getTeamSpirit() const;
    int getTeamId() const;
    Upside_Node *getRootPlayerNode();
    int getGamesTeamPlayed() const;
    int getTeamStrength() const;
    int getTeamAbility() const;
    int getTeamScoreForMatch() const;

    //  setters
    void setTeamId(int teamId);
    void setNumOfPlayers(int new_num_of_players);
    void setNumOfGoalKeepers(int new_goalkeepers);
    void setPoints(int new_points);
    void setRoot(Upside_Node *);
    void setTeamAbility(int new_ability);

    bool isEmpty() const;
    bool isValidTeam() const;

    void addPlayer(Upside_Node *);

    void handlePlayerAdded(Player *player);
    void handleTeamBought(Team *source_team);
    void handleTeamRemoved();

    void applyMatch(int point_to_add);
};

// operations
bool operator<(std::shared_ptr<Team> a, std::shared_ptr<Team> b);
bool operator>(std::shared_ptr<Team> a, std::shared_ptr<Team> b);

#endif