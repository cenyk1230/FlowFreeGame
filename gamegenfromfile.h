#ifndef GAMEGENFROMFILE_H
#define GAMEGENFROMFILE_H

#include "gamegen.h"

class GameGenFromFile : public GameGen
{
public:
    GameGenFromFile();
    
    virtual void newGame(int);
};

#endif // GAMEGENFROMFILE_H
