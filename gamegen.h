#ifndef GAMEGEN_H
#define GAMEGEN_H

#include <QObject>

class GameGen : public QObject
{
    Q_OBJECT
public:
    explicit GameGen(QObject *parent = 0);
    ~GameGen() {}
    
public slots:
    virtual void newGame(int, int *&, int *&, int **&, int, int &, int);
signals:
    
};

#endif // GAMEGEN_H
