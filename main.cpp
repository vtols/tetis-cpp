#include <QApplication>
#include "tetrispanel.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    TetrisPanel tpan(app);
    tpan.show();
    return app.exec();
}
