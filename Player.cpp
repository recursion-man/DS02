#include "Player.h"
#include <utility>

//  getters

Team *Player::getTeam()
{
    return team;
}

int Player::getGamesPlayed() const
{
    int games_played_total = this->team->getGamesTeamPlayed() -
                             this->games_team_played_when_added + this->gamesPlayed;
    return games_played_total;
}

int Player::getGoals() const
{
    return goals;
}
int Player::getCards() const
{
    return cards;
}
int Player::getId() const
{
    return playerId;
}

int PlayerRank::getClosesOutOfTwo(PlayerRank *a, PlayerRank *b) const
{
    int a_goals_dif = abs(goals - a->goals);
    int b_goals_dif = abs(goals - b->goals);
    if (a_goals_dif != b_goals_dif)
    {
        return a_goals_dif < b_goals_dif ? a->playerId : b->playerId;
    }
    int a_cards_dif = abs(cards - a->cards);
    int b_cards_dif = abs(cards - b->cards);
    if (a_cards_dif != b_cards_dif)
    {
        return a_cards_dif < b_cards_dif ? a->playerId : b->playerId;
    }
    int a_id_dif = abs(playerId - a->playerId);
    int b_id_dif = abs(playerId - b->playerId);
    if (a_id_dif != b_id_dif)
    {
        return a_id_dif < b_id_dif ? a->playerId : b->playerId;
    }
    return a->playerId > b->playerId ? a->playerId : b->playerId;
}

int PlayerRank::getClosest() const
{
    if (next == nullptr && prev == nullptr)
    {
        throw std::invalid_argument("single instance in the system");
    }
    else if (next == nullptr)
    {
        return prev->playerId;
    }
    else if (prev == nullptr)
    {
        return next->playerId;
    }
    else
    {
        return getClosesOutOfTwo(next, prev);
    }
}

int PlayerRank::getId() const
{
    return Player::getId();
}

int Player::getGamesTeamPlayedWhenAdded() const
{
    return games_team_played_when_added;
}

//  setters

void Player::setTeam(Team *new_team)
{
    team = new_team;
}

void Player::setGamesPlayed(int games_played)
{
    this->gamesPlayed = games_played;
}

void Player::setGamesTeamPlayed(int new_games_team_played)
{
    this->games_team_played_when_added = new_games_team_played;
}

// operators

bool Player::operator<(const Player &other) const
{
    return playerId < other.playerId;
}

bool Player::operator>(const Player &other) const
{
    return playerId > other.playerId;
    ;
}

bool PlayerRank::operator<(const PlayerRank &other) const
{
    if (goals == other.goals)
    {
        if (cards == other.cards)
        {
            return Player::operator<(other);
        }
        return cards > other.cards;
    }
    return goals < other.goals;
}

bool PlayerRank::operator>(const PlayerRank &other) const
{
    if (goals == other.goals)
    {
        if (cards == other.cards)
        {
            return Player::operator>(other);
        }
        return cards < other.cards;
    }
    return goals > other.goals;
}

bool operator<(const std::shared_ptr<Player> a, const std::shared_ptr<Player> b)
{
    return a->operator<(*b);
}
bool operator>(const std::shared_ptr<Player> a, const std::shared_ptr<Player> b)
{
    return a->operator>(*b);
}

bool operator<(const std::shared_ptr<PlayerRank> a, const std::shared_ptr<PlayerRank> b)
{
    return a->operator<(*b);
}
bool operator>(const std::shared_ptr<PlayerRank> a, const std::shared_ptr<PlayerRank> b)
{
    return a->operator>(*b);
}
//<---------------->

bool Player::isGoalKeeper() const
{
    return goalKeeper;
}
void Player::updateStats(int gamesPlayed_to_add, int goals_to_add, int cards_to_add)
{
    gamesPlayed += gamesPlayed_to_add;
    goals += goals_to_add;
    cards += cards_to_add;
}

void PlayerRank::removeFromRankList()
{
    if (next != nullptr && prev != nullptr)
    {
        next->prev = prev;
        prev->next = next;
    }
    else if (prev == nullptr && next == nullptr)
    {
        return;
    }

    else if (prev == nullptr)
    {
        next->prev = nullptr;
    }
    else
    {
        prev->next = nullptr;
    }
}

void PlayerRank::addToRankList(AVL_Tree<std::shared_ptr<PlayerRank>> &players_rank)
{
    std::shared_ptr<PlayerRank> temp (new PlayerRank(*this));
    next = players_rank.getNext(temp).get();
    prev = players_rank.getPrev(temp).get();
    if (next->playerId == playerId)
        next = nullptr;
    if (prev->playerId == playerId)
        prev = nullptr;

    if (next != nullptr)
    {
        next->prev = this;
    }
    if (prev != nullptr)
    {
        prev->next = this;
    }
}
