#include "gamegenfromfile.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPoint>
#include <QString>

GameGenFromFile::GameGenFromFile(QObject *parent) : GameGen(parent), m_num(0), m_size(0), m_pairNum(0)
{
    
}

void GameGenFromFile::newGame(int size, int *&x, int *&y, int **&arr, int lastSize, int &pairNum, int num) {
    qDebug() << "Begin GameGenFromFile::newGame";
    m_size = size;
    QString fileName = QString::number(m_size) + "_" + QString::number(num) + ".txt";
    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly)) {
        qDebug() << "Can't read file";
    }
    QTextStream in(&f);
    
    in >> pairNum;
    m_pairNum = pairNum;
    
    if (x != NULL)
        delete []x;
    x = new int[pairNum * 2];
    if (y != NULL)
        delete []y;
    y = new int[pairNum * 2];
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
    for (int i = 0; i < pairNum * 2; ++i) {
        in >> x[i] >> y[i];
        arr[x[i]][y[i]] = i / 2;
    }
    f.close();
    qDebug() << "End GameGenFromFile::newGame";
}
