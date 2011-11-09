#ifndef MENU_H
#define MENU_H

#include <QObject>
#include "tetrispanel.h"

class TetrisPanel;

class Menu : public QObject {
    Q_OBJECT
protected:
    TetrisPanel *owner;

public:
    explicit Menu(QObject *parent = 0);

    Menu(TetrisPanel *ow);

    virtual void repaint();

    virtual void paint(QPainter&);

    virtual void mouseMove(QMouseEvent *);

    virtual void mousePress(QMouseEvent *);

    virtual void key(QKeyEvent *);

signals:

public slots:

};

#endif // MENU_H
