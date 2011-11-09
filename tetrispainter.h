#ifndef TETRISPAINTER_H
#define TETRISPAINTER_H

#include "menu.h"
#include "tetris.h"
#include <QTimer>

class TetrisPainter : public Menu {
    Q_OBJECT

    Tetris *t;
    QTimer *timer;
    int th, tw;

public:
    explicit TetrisPainter(QObject *parent = 0);

    TetrisPainter(TetrisPanel *ow);

    ~TetrisPainter();

    bool started, paused;

    void paint(QPainter&);
    void mouseMove(QMouseEvent *);
    void mousePress(QMouseEvent *);
    void key(QKeyEvent *);

    void start();
    void stopTetris();
    bool moveTetris();

    int paintLeft(int startx, QPainter& p);
    int paintCenter(int startx, QPainter& p);
    int paintRight(int startx, QPainter& p);
    void paintPreview(int x, int y, QPainter& p, Block& pblock);

signals:

public slots:

    void update();

};

#endif // TETRISPAINTER_H
