#include "solver.h"
#include <QPoint>
#include <vector>
#include <QDebug>

using namespace std;

Solver::Solver()
{
    
}

int *X, *Y, **a;
vector<QPoint> *path;
int size, pairNum;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};

bool check() {
    int sum = 0;
    for (int i = 0; i < pairNum; ++i)
        sum += path[i].size();
    return sum == size * size;
}
int g[200][2];
bool v[10][10];
bool bfs(int sx, int sy, int tx, int ty) {
    int l = 1, r = 1, x, y, nx, ny;
    g[1][0] = sx;
    g[1][1] = sy;
    memset(v, false, sizeof v);
    v[sx][sy] = true;
    while (l <= r) {
        x = g[l][0];
        y = g[l++][1];
        for (int i = 0; i < 4; ++i) {
            nx = x + dx[i];
            ny = y + dy[i];
            if (nx < 0 || ny < 0 || nx >= size || ny >= size || a[nx][ny] != 10000)
                continue;
            if (nx == tx && ny == ty)
                return true;
            if (!v[nx][ny]) {
                g[++r][0] = nx;
                g[r][1] = ny;
                v[nx][ny] = true;
            }
        }
    }
    return false;
}

bool isValid(int dep) {
    for (int i = dep + 1; i < pairNum; ++i)
        if (!bfs(X[i * 2], Y[i * 2], X[i * 2 + 1], Y[i * 2 + 1]))
            return false;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j) {
            if (a[i][j] != 10000)
                continue;
            bool target = false;
            for (int k = 0; k < pairNum; ++k)
                if (i == X[k * 2 + 1] && j == Y[k * 2 + 1]) {
                    target = true;
                    break;
                }
            if (target)
                continue;
            int num = 0;
            for (int k = 0; k < 4; ++k) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni < 0 || ni >= size || nj < 0 || nj >= size || (a[ni][nj] != 10000 && a[ni][nj] < dep))
                    continue;
                ++num;
            }
            if (num <= 1)
                return false;
        }
    return true;
}

bool dfs(int dep, int x, int y) {
    //qDebug() << dep << " " << x << " " << y;
    if (!isValid(dep)) {
        return false;
    }
    
    path[dep].push_back(QPoint(x, y));

    if (x == X[dep * 2 + 1] && y == Y[dep * 2 + 1]) {
        if (dep + 1 == pairNum) {
            if (check())
                return true;
        }else {
            if (dfs(dep + 1, X[dep * 2 + 2], Y[dep * 2 + 2]))
                return true;
        }
    }else {
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx >= 0 && ny >= 0 && nx < size && ny < size && a[nx][ny] == 10000) {
                a[nx][ny] = dep;
                if (dfs(dep, nx, ny))
                    return true;
                a[nx][ny] = 10000;
            }
        }
    }
    path[dep].pop_back();
    return false;
}

bool Solver::solve(int _size, int *x, int *y, int **arr, vector<QPoint> *_path, int _pairNum) {
    size = _size;
    pairNum = _pairNum;
    X = x;
    Y = y;
    a = arr;
    path = _path;
    for (int i = 0; i < size; ++i)
        for (int j = 0; j < size; ++j)
            a[i][j] = 10000;
    for (int i = 0; i < pairNum * 2; ++i) {
        if (i % 2 == 1)
            continue;
        a[x[i]][y[i]] = i / 2;
    }
    for (int i = 0; i < pairNum; ++i)
        path[i].clear();
    
    return dfs(0, x[0], y[0]);
}
