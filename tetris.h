#ifndef TETRIS_H
#define TETRIS_H

#include <QObject>
#include <QVector>
#include "colortable.h"
#include "block.h"
#include <QTime>

class Tetris : public QObject
{
    Q_OBJECT



    void initVars();
    void gen();
    Block getNext();
    bool canGen();
    void calcghost();

public:
    explicit Tetris(QObject *parent = 0);

    Tetris(int h, int w);

    ColorTable ct;
    Block cur, hold;
    //QVector<Block> nextq; //new feature in future
    Block next;
    bool end;
    bool drawcur,  // =false
            holdf; // =false
    int ptinc; // = 0
    int qsize;
    int h, w, x, y, ghx, ghy;

    QList<Block> blocks;
    QList<QColor> colors;

    bool checkmove();
    bool move();
    bool gameover();
    bool checkLine();
    void swap();
    void moveLeft();
    void moveRight();
    void rotate(bool clockwise);
    void rotate();
    void nrotate();
    ColorTable table();

signals:

public slots:

};

#endif // TETRIS_H
