#ifndef GAMEGENRANDOM_H
#define GAMEGENRANDOM_H

#include "gamegen.h"

class GameGenRandom : public GameGen
{
    Q_OBJECT
public:
    explicit GameGenRandom(QObject *parent = 0);
    ~GameGenRandom() {}
    
public slots:
    virtual void newGame(int, int *&, int *&, int **&, int, int &, int);
};

#endif // GAMEGENRANDOM_H
