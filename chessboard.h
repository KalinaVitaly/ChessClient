#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "cell.h"
#include "gamelogic.h"

#include <QGridLayout>
#include <QParallelAnimationGroup>
#include <QTimer>
#include <QWidget>

class ChessBoard : public QWidget
{
    Q_OBJECT
public:
    explicit ChessBoard(QWidget* parent = nullptr);

protected:
    void resizeEvent(QResizeEvent* _event) override;

private:
    void initCell();
    void initFigures();
    QPair<int, int> figurePosition(Cell* cell);
    void setFigureMotionPositions(Cell* _cell);

private slots:
    void animationTimerAlarm();
    void slotCurrentCellChanged();

private:
    QVector<Cell*> vectorCells;
    QGridLayout* gridLayout;
    QParallelAnimationGroup* parellelAnimationGroup;
    QTimer* animationTimer;
    bool isForwardAnimation;
    PlayerChooseColor playerColor;

    GameLogic* gameLogic;
};

#endif // CHESSBOARD_H
