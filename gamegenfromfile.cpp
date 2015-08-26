#include "gamegenfromfile.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPoint>

GameGenFromFile::GameGenFromFile()
{
    
}

void GameGenFromFile::newGame(int size, int *&x, int *&y, int **&arr, int lastSize) {
    //qDebug() << "Begin newGame";
    QFile f("5_1.txt");
    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "Can't read file";
    }
    QTextStream in(&f);
    if (x != NULL)
        delete []x;
    x = new int[size * 2];
    if (y != NULL)
        delete []y;
    y = new int[size * 2];
    if (arr != NULL) {
        for (int i = 0; i < lastSize; ++i)
            delete []arr[i];
        delete []arr;
    }
    arr = new int*[size];
    for (int i = 0; i < size; ++i) {
        arr[i] = new int[size];
        for (int j = 0; j < size; ++j)
            arr[i][j] = 10000;
    }
    for (int i = 0; i < size * 2; ++i) {
        in >> x[i] >> y[i];
        arr[x[i]][y[i]] = i / 2;
    }
    f.close();
    //qDebug() << "End newGame";
}

