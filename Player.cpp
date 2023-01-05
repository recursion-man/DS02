#include "Player.h"
//  getters

int Player::getGamesPlayed() const
{
    return this->gamesPlayed;
}

int Player::getCards() const
{
    return cards;
}

Team *Player::getTeam() const
{
    return team;
}

int Player::getId() const
{
    return playerId;
}

int Player::getGamesTeamPlayedWhenAdded() const
{
    return games_team_played_when_added;
}

int Player::getAbility() const
{
    return ability;
}
permutation_t Player::getPlayerSpirit() const
{
    return player_spirit;
}

permutation_t Player::getTeamSpiritWhenAdded() const
{
    return this->team_spirit_when_added;
}
//  setters

void Player::setGamesPlayed(int games_played)
{
    this->gamesPlayed = games_played;
}

void Player::setGamesTeamPlayed(int new_games_team_played)
{
    this->games_team_played_when_added = new_games_team_played;
}

void Player::setTeam(Team *team)
{
    this->team = team;
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

bool operator<(const std::shared_ptr<Player> a, const std::shared_ptr<Player> b)
{
    return a->operator<(*b);
}
bool operator>(const std::shared_ptr<Player> a, const std::shared_ptr<Player> b)
{
    return a->operator>(*b);
}

//<---------------->

bool Player::isGoalKeeper() const
{
    return goalKeeper;
}

void Player::addCard(int card_to_add)
{
    this->cards += card_to_add;
}