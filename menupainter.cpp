#include "menupainter.h"

MenuPainter::MenuPainter(QObject *parent) :
    Menu(parent) {
}

MenuPainter::MenuPainter(TetrisPanel *ow) :
    Menu(ow) {
    mentries << "New game" << "Resume" << "Help" << "Exit";
    menabled << true << false << false << true;
    paintfont = QFont("Arial", 30);
    selected = enc = 0;
    for (int i = 0; i < mentries.length(); i++)
        if (menabled[i])
            enc++;
}

void MenuPainter::paint(QPainter& painter) {
    painter.setFont(paintfont);
    QFontMetrics fm(paintfont);
    int h = fm.height(), nh = enc * h;
    for (int i = 0, dc = 0; i < mentries.length(); i++) {
        if (!menabled[i])
            continue;
        painter.setPen(dc == selected ? Qt::red : Qt::black);
        int ws = fm.width(mentries[i]);
        int x = 800 / 2 - ws / 2,
            y = 500 / 2 - nh / 2 + h * dc;
        painter.drawText(x, y, mentries[i]);
        dc++;
    }
}

void MenuPainter::mouseMove(QMouseEvent *ev) {
    QFontMetrics fm(paintfont);
    int h = fm.height(), nh = enc * h;
    int dy = 500 / 2 - nh / 2 - h;
    int my = ev->y();
    if(my >= dy && my < dy + nh)
        selected = (my - dy) / h;
    repaint();
}

void MenuPainter::mousePress(QMouseEvent *) {
    openSelected();
}

void MenuPainter::key(QKeyEvent *ev) {
    if (ev->key() == Qt::Key_Up)
        selected = (selected + enc - 1) % enc;
    else if (ev->key() == Qt::Key_Down)
        selected = (selected + enc + 1) % enc;
    else if (ev->key() == Qt::Key_Return)
        openSelected();
    repaint();
}

void MenuPainter::openSelected() {
    int rc = -1, i;
    for (i = 0, rc = -1; rc < selected; i++)
        if (menabled[i])
            rc++;
    if (mentries[i - 1] == "New game") {
        setStated(true);
        owner->restartTetris();
    }
    else if (mentries[i - 1] == "Resume")
        owner->openTetris();
    else if (mentries[i - 1] == "Exit")
        exit(0);
    repaint();
}

void MenuPainter::setStated(bool state) {
    for (int i = 0; i < mentries.size(); i++)
        if (mentries[i] == "Resume") {
            enc += (int) state - menabled[i];
            menabled[i] = state;
            return;
        }
}
