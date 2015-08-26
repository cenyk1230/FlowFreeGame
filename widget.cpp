#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPen>
#include <QPushButton>
#include <QLayout>
#include <QSpacerItem>
#include <QString>
#include <QDebug>
#include <QMouseEvent>
#include <vector>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Flow Free Game");
    this->setFixedHeight(500);
    this->setFixedWidth(500);
    m_gen = NULL;
    m_size = m_sizePrev = 5;
    m_x = m_y = NULL;
    m_arr = NULL;
    m_path = NULL;
    isMousePress = false;
    isDrawing = -1;
    
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

const int ColorNum = 7;
const QColor cc[] = {QColor(255, 0, 0), QColor(0, 255, 0), QColor(0, 0, 255),
                     QColor(255, 255, 0), QColor(255, 0, 255), QColor(0, 255, 255),
                     QColor(255, 255, 255)};

int Widget::getX(int num) {
    return m_ltx + 420 / m_size * num + 210 / m_size;
}

int Widget::getY(int num) {
    return m_lty + 420 / m_size * num + 210 / m_size;
}

void Widget::paintEvent(QPaintEvent *) {
    QPainter painter(this); 
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width(), height());
    /*if (m_gen == NULL)
        return;
    m_gen->newGame(m_size, m_x, m_y, m_arr, m_sizePrev);
    if (m_path != NULL)
        delete []m_path;
    m_path = new std::vector<QPoint>[m_size];*/
    
    //for (int i = 0; i < m_size * 2; ++i) {
    //    qDebug() << m_x[i] << " " << m_y[i];
    //}
    int w = width();
    int h = height();
    h -= 50;
    int s = 420;
    m_ltx = w / 2 - s / 2;
    m_lty = h / 2 - s / 2;
    painter.setPen(Qt::yellow);
    //painter.drawRect(cX - s / 2, cY - s / 2, s, s);
    for (int i = 0; i <= m_size; ++i) {
        painter.drawLine(m_ltx, m_lty + s / m_size * i, m_ltx + s, m_lty + s / m_size * i);
        painter.drawLine(m_ltx + s / m_size * i, m_lty, m_ltx + s / m_size * i, m_lty + s);
    }
   /*for (int i = 0; i < m_size; ++i)
        for (int j = 0; j < m_size; ++j) {
            int x = getX(i), y = getY(j);
            painter.setPen(cc[(i + j) % 7]);
            painter.setBrush(cc[(i + j) % 7]);
            painter.drawEllipse(QPoint(x, y), 420 / m_size / 2 - 10, 420 / m_size / 2 - 10);
        }*/
    for (int i = 0; i < m_size; ++i) {
        for (int j = 0; j < 2; ++j) {
            int x = getX(m_x[i * 2 + j]), y = getY(m_y[i * 2 + j]);
            painter.setPen(cc[i % ColorNum]);
            painter.setBrush(cc[i % ColorNum]);
            int r = s / m_size / 2 - 15;
            painter.drawEllipse(QPoint(x, y), r, r);
        }
    }
    int hiddenColor = -1;
    if (isMousePress) {
        int i, j;
        if (getXY(i, j)) {
            QColor tempColor = cc[m_arr[i][j]];
            tempColor.setAlpha(75);
            painter.setPen(tempColor);
            painter.setBrush(tempColor);
            int r = s / m_size / 2 + 5;
            painter.drawEllipse(QPoint(m_mx, m_my), r, r);
            hiddenColor = m_arr[i][j];
            isDrawing = m_arr[i][j];
        }else {
            isDrawing = -1;
        }
    }else {
        isDrawing = -1;
    }
    for (int i = 0; i < m_size; ++i) {
        qDebug() << m_path[i].size();
        for (int j = 0; j < (int)m_path[i].size() - 1; ++j) {
            painter.setPen(cc[m_arr[m_path[i][j].x()][m_path[i][j].y()]]);
            painter.setBrush(cc[m_arr[m_path[i][j].x()][m_path[i][j].y()]]);
            int x1 = getX(m_path[i][j].x());
            int y1 = getY(m_path[i][j].y());
            int x2 = getX(m_path[i][j + 1].x());
            int y2 = getY(m_path[i][j + 1].y());
            painter.drawEllipse(QPoint(x2, y2), 12, 12);
            if (x1 == x2) {
                if (y1 > y2)
                    swap(y1, y2);
                painter.drawRect(x1 - 12, y1, 24, y2 - y1);
            }else {
                if (x1 > x2)
                    swap(x1, x2);
                painter.drawRect(x1, y1 - 12, x2 - x1, 24);
            }
        }
        if (i == hiddenColor)
            continue;
        for (int j = 0; j < m_path[i].size(); ++j) {
            QColor tempColor = cc[m_arr[m_path[i][j].x()][m_path[i][j].y()]];
            tempColor.setAlpha(110);
            painter.setPen(tempColor);
            painter.setBrush(tempColor);
            int x = getX(m_path[i][j].x());
            int y = getY(m_path[i][j].y());
            painter.drawRect(x - s / m_size / 2, y - s / m_size / 2, s / m_size, s / m_size);
        }
    }
    qDebug() << endl;
}

