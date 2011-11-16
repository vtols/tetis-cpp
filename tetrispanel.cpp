#include "tetrispanel.h"
#include "tetris.h"
#include "tetrispainter.h"
#include "menupainter.h"

TetrisPanel::TetrisPanel(QApplication& app, QWidget *parent) :
    QWidget(parent) {
    //Tetris tet;
    //tet.swap();
    app.installEventFilter(this);
    QApplication::setKeyboardInputInterval(0);
    main = new MenuPainter(this);
    mtetris = new TetrisPainter(this);
    current = main;
    setFixedSize(800, 500);
    this->setMouseTracking(true);
    current->repaint();
}

TetrisPanel::~TetrisPanel() {
    delete main;
    delete mtetris;
}

QSize TetrisPanel::sizeHint() const {
    return QSize(800, 500);
}

bool TetrisPanel::eventFilter(QObject *, QEvent *ev) {
    if (ev->type() == QEvent::ActivationChange &&
            current == mtetris &&
            !mtetris->paused)
        mtetris->paused = !mtetris->paused;
    return false;
}

void TetrisPanel::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    current->paint(painter);

}

void TetrisPanel::keyPressEvent(QKeyEvent *ev) {
    current->key(ev);
}

void TetrisPanel::mouseMoveEvent(QMouseEvent *ev) {
    current->mouseMove(ev);
}

void TetrisPanel::mousePressEvent(QMouseEvent *ev) {
    current->mousePress(ev);
}

void TetrisPanel::focusOutEvent(QFocusEvent *) {
    if (current == mtetris)
        mtetris->paused = true;
}


void TetrisPanel::openMenu() {
    current = main;
    repaint();
}

void TetrisPanel::openTetris() {
    current = mtetris;
    mtetris->paused = false;
    repaint();
}

void TetrisPanel::restartTetris() {
    current = mtetris;
    if (mtetris->started)
        mtetris->stopTetris();
    mtetris->start();
    mtetris->paused = false;
    repaint();
}

void TetrisPanel::setStarted(bool started) {
    main->setStarted(started);
}
