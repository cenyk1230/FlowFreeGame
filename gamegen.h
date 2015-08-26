#ifndef GAMEGEN_H
#define GAMEGEN_H


class GameGen
{
public:
    GameGen();
    
    virtual void newGame(int) = 0;
};

#endif // GAMEGEN_H
