#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "GameGen.h"

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
    
public slots:
    void newGame(int);

private:
    Ui::Widget *ui;
    GameGen *m_gen;
    
};

#endif // WIDGET_H
