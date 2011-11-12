#include "tetris.h"

void Tetris::initVars() {
    qsize = 5;
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    end = holdf = false;
    hold = next = cur = Block::empty;
    h = w = 0;
    blocks << Block::f1 << Block::f2 << Block::f3
           << Block::f4 << Block::f5 << Block::f6
           << Block::f7;
    colors << QColor(Qt::red)  << QColor(Qt::green)
           << QColor(Qt::cyan) << QColor(Qt::yellow);
}

Tetris::Tetris(QObject *parent) :
    QObject(parent) {
    initVars();
}

Tetris::Tetris(int x, int y) {
    initVars();
    ct = ColorTable(x, y);
    h = x;
    w = y;
}

void Tetris::gen() {
    ptinc = 0;
    if(next.isEmpty())
        next = getNext();
    if(!canGen()) {
        cur = Block::empty;
        end = true;
        return;
    }
    x = 0;
    y = w / 2 - next.w / 2;
    cur = next;
    next = getNext();
    drawcur = true;
    holdf = false;
    calcghost();
}

bool Tetris::checkmove() {
    for (int i = 0; i < cur.sph; i++)
        for (int j = 0; j < cur.spw; j++) {
            if (cur.spinned(i, j) && ct.t(x + i, y + j) && drawcur)
                end = true;
            if (x + i + 1 == h ||
                (cur.spinned(i, j) && ct.t(x + i + 1, y + j)))
                return false;
        }
    return true;
}

bool Tetris::move() {
    if (end)
        return false;
    bool continuemv = true;
    if (cur.isEmpty())
        gen();
    if (checkmove()) x++;
    else if (!end) {
        continuemv = false;
        if (drawcur) {
            //ptc.figureStopped();
            for (int i = 0; i < cur.sph; i++)
                for (int j = 0; j < cur.spw; j++)
                    if (cur.spinned(i, j)) {
                        ct.t(x + i, y + j) = true;
                        ct.code(x + i, y + j) = 1;
                        ct.c(x + i, y + j) = cur.color;
                    }
        }
        if (!checkLine())
            gen();
    }
    calcghost();
    return continuemv;
}

void Tetris::moveLeft() {
    if (end)
        return;
    for (int i = 0; i < cur.sph; i++)
        for (int j = 0; j < cur.spw; j++) {
            if (y + j - 1 < 0 ||
                (cur.spinned(i, j) && ct.t(x + i, y + j - 1)))
                return;
        }
    y--;
    calcghost();
}

void Tetris::moveRight() {
    if (end)
        return;
    for (int i = 0; i < cur.sph; i++)
        for (int j = 0; j < cur.spw; j++) {
            if (y + j + 1 < 0 || y + j + 1 >= w ||
                (cur.spinned(i, j) && ct.t(x + i, y + j + 1)))
                return;
        }
    y++;
    calcghost();
}

void Tetris::rotate(bool clockwise) {
    if(end)
        return;
    Block rot = cur;
    if (clockwise)
        rot.spinClockwise();
    else
        rot.spinCounterclockwise();
    int ny = y;
    while(rot.spw + ny > w)
        ny--;
    if(rot.sph + x > h)
        return;
    for(int i = 0; i < rot.sph; i++)
        for(int j = 0; j < rot.spw; j++) {
            if (rot.spinned(i, j) && ct.t(x + i, ny + j))
                return;
        }
    y = ny;
    rot.color = cur.color;
    cur = rot;
    calcghost();
}

void Tetris::rotate() {
    rotate(true);
}

void Tetris::nrotate() {
    rotate(false);
}

Block Tetris::getNext() {
    Block tmp = blocks[qrand() % blocks.size()];
    tmp.color = colors[qrand() % colors.size()];
    return tmp;
}

bool Tetris::canGen() {
    int nx = 0;
    int ny = w / 2 - next.w / 2;
    for(int i = 0; i < next.h; i++)
        for(int j = 0; j < next.w; j++) {
            if(next.block(i, j) && ct.t(nx + i, ny + j)) {
                end = true;
                return false;
            }
        }
    return true;
}

bool Tetris::gameover() {
    if (end)
        return true;
    for (int i = 0; i < w; i++)
        if (ct.t(0, i)) {
            end = true;
            return true;
        }
    return false;
}

ColorTable Tetris::table() {
    ColorTable pt = ColorTable(h, w);
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++) {
            pt.t(i, j) = ct.t(i, j);
            pt.c(i, j) = ct.c(i, j);
            pt.code(i, j) = ct.code(i, j);
        }
    if (!end && !cur.isEmpty() && drawcur) {
        for (int i = 0; i < cur.sph; i++)
            for (int j = 0; j < cur.spw; j++)
                if (cur.spinned(i, j)) {
                    pt.t(x + i, y + j) = true;
                    pt.code(x + i, y + j) = 1;
                    pt.c(x + i, y + j) = cur.color;

                    if(ghx - x >= cur.h) {
                        pt.code(ghx + i, ghy + j) = 2;
                        pt.c(ghx + i, ghy + j) = cur.color;
                    }
                }
    }
    return pt;
}

void Tetris::swap() {
    if(!holdf) {
        if(hold.isEmpty()) {
            //hold = cur;
            hold = cur;
            gen();
        } else {
            qSwap(cur, hold);
            hold.spinc = 0;
            x = 0;
            y = w / 2 - cur.spw / 2;
            calcghost();
        }
        holdf = true;
    }
}

bool Tetris::checkLine()  {
    for(int k = h - 1; k > 0; k--) {
        bool ln = true;
        for(int j = 0; j < w; j++)
            ln &= ct.t(k, j);
        if (ln) {
            for (int i = k; i > 0; i--)
                for (int j = 0; j < w; j++) {
                    ct.t(i, j) = ct.t(i - 1, j);
                    ct.code(i, j) = ct.code(i - 1, j);
                    //ct.t[i][j] = ct.t[i - 1][j];
                    ct.c(i, j) = ct.c(i - 1, j);
                }
            //ptc.lineCleared(++ptinc);
            //points += (++ptinc) * 100;
            //lines++;
            drawcur = false;
            return true;
        }
    }
    return false;
}

void Tetris::calcghost() {
    if (end)
        return;
    int xinc = -1;
    for (int i = 0; i < cur.spw; i++) {
        int d = 0, inc = 0;
        for (int j = 0; j < cur.sph; j++)
            if (cur.spinned(j, i))
                d = j + x + 1;
        while (d < h && !ct.t(d, y + i)) {
            inc++;
            d++;
        }
        if (xinc == -1 || xinc > inc)
            xinc = inc;
    }
    ghx = x + xinc;
    ghy = y;
}


