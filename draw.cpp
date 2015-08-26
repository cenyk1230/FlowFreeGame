#include "draw.h"

Draw::Draw(QWidget *parent) : QWidget(parent) {
    
}

Draw::~Draw() {
    
}

void Draw::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPen pen;
    pen.setColor(Qt::yellow);
    painter.setPen(pen);
    painter.drawLine(rect().topLeft, rect().bottomRight());
}
