#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QFrame>
#include <QLayout>
#include <QSpacerItem>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    
    QPushButton *prev = new QPushButton("Prev", this);
    QPushButton *next = new QPushButton("Next", this);
    QPushButton *newGame = new QPushButton("NewGame", this);
    
    QVBoxLayout *vt = new QVBoxLayout(this);
    vt->addStretch();
    QHBoxLayout *ht = new QHBoxLayout(this);
    vt->addLayout(ht);
    ht->addWidget(prev);
    ht->addWidget(newGame);
    ht->addWidget(next);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawLine(0, 0, 20, 20);
}
