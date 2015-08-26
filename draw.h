#ifndef DRAW_H
#define DRAW_H

#include <QWidget>

class Draw : public QWidget
{
    Q_OBJECT
public:
    explicit Draw(QWidget *parent = 0);
    ~Draw();
    void paintEvent(QPaintEvent *);
signals:
    
public slots:
};

#endif // DRAW_H
