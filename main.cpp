#include "mainwindow.h"

#include <QApplication>

#include <cell.h>
#include <chessboard.h>
#include <positionmap.h>
#include <storage.h>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    MainWindow* w = new MainWindow;
    // ChessBoard w;

    PositionMap pm;
    pm.setPositionMap({ -4, -2, -3, -5, -6, -3, -2, -4, -1, -1, -1, -1, -1, -1, -1, -1,
                        0,  0,  4,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  2,  0,  0,
                        0,  -6, 0,  3,  0,  8,  -8, 8,  0,  0,  0,  0,  -1, 1,  -5, -1,
                        1,  1,  1,  1,  1,  1,  1,  1,  4,  2,  3,  6,  5,  3,  2,  4 });
    // pm.show();

    w->show();
    return a.exec();
}
