#include "block.h"
#include <QList>

/*Block::Block(QObject *parent) :
    QObject(parent) {
    spinc = 0;
    block = Matrix<int>();
}*/

/*Block::Block(Matrix<int> mx) {
    spinc = 0;
    color = QColor::fromRgb(0, 0, 0);
    block = mx;
}*/



/*
Block::Block(int bh, int bw, ...) {
    color = QColor::fromRgb(0, 0, 0);
    va_list vl;
    va_start(vl, bw);
    h = bh;
    w = bw;
    block = new bool*[h];
    for (int i = 0; i < h; i++)
        block[i] = new bool[w];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            block[i][j] = va_arg(vl, int);
}
*/

/*
Block::Block(QColor col, int bh, int bw, ...) {
    color = col;
    va_list vl;
    va_start(vl, bw);
    h = bh;
    w = bw;
    block = new bool*[h];
    for (int i = 0; i < h; i++)
        block[i] = new bool[w];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            block[i][j] = va_arg(vl, int);
}*/

/*void Block::spin() {
    spinc = (spinc + 1) % 4;
}*/

Block Block::f1 = Block(Matrix<int>(true, 2, 2, 1, 1, 1, 1));
Block Block::f2 = Block(Matrix<int>(true, 2, 3, 1, 1, 0, 0, 1, 1));
Block Block::f3 = Block(Matrix<int>(true, 2, 3, 0, 1, 1, 1, 1, 0));
Block Block::f4 = Block(Matrix<int>(true, 2, 3, 1, 1, 0, 0, 1, 1));
Block Block::f5 = Block(Matrix<int>(true, 2, 3, 1, 1, 1, 1, 0, 0));
Block Block::f6 = Block(Matrix<int>(true, 2, 3, 1, 1, 1, 0, 1, 0));
Block Block::f7 = Block(Matrix<int>(true, 1, 4, 1, 1, 1, 1));
Block Block::empty = Block();













