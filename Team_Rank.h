struct Team_Rank
{
    int teamId;
    int team_ability;
    Team_Rank(int teamId, int team_ability) : teamId(teamId), team_ability(team_ability){};
    int getTeamId() const;
    int getTeamAbility() const;
    void setTeamId(int teamId);
    void setTeamAbility(int team_ability);
};
bool operator<(Team_Rank a, Team_Rank b);
bool operator>(Team_Rank a, Team_Rank b);