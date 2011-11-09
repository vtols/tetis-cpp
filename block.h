#ifndef BLOCK_H
#define BLOCK_H

#include <QObject>
#include <QColor>
#include <QList>
#include "matrix.h"

class Block //: public QObject
{
    //Q_OBJECT

    //bool **block;

public:

    Matrix<int> block, spinned;
    int h, w, sph, spw;
    QColor color;
    int spinc; // = 0 //spinning counter
    int spinx, spiny; //spinning center (in future)

    //explicit Block(QObject *parent = 0);

    Block() {
        h = w = sph = spw = 0;
        spinc = 0;
        spinned = block = Matrix<int>();
    }

    //Block(const Block&);

    Block(Matrix<int> mx) {
        spinc = 0;
        sph = h = mx.height();
        spw = w = mx.width();
        color = QColor::fromRgb(0, 0, 0);
        spinned = block = mx;
    }

    //Block(int h, int w, ...);

    //Block(QColor col, int h, int w, ...);

    static Block f1, f2, f3, f4, f5, f6, f7;
    static Block empty;

    bool isEmpty() {
        return (block.height() == 0 && block.width() == 0);
    }

    void spinClockwise() {
        int nsph = spw, nspw = sph;
        Matrix<int> t(nsph, nspw);
        int i, j;
        for(i = 0; i < sph; i++)
            for(j = 0; j < spw; j++)
                t(j, sph - i - 1) = spinned(i, j);
        spinned = t;
        sph = nsph;
        spw = nspw;
        spinc = (spinc + 1) % 4;
    }

    void spinCounterclockwise() {
        for (int i = 0; i < 3; i++)
            spinClockwise();
    }

    //bool** spinmatrix(); //TODO

//signals:

//public slots:

};



#endif // BLOCK_H
