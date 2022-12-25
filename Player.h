#ifndef PLAYER
#define PLAYER

#include "AVLTree.h"
#include "Team.h"
#include "wet2util.h"

class Team;
class Player
{
protected:
    int playerId, teamId, gamesPlayed, cards, ability, games_team_played_when_added;
    bool goalKeeper;
    permutation_t player_spirit, team_spirit_when_added;
    Team *team;

public:
    //  C'tor and D'tor
    explicit Player(int playerId) : playerId(playerId){};
    Player(int playerId, int teamId, int gamesPlayed, int cards, bool goalKeeper, int ability, const permutation_t &spirit, int games_team_played_when_added, permutation_t team_spirit_when_added, Team *team) : playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed), cards(cards), ability(ability), games_team_played_when_added(games_team_played_when_added), goalKeeper(goalKeeper), player_spirit(spirit), team_spirit_when_added(team_spirit_when_added), team(team){};
    ~Player() = default;

    //  getters
    int getGamesPlayed() const;
    int getCards() const;
    Team *getTeam() const;
    int getGamesTeamPlayedWhenAdded() const;
    int getId() const;
    int getAbility() const;
    permutation_t getPlayerSpirit() const;
    permutation_t getPartialPlayerSpirit() const;

    //  setters
    void setGamesPlayed(int gamesPlayed);
    void setTeam(Team *team);
    void setGamesTeamPlayed(int new_games_team_played);

    void addCard(int card_to_add);
    bool isGoalKeeper() const;
    virtual bool operator<(const Player &other) const;
    virtual bool operator>(const Player &other) const;
};

bool operator<(const std::shared_ptr<Player> a, const std::shared_ptr<Player> b);
bool operator>(const std::shared_ptr<Player> a, const std::shared_ptr<Player> b);
#endif