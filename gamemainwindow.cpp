#include "gamemainwindow.h"
#include "ui_gamemainwindow.h"

GameMainWindow::GameMainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameMainWindow)
{
    ui->setupUi(this);
}

GameMainWindow::~GameMainWindow()
{
    delete ui;
}
