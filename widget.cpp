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
#include <QPalette>
#include <vector>

using namespace std;

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("Flow Free Game");
    this->setFixedHeight(560);
    this->setFixedWidth(500);
    m_gen = NULL;
    m_size = m_sizePrev = 0;
    m_pairNum = 0;
    m_num = 0;
    m_move = 0;
    m_x = m_y = NULL;
    m_arr = NULL;
    m_path = NULL;
    isMousePress = false;
    isDrawing = -1;
    
    prev = new QPushButton("Prev", this);
    next = new QPushButton("Next", this);
    reStart = new QPushButton("ReStart", this);
    
    flowLabel = new QLabel("flows:");
    moveLabel = new QLabel("moves:");
    pipeLabel = new QLabel("pipe:");
    
    flowEdit = new QLineEdit();
    moveEdit = new QLineEdit();
    pipeEdit = new QLineEdit();
    flowEdit->setReadOnly(true);
    moveEdit->setReadOnly(true);
    pipeEdit->setReadOnly(true);
    
    QVBoxLayout *vt = new QVBoxLayout(this);
    QHBoxLayout *ht1 = new QHBoxLayout();
    vt->addLayout(ht1);
    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::white);
    flowLabel->setPalette(pe);
    moveLabel->setPalette(pe);
    pipeLabel->setPalette(pe);
    
    ht1->addWidget(flowLabel);
    ht1->addWidget(flowEdit);
    ht1->addSpacing(50);
    ht1->addWidget(moveLabel);
    ht1->addWidget(moveEdit);
    ht1->addSpacing(50);
    ht1->addWidget(pipeLabel);
    ht1->addWidget(pipeEdit);
            
    vt->addStretch();
    
    QHBoxLayout *ht2 = new QHBoxLayout();
    vt->addLayout(ht2);
    ht2->addWidget(prev);
    ht2->addWidget(reStart);
    ht2->addWidget(next);
    
    connect(reStart, SIGNAL(clicked(bool)), this, SLOT(reGame()));
    connect(prev, SIGNAL(clicked(bool)), this, SLOT(prevGame()));
    connect(next, SIGNAL(clicked(bool)), this, SLOT(nextGame()));
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
    qDebug() << "Begin Drawing" << endl;
    QPainter painter(this); 
    painter.setBrush(Qt::black);
    painter.drawRect(0, 0, width(), height());
    /*if (m_gen == NULL)
        return;
    m_gen->newGame(m_size, m_x, m_y, m_arr, m_sizePrev);
    if (m_path != NULL)
        delete []m_path;
    m_path = new std::vector<QPoint>[m_size];*/
    
    //for (int i = 0; i < m_pairNum * 2; ++i) {
    //    qDebug() << m_x[i] << " " << m_y[i];
    //}
    int w = width();
    int h = height();
    h -= 50;
    int s = 420;
    m_ltx = w / 2 - s / 2;
    m_lty = h / 2 - s / 2 + 20;
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
    for (int i = 0; i < m_pairNum; ++i) {
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
    for (int i = 0; i < m_pairNum; ++i) {
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
    updateText();
    qDebug() << "End Drawing" << endl;
}

void Widget::updateText() {
    int connectedNum = 0;
    for (int i = 0; i < m_pairNum; ++i)
        if (isConnected(i))
            ++connectedNum;
    flowEdit->setText(QString::number(connectedNum) + "/" + QString::number(m_pairNum));
    
    moveEdit->setText(QString::number(m_move));
    
    int pipeNum = 0;
    for (int i = 0; i < m_pairNum; ++i)
        pipeNum += max((int)m_path[i].size() - 1, 0);
    int per = (int)(pipeNum * 1.0 / (m_size * m_size - m_pairNum) * 100 + 0.5);
    pipeEdit->setText(QString::number(per) + "%");
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
    qDebug() << "Begin setGameGen";
    if (m_gen != NULL) {
        disconnect(this, SIGNAL(newGame(int, int *&, int *&, int **&, int, int &, int)), this->m_gen, SLOT(newGame(int, int *&, int *&, int **&, int, int &, int)));
        disconnect(this, SIGNAL(newGame(int, int *&, int *&, int **&, int, int &, int)), this->m_gen, SLOT(newGame(int, int *&, int *&, int **&, int, int &, int)));
        delete m_gen;
    }
    m_gen = gen;
    
    connect(this, SIGNAL(newGame(int, int *&, int *&, int **&, int, int &, int)), this->m_gen, SLOT(newGame(int, int *&, int *&, int **&, int, int &, int)));
    connect(this, SIGNAL(newGame(int, int *&, int *&, int **&, int, int &, int)), this->m_gen, SLOT(newGame(int, int *&, int *&, int **&, int, int &, int)));
    qDebug() << "End setGameGen";
}


void Widget::newGame(int size) {
    qDebug() << "Begin newGame";
    if (m_gen == NULL) {
        qDebug() << "can't new game";
        return;
    }
    m_sizePrev = m_size;
    m_size = size;
    m_gen->newGame(m_size, m_x, m_y, m_arr, m_sizePrev, m_pairNum, m_num);
    if (m_path != NULL)
        delete []m_path;
    m_path = new std::vector<QPoint>[m_pairNum];
    for (int i = 0; i < m_pairNum; ++i)
        m_path[i].clear();
    m_move = 0;
    this->repaint();
    qDebug() << "End newGame";
}

void Widget::reGame() {
    for (int i = 0; i < m_pairNum; ++i)
        m_path[i].clear();
    for (int i = 0; i < m_size; ++i)
        for (int j = 0; j < m_size; ++j)
            m_arr[i][j] = 10000;
    for (int i = 0; i < m_pairNum * 2; ++i)
        m_arr[m_x[i]][m_y[i]] = i / 2;
    m_move = 0;
    this->repaint();
}

void Widget::prevGame() {
    qDebug() << "Begin Widget::prevGame";
    m_num -= 1;
    if (m_num < 0)
        m_num += 3;
    emit newGame(m_size, m_x, m_y, m_arr, m_sizePrev, m_pairNum, m_num);
    if (m_path != NULL)
        delete []m_path;
    m_path = new std::vector<QPoint>[m_pairNum];
    for (int i = 0; i < m_pairNum; ++i)
        m_path[i].clear();
    this->repaint();
    qDebug() << "End Widget::prevGame";
}

void Widget::nextGame() {
    qDebug() << "Begin Widget::nextGame";
    m_num += 1;
    if (m_num >= 3)
        m_num -= 3;
    emit newGame(m_size, m_x, m_y, m_arr, m_sizePrev, m_pairNum, m_num);
    if (m_path != NULL)
        delete []m_path;
    m_path = new std::vector<QPoint>[m_pairNum];
    for (int i = 0; i < m_pairNum; ++i)
        m_path[i].clear();
    this->repaint();
    qDebug() << "End Widget::nextGame";
}

void Widget::mouseMoveEvent(QMouseEvent *event) {
    qDebug() << "Begin mouseMoveEvent";
    m_mx = event->x();
    m_my = event->y();
    qDebug() << m_mx << " " << m_my << " " << isDrawing << endl;
    if (isDrawing != -1 && !isConnected(isDrawing)) {
        if (m_path[isDrawing].size() == 0) {
            isMousePress = false;
            isDrawing = -1;
            this->update();
            qDebug() << "End mouseMoveEvent";
            return;
        }
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
                    isMousePress = false;
                    isDrawing = -1;
                }else {
                    int color = m_arr[i][j];
                    while (m_path[color].size() > 0) {
                        int t = (int)m_path[color].size() - 1;
                        if (m_path[color][t] != QPoint(i, j)) {
                            if (!isInitalPoint(m_path[color][t]))
                                m_arr[m_path[color][t].x()][m_path[color][t].y()] = 10000;
                            m_path[color].pop_back();
                        }else {
                            if (!isInitalPoint(m_path[color][t]))
                                m_arr[m_path[color][t].x()][m_path[color][t].y()] = 10000;
                            m_path[color].pop_back();
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
                    
                    mouseReleaseEvent(event);
                    
                }else {
                    while (m_path[isDrawing].size() > 0) {
                        int t = (int)m_path[isDrawing].size() - 1;
                        if (m_path[isDrawing][t] != QPoint(i, j)) {
                            if (!isInitalPoint(m_path[isDrawing][t]))
                                m_arr[m_path[isDrawing][t].x()][m_path[isDrawing][t].y()] = 10000;
                            m_path[isDrawing].pop_back();
                        }else
                            break;
                    }
                }
            }
        }else {
            isDrawing = -1;
        }
    }
    
    this->update();
    qDebug() << "End mouseMoveEvent";
}

