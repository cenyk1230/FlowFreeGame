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
    
    // test read
    /*f("test.txt");
    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "Can't read file";
    }
    int aa, bb;
    QTextStream in(&f);
    in >> aa >> bb;
    qDebug() << aa << " " << bb;*/
    
    return a.exec();
}
