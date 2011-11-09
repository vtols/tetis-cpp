#include <QApplication>
#include "tetrispanel.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TetrisPanel tpan;
    tpan.show();
    return app.exec();
}
