#ifndef MATRIX_H
#define MATRIX_H

#include <QVector>
#include <cstdarg>

template<class T>
class Matrix {
    QVector< QVector<T> > data;
    int h, w;

public:
    Matrix() {h = 0; w = 0;}

    Matrix(int lh, int lw) {
        w = lw;
        h = lh;
        data.fill(QVector<T>(w), h);
    }

    Matrix(bool init, int lh, int lw, ...) {
        w = lw;
        h = lh;
        data.fill(QVector<T>(w), h);
        if (init) {
            va_list vl;
            va_start(vl, lw);
            for (int i = 0; i < h; i++)
                for (int j = 0; j < w; j++)
                    data[i][j] = va_arg(vl, T);
            va_end(vl);
        }
    }

    void fill(T val) {
        foreach (QVector<T> line, data) {
            line.fill(val);
        }
    }

    T& operator () (int i, int j) {
            return data[i][j];
    }

    int height() {
        return h;
    }

    int width() {
        return w;
    }
};


#endif // MATRIX_H
