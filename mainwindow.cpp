#include "mainwindow.h"

#include "chessboard.h"
#include "gamemainwindow.h"
#include "ui_mainwindow.h"

#include <QFont>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose);
}

void MainWindow::resizeEvent(QResizeEvent* _event)
{
    ui->startGameButton->setMinimumHeight(_event->size().height() * 0.1);
    QFont font = ui->startGameButton->font();
    font.setPixelSize(ui->startGameButton->height() * 0.8);
    ui->startGameButton->setFont(font);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startGameButton_released()
{
    GameMainWindow* chessBoard = new GameMainWindow;
    chessBoard->show();
    close();
}
