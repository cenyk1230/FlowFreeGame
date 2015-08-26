#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QLayout>
#include <QSpacerItem>
#include <QString>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    m_gen = NULL;
    
    QPushButton *prev = new QPushButton("Prev", this);
    QPushButton *next = new QPushButton("Next", this);
    QPushButton *reStart = new QPushButton("ReStart", this);
    
    QVBoxLayout *vt = new QVBoxLayout(this);
    vt->addStretch();
    QHBoxLayout *ht = new QHBoxLayout();
    vt->addLayout(ht);
    ht->addWidget(prev);
    ht->addWidget(reStart);
    ht->addWidget(next);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter painter(this); 
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width(), height());
    
    /*painter.drawLine(80, 100, 650, 500); 
    painter.setPen(Qt::red); 
    painter.drawRect(10, 10, 100, 400); 
    painter.setPen(QPen(Qt::green, 5)); 
    painter.setBrush(Qt::blue); 
    painter.drawEllipse(50, 150, 400, 200);*/
}

void Widget::setGameGen(GameGen *gen) {
    if (m_gen != NULL)
        delete m_gen;
    m_gen = gen;
}

void Widget::newGame(int size) {
    m_gen->newGame(size);
}
