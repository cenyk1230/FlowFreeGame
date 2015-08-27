#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "GameGen.h"
#include <QPoint>
#include <vector>

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

private:
    int getX(int);
    int getY(int);
    bool getXY(int &, int &);
    bool isInitalPoint(int, int);
    bool isInitalPoint(QPoint);
    bool isPathSource(int, int);
    bool isConnected(int);
    
    Ui::Widget *ui;
    GameGen *m_gen;
    int *m_x, *m_y;
    int **m_arr;
    int m_size, m_sizePrev, m_pairNum;
    int m_ltx, m_lty;
    bool isMousePress;
    int isDrawing;
    int m_mx, m_my;
    std::vector<QPoint> *m_path;
};

#endif // WIDGET_H
