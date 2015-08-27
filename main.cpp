#include "widget.h"
#include <QApplication>
#include "gamegen.h"
#include "gamegenfromfile.h"
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.setGameGen(new GameGenFromFile);
    //w.newGame(5);
    w.show();
    
    return a.exec();
}
