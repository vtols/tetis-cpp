#ifndef COLORTABLE_H
#define COLORTABLE_H

#include <QObject>
#include <QColor>
#include "matrix.h"

class ColorTable //: public QObject
{
    //Q_OBJECT
public:
    //explicit ColorTable(QObject *parent = 0);

    ColorTable() {}

    ColorTable(int h, int w) {
        t = Matrix<int>(h, w);
        code = Matrix<int>(h, w);
        c = Matrix<QColor>(h, w);
        //c.fill(QColor(0, 0, 0));
    }

    Matrix<int> t;
    Matrix<int> code;
    Matrix<QColor> c;

//signals:

//public slots:

};

#endif // COLORTABLE_H
