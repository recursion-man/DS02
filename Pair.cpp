#include "Pair.h"

int Pair::getTeamId() const
{
    return this->teamId;
}
int Pair::getTeamAbility() const
{
    return this->team_ability;
}
void Pair::setTeamId(int teamId)
{
    this->teamId = teamId;
}
void Pair::setTeamAbility(int team_ability)
{
    this->team_ability = team_ability;
}

bool operator<(Pair a, Pair b)
{
    if (a.getTeamAbility() < b.getTeamAbility())
    {
        return true;
    }
    else if (a.getTeamAbility() > b.getTeamAbility())
    {
        return false;
    }
    else
    {
        return a.getTeamId() < b.getTeamId();
    }
}

bool operator>(Pair a, Pair b)
{
    if (a.getTeamAbility() > b.getTeamAbility())
    {
        return true;
    }
    else if (a.getTeamAbility() < b.getTeamAbility())
    {
        return false;
    }
    else
    {
        return a.getTeamId() > b.getTeamId();
    }
}
