#include "tetrispainter.h"
#include <QMouseEvent>

TetrisPainter::TetrisPainter(QObject *parent) :
    Menu(parent) {
}


TetrisPainter::TetrisPainter(TetrisPanel *ow) {
    th = 20;
    tw = 10;
    //t = new Tetris(th, tw);
    t = NULL;
    owner = ow;
    started = false;
    paused = false;
    timer = new QTimer();
    timer->connect(timer, SIGNAL(timeout()), this, SLOT(update()));
}

TetrisPainter::~TetrisPainter() {
    delete t;
}

void TetrisPainter::paint(QPainter &p) {
    p.drawText(100, 100, "It's Tetis");
    int nx = paintLeft(0, p);
    nx += paintCenter(nx, p);
    paintRight(nx, p);
}

int TetrisPainter::paintLeft(int startx, QPainter &p) {
    paintPreview(startx, 41, p, t->hold);
    if (t->holdf)
        p.setBrush(Qt::red);
    else
        p.setBrush(Qt::green);
    p.setPen(Qt::black);
    p.drawEllipse(10, 90, 20, 20);
    //p.setFont(paintfont);
    p.drawText(startx + 10, 30, "Hold:");
    return 90;
}

int TetrisPainter::paintCenter(int startx, QPainter &p) {
    ColorTable table = t->table();
    p.setPen(QPen(QColor(127, 127, 127)));
    for (int i = 0; i < th; i++)
        for (int j = 0; j < tw; j++)
            if (table.code(i, j) == 1) {
                p.setBrush(QBrush(table.c(i, j)));
                p.drawRoundedRect(j * 20 + j + 1 + startx, i * 20 + i + 1,
                                  20, 20, 5.0, 5.0);
            } else if (table.code(i, j) == 2) {
                p.setBrush(QBrush(QColor(127, 127, 127)));
                p.drawRoundedRect(j * 20 + j + 1 + startx, i * 20 + i + 1,
                                  20, 20, 5.0, 5.0);
                QColor light = table.c(i, j);
                light.setAlpha(90);
                p.setBrush(QBrush(light));
                p.drawRoundedRect(j * 20 + j + 1 + startx, i * 20 + i + 1,
                                  20, 20, 5.0, 5.0);
            } else {
                p.setBrush(QBrush(QColor(127, 127, 127)));
                p.drawRoundedRect(j * 20 + j + 1 + startx, i * 20 + i + 1,
                                  20, 20, 5.0, 5.0);
            }
    return tw * 21;
}

int TetrisPainter::paintRight(int startx, QPainter &p) {
    paintPreview(startx, 41, p, t->next);
    p.setPen(QPen(Qt::black));
    //p.setFont(paintfont);
    p.drawText(startx + 10, 30, "Next:");
    p.drawText(startx + 10, 120, "Score: 0");
    p.drawText(startx + 10, 150, "Lines: 0");
    if (paused) {
        p.setBrush(QBrush(QColor(60, 60, 60, 200)));
        p.drawRect(0, 0, 800, 500);
        p.setPen(QPen(Qt::red));
        p.drawText(startx + 50, 90, "Paused");
    }
    if(t->gameover()) {
        timer->stop();
        paused = false;
        started = false;
        owner->setStarted(false);
        p.setPen(Qt::red);
        p.drawText(startx + 10, 180, "Game over");
    }
    return 0; //we not use this result
}

void TetrisPainter::paintPreview(int x, int y, QPainter& p, Block& pblck) {
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            if (!pblck.isEmpty() &&
                    i < pblck.block.height() &&
                    j < pblck.block.width() &&
                    pblck.block(i, j)) {
                p.setBrush(QBrush(pblck.color));
                p.drawRoundedRect(j * 10 + j + 10 + x, i * 10 + i + y,
                                  10, 10, 2.5, 2.5);
            } else {
                p.setBrush(QBrush(QColor(127, 127, 127)));
                p.drawRoundedRect(j * 10 + j + 10 + x, i * 10 + i + y,
                                  10, 10, 2.5, 2.5);
            }
}

void TetrisPainter::start() {
    if (t == NULL)
        t = new Tetris(th, tw);
    started = true;
    repaint();
    timer->start(1000);
}

void TetrisPainter::stopTetris() {
    delete t;
    t = NULL;
    if (started) {
        paused = false;
        started = false;
        timer->stop();
    }
}

void TetrisPainter::update() {
    if (!started)
        return;
    if (!paused)
        moveTetris();
    repaint();
}

bool TetrisPainter::moveTetris() {
    if(started)
        return t->move();
    return false;
}

void TetrisPainter::mouseMove(QMouseEvent *) {

}

void TetrisPainter::mousePress(QMouseEvent *) {

}

void TetrisPainter::key(QKeyEvent *ev) {
    if (started && !paused) {
        if (ev->key() == Qt::Key_Left)
            t->moveLeft();
        else if (ev->key() == Qt::Key_Right)
            t->moveRight();
        else if (ev->key() == Qt::Key_Return ||
                 ev->key() == Qt::Key_Space)
            while(moveTetris());
        else if (ev->key() == Qt::Key_Up)
            t->rotate();
        else if (ev->key() == Qt::Key_Control)
            t->nrotate();
        else if (ev->key() == Qt::Key_Down)
            t->move();
        else if (ev->key() == Qt::Key_Shift)
            t->swap();
    }

    if (ev->key() == Qt::Key_Pause) {
        if (!t->gameover()) {
            paused = !paused;
            repaint();
        }
    } else if (ev->key() == Qt::Key_Escape) {
        paused = true;
        owner->openMenu();
    }
    repaint();
}