bool Widget::getXY(int &x, int &y) {
    x = y = -1;
    int s = 420;
    for (int i = 0; i < m_size; ++i)
        for (int j = 0; j < m_size; ++j) {
            int lx = m_ltx + s / m_size * i;
            int rx = lx + s / m_size;
            int ly = m_lty + s / m_size * j;
            int ry = ly + s / m_size;
            if (m_mx >= lx && m_mx < rx && m_my >= ly && m_my < ry) {
                //if (m_arr[i][j] >= ColorNum)
                //    continue;
                x = i;
                y = j;
                return m_arr[x][y] < ColorNum;
            }
        }
    return false;
}

void Widget::setGameGen(GameGen *gen) {
    if (m_gen != NULL)
        delete m_gen;
    m_gen = gen;
}

void Widget::newGame(int size) {
    if (m_gen == NULL) {
        qDebug() << "can't new game";
        return;
    }
    m_sizePrev = m_size;
    m_size = size;
    m_gen->newGame(m_size, m_x, m_y, m_arr, m_sizePrev);
    if (m_path != NULL)
        delete []m_path;
    m_path = new std::vector<QPoint>[m_size];
    for (int i = 0; i < m_size; ++i)
        m_path[i].clear();
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
    m_mx = event->x();
    m_my = event->y();
    qDebug() << m_mx << " " << m_my << endl;
    if (isDrawing != -1) {
        int lasti, lastj;
        int t = (int)m_path[isDrawing].size() - 1;
        lasti = m_path[isDrawing][t].x();
        lastj = m_path[isDrawing][t].y();
        int i, j;
        getXY(i, j);
        if (abs(i - lasti) + abs(j - lastj) == 0) {
            // nothing to do
        }else if (abs(i - lasti) + abs(j - lastj) == 1) {
            if (m_arr[i][j] >= ColorNum) {
                m_arr[i][j] = isDrawing;
                m_path[isDrawing].push_back(QPoint(i, j));
            }else if (m_arr[i][j] != isDrawing) {
                if (isInitalPoint(i, j)) {
                    isDrawing = -1;
                }else {
                    while (m_path[m_arr[i][j]].size() > 0) {
                        int t = (int)m_path[m_arr[i][j]].size() - 1;
                        if (m_path[m_arr[i][j]][t] != QPoint(i, j))
                            m_path[m_arr[i][j]].pop_back();
                        else {
                            m_path[m_arr[i][j]].pop_back();
                            break;
                        }
                    }
                    m_arr[i][j] = isDrawing;
                    m_path[isDrawing].push_back(QPoint(i, j));
                }
            }else {
                if (isInitalPoint(i, j) && !isPathSource(i, j)) {
                    m_arr[i][j] = isDrawing;
                    m_path[isDrawing].push_back(QPoint(i, j));
                }else {
                    while (m_path[isDrawing].size() > 0) {
                        int t = (int)m_path[isDrawing].size() - 1;
                        if (m_path[isDrawing][t] != QPoint(i, j))
                            m_path[m_arr[i][j]].pop_back();
                        else
                            break;
                    }
                }
            }
        }else {
            isDrawing = -1;
        }
    }
    this->update();
}

void Widget::mousePressEvent(QMouseEvent *event) {
    m_mx = event->x();
    m_my = event->y();
    isMousePress = true;
    //qDebug() << m_mx << " " << m_my << endl;
    int i, j;
    
    if (getXY(i, j)) {
        while (m_path[m_arr[i][j]].size() > 0) {
            int t = (int)m_path[m_arr[i][j]].size() - 1;
            if (m_path[m_arr[i][j]][t] != QPoint(i, j))
                m_path[m_arr[i][j]].pop_back();
            else
                break;
        }
        if (m_path[m_arr[i][j]].size() == 0) {
            m_path[m_arr[i][j]].push_back(QPoint(i, j));
        }
    }
    this->update();
}

void Widget::mouseReleaseEvent(QMouseEvent *event) {
    m_mx = event->x();
    m_my = event->y();
    isMousePress = false;
    isDrawing = -1;
    this->update();
}

bool Widget::isInitalPoint(int x, int y) {
    for (int i = 0; i < m_size * 2; ++i)
        if (m_x[i] == x && m_y[i] == y)
            return true;
    return false;
}

bool Widget::isPathSource(int x, int y) {
    for (int i = 0; i < m_size; ++i)
        if (m_path[i].size() > 0) {
            if (m_path[i][0].x() == x && m_path[i][0].y() == y)
                return true;
        }
    return false;
}
