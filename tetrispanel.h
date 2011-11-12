#ifndef TETRISPANEL_H
#define TETRISPANEL_H

#include <QApplication>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>

#include "menu.h"
//#include "menupainter.h"
//#include "tetrispainter.h"

class Menu;
class MenuPainter;
class TetrisPainter;

class TetrisPanel : public QWidget
{
    Q_OBJECT
public:
    explicit TetrisPanel(QWidget *parent = 0);

    ~TetrisPanel();

    QSize sizeHint() const;

    Menu *current;
    MenuPainter *main;
    TetrisPainter *mtetris;

signals:

public slots:
    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void focusOutEvent(QFocusEvent *);

    void openMenu();
    void openTetris();
    void restartTetris();
    void setStarted(bool);

};

#endif // TETRISPANEL_H
