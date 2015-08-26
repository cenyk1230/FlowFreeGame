#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class QFrame;

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
private:
    Ui::Widget *ui;
    int m_size;
    
};

#endif // WIDGET_H
