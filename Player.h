#ifndef PLAYER
#define PLAYER


class Player
{
    int playerId;

public:
    //  C'tor and D'tor
    explicit Player(int playerId) : playerId(playerId){};

    int getId() const;
};


#endif