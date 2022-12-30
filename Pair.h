struct Pair
{
    int teamId;
    int team_ability;
    Pair(int teamId, int team_ability) : teamId(teamId), team_ability(team_ability){};
    int getTeamId() const;
    int getTeamAbility() const;
    void setTeamId(int teamId);
    void setTeamAbility(int team_ability);
};
bool operator<(Pair a, Pair b);
bool operator>(Pair a, Pair b);