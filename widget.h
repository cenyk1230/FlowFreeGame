#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "gamegen.h"
#include "solver.h"
#include <QPoint>
#include <vector>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
    void paintEvent(QPaintEvent *);
    void setGameGen(GameGen *gen);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    
public slots:
    void newGame(int);
    void reGame();
    void prevGame();
    void nextGame();
    void chooseLevel(QString);
    void solve();

signals:
    void newGame(int, int *&, int *&, int **&, int, int &, int);
    void win();

private:
    int getX(int);
    int getY(int);
    bool getXY(int &, int &);
    bool isInitalPoint(int, int);
    bool isInitalPoint(QPoint);
    bool isPathSource(int, int);
    bool isConnected(int);
    void updateText();
    
    Ui::Widget *ui;
    GameGen *m_gen;
    Solver *m_solver;
    int *m_x, *m_y;
    int **m_arr;
    int m_size, m_sizePrev, m_pairNum;
    int m_num;
    int m_ltx, m_lty;
    bool isMousePress;
    bool isGameBegin;
    int isDrawing;
    int m_move;
    int m_connectedNum;
    int m_mx, m_my;
    QPushButton *prev, *next, *reStart, *choose, *solution;
    QLabel *flowLabel, *moveLabel, *pipeLabel;
    QLineEdit *flowEdit, *moveEdit, *pipeEdit;
    QDialog *chooseDialog, *conDialog;
    QLabel *label5, *label6, *label7, *conLabel;
    QPushButton *level5[3], *level6[3], *level7[3], *conButton;
    std::vector<QPoint> *m_path;
};

#endif // WIDGET_H
