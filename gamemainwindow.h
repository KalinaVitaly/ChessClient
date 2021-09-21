#ifndef GAMEMAINWINDOW_H
#define GAMEMAINWINDOW_H

#include <QWidget>

namespace Ui {
class GameMainWindow;
}

class GameMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit GameMainWindow(QWidget *parent = nullptr);
    ~GameMainWindow();

private:
    Ui::GameMainWindow *ui;
};

#endif // GAMEMAINWINDOW_H
