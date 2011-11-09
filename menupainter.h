#ifndef MENUPAINTER_H
#define MENUPAINTER_H


#include <QList>
#include <QFont>
#include <QString>
#include "menu.h"

class MenuPainter : public Menu {
    Q_OBJECT

    QList<QString> mentries;
    QList<bool> menabled;

    int enc, selected;

    QFont paintfont;

public:
    explicit MenuPainter(QObject *parent = 0);
    MenuPainter(TetrisPanel *ow);

    void paint(QPainter&);
    void mouseMove(QMouseEvent *);
    void mousePress(QMouseEvent *);
    void key(QKeyEvent *);

    void openSelected();
    void setStated(bool state);

signals:

public slots:

};

#endif // MENUPAINTER_H
