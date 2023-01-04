#include "Team_Rank.h"

int Team_Rank::getTeamId() const
{
    return this->teamId;
}
int Team_Rank::getTeamAbility() const
{
    return this->team_ability;
}
void Team_Rank::setTeamId(int teamId)
{
    this->teamId = teamId;
}
void Team_Rank::setTeamAbility(int team_ability)
{
    this->team_ability = team_ability;
}

bool operator<(Team_Rank a, Team_Rank b)
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

bool operator>(Team_Rank a, Team_Rank b)
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
