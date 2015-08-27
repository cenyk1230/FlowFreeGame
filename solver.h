#ifndef SOLVER_H
#define SOLVER_H

#include <vector>
#include <QPoint>

class Solver
{
public:
    Solver();
    
    bool solve(int, int *, int *, int **, std::vector<QPoint>*, int);
};

#endif // SOLVER_H
