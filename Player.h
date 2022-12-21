#ifndef PLAYER
#define PLAYER

#include "AVLTree.h"
#include "Team.h"

class Team;
class Player
{
protected:
    int playerId, teamId, gamesPlayed, goals, cards, games_team_played_when_added;
    bool goalKeeper;
    Team *team;

public:
    //  C'tor and D'tor
    explicit Player(int playerId) : playerId(playerId){};
    Player(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper, int games_team_played_when_added) : playerId(playerId), teamId(teamId), gamesPlayed(gamesPlayed), goals(goals), cards(cards), games_team_played_when_added(games_team_played_when_added), goalKeeper(goalKeeper) {}
    virtual ~Player() = default;

    //  getters
    Team *getTeam();
    int getGamesPlayed() const;
    int getCards() const;
    int getGoals() const;
    int getGamesTeamPlayedWhenAdded() const;
    virtual int getId() const;

    //  setters
    void setTeam(Team *team);
    void setGamesPlayed(int gamesPlayed);
    void setGamesTeamPlayed(int new_games_team_played);

    bool isGoalKeeper() const;

    void updateStats(int gamesPlayed_to_add, int goals_to_add, int cards_to_add);
    virtual bool operator<(const Player &other) const;
    virtual bool operator>(const Player &other) const;
};

class PlayerRank : public Player
{
private:
    PlayerRank *prev;
    PlayerRank *next;

public:
    // C'tor
    explicit PlayerRank(const Player &other) : Player(other) {}
    PlayerRank(int playerId, int teamId, int gamesPlayed, int goals, int cards, bool goalKeeper, int games_team_played_when_added) : Player(playerId, teamId, gamesPlayed, goals, cards, goalKeeper, games_team_played_when_added) {}
    virtual ~PlayerRank() override = default;

    // getters
    int getClosest() const;
    int getId() const override;
    int getClosesOutOfTwo(PlayerRank *a, PlayerRank *b) const;

    bool operator<(const PlayerRank &other) const;
    bool operator>(const PlayerRank &other) const;

    void addToRankList(AVL_Tree<std::shared_ptr<PlayerRank>> &players_rank);
    void updateTopScorer(const AVL_Tree<std::shared_ptr<PlayerRank>> &players_rank);
    void removeFromRankList();
};

bool operator<(const std::shared_ptr<Player> a, const std::shared_ptr<Player> b);
bool operator>(const std::shared_ptr<Player> a, const std::shared_ptr<Player> b);
bool operator<(const std::shared_ptr<PlayerRank> a, const std::shared_ptr<PlayerRank> b);
bool operator>(const std::shared_ptr<PlayerRank> a, const std::shared_ptr<PlayerRank> b);

#endif