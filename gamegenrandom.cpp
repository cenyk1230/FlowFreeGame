#include "gamegenrandom.h"

GameGenRandom::GameGenRandom(QObject *parent) : GameGen(parent)
{
    
}

void GameGenRandom::newGame(int size, int *&x, int *&y, int **&arr, int lastSize, int &pairNum, int num) {
    pairNum = size - rand() % 3;
    bool **v;
    v = new bool*[size];
    for (int i = 0; i < size; ++i) {
        v[i] = new bool[size];
        for (int j = 0; j < size; ++j)
            v[i][j] = false;
    }
    
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
    
    int nx, ny;
    for (int i = 0; i < pairNum * 2; ++i) {
        do {
            nx = rand() % size;
            ny = rand() % size;
        }while (v[nx][ny]);
        v[nx][ny] = true;
        x[i] = nx;
        y[i] = ny;
        arr[nx][ny] = i / 2;
    }
    
    for (int i = 0; i < size; ++i)
        delete []v[i];
    delete []v;
}