void Widget::mousePressEvent(QMouseEvent *event) {
    qDebug() << "Begin mousePressEvent";
    m_mx = event->x();
    m_my = event->y();
    isMousePress = true;
    //qDebug() << m_mx << " " << m_my << endl;
    int i, j;
    
    if (getXY(i, j)) {
        int color = m_arr[i][j];
        if (isConnected(color) && isInitalPoint(i, j)) {
            while (m_path[color].size() > 0) {
                int t = (int)m_path[color].size() - 1;
                if (!isInitalPoint(m_path[color][t]))
                    m_arr[m_path[color][t].x()][m_path[color][t].y()] = 10000;
                m_path[color].pop_back();
            }
            m_path[color].push_back(QPoint(i, j));
        }else {
            while (m_path[color].size() > 0) {
                int t = (int)m_path[color].size() - 1;
                if (m_path[color][t] != QPoint(i, j)) {
                    if (!isInitalPoint(m_path[color][t]))
                        m_arr[m_path[color][t].x()][m_path[color][t].y()] = 10000;
                    m_path[color].pop_back();
                }else
                    break;
            }
            if (m_path[color].size() == 0) {
                m_path[color].push_back(QPoint(i, j));
            }
        }
    }
    this->update();
    qDebug() << "End mousePressEvent";
}

void Widget::mouseReleaseEvent(QMouseEvent *event) {
    m_mx = event->x();
    m_my = event->y();
    isMousePress = false;
    if (isDrawing != -1)
        ++m_move;
    isDrawing = -1;
    this->update();
}

bool Widget::isInitalPoint(int x, int y) {
    for (int i = 0; i < m_pairNum * 2; ++i)
        if (m_x[i] == x && m_y[i] == y)
            return true;
    return false;
}

bool Widget::isInitalPoint(QPoint p) {
    return isInitalPoint(p.x(), p.y());
}

bool Widget::isPathSource(int x, int y) {
    for (int i = 0; i < m_pairNum; ++i)
        if (m_path[i].size() > 0) {
            if (m_path[i][0].x() == x && m_path[i][0].y() == y)
                return true;
        }
    return false;
}

bool isInPath(const QPoint &p, const vector<QPoint> &VP) {
    for (int i = 0; i < VP.size(); ++i)
        if (p == VP[i])
            return true;
    return false;
}

bool Widget::isConnected(int color) {
    QPoint p1 = QPoint(m_x[color * 2], m_y[color * 2]);
    QPoint p2 = QPoint(m_x[color * 2 + 1], m_y[color * 2 + 1]);
    return isInPath(p1, m_path[color]) && isInPath(p2, m_path[color]);
}
