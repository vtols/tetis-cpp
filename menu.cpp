#include "menu.h"

Menu::Menu(QObject *parent) :
    QObject(parent) {
}

Menu::Menu(TetrisPanel *ow) :
    owner(ow) {
}

void Menu::repaint() {
    owner->repaint();
}

void Menu::paint(QPainter&) {
}

void Menu::mouseMove(QMouseEvent *) {
}

void Menu::mousePress(QMouseEvent *) {
}

void Menu::key(QKeyEvent *) {
}
