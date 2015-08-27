#ifndef GAMEGENFROMFILE_H
#define GAMEGENFROMFILE_H

#include "gamegen.h"
#include <QObject>
#include <QPoint>
#include <vector>

class GameGenFromFile : public GameGen
{
    Q_OBJECT
public:
    explicit GameGenFromFile(QObject *parent = 0);
    ~GameGenFromFile() {}
    
    //virtual void newGame(int, int *&, int *&, int **&, int, int &, int);
    //virtual void newGame();
    
public slots:
    virtual void newGame(int, int *&, int *&, int **&, int, int &, int);
    //void nextGame();
    //void prevGame();
    
private:
    int m_size;
    int m_num;
    int m_pairNum;
};

#endif // GAMEGENFROMFILE_H
