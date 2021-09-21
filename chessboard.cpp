#include "chessboard.h"

#include "storage.h"

#include <QDebug>
#include <QResizeEvent>

ChessBoard::ChessBoard(QWidget* parent)
    : QWidget(parent)
    , gridLayout(new QGridLayout(this))
    , parellelAnimationGroup(new QParallelAnimationGroup(this))
    , animationTimer(new QTimer(this))
    , isForwardAnimation(false)
    , gameLogic(new GameLogic(this))
{
    playerColor = PlayerChooseColor::WHITE;
    gameLogic->setPlayerColor(playerColor);

    setMinimumSize(QSize(minWidth, minHeight));
    setLayout(gridLayout);
    initCell();
    initFigures();

    connect(animationTimer, SIGNAL(timeout()), this, SLOT(animationTimerAlarm()));
}

void ChessBoard::initCell()
{
    CellType type;
    gridLayout->setSpacing(0);

    for (int i = 0; i < cellHeightCount; ++i) {
        for (int j = 0; j < cellWidthCount; ++j) {

            if ((i + j) % 2 == 0) {
                type = CellType::BLACK;
            } else {
                type = CellType::WHITE;
            }

            Cell* cell = new Cell(type, this);
            vectorCells.push_back(cell);
            gridLayout->addWidget(cell, i, j);

            connect(cell, &Cell::currentCellChanged, this, &ChessBoard::slotCurrentCellChanged);
        }
    }
}

void ChessBoard::initFigures()
{
    std::function<void(int(&a)[8][8])> initBoard = [&](int(&chessBoard)[8][8]) {
        for (int i = 0; i < cellHeightCount; ++i) {
            for (int j = 0; j < cellWidthCount; ++j) {
                switch (chessBoard[i][j]) {
                case 1:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::WHITE,
                                                                         FigureType::PAWN);
                    break;
                case -1:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::BLACK,
                                                                         FigureType::PAWN);
                    break;
                case 2:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::WHITE,
                                                                         FigureType::HORSE);
                    break;
                case -2:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::BLACK,
                                                                         FigureType::HORSE);
                    break;
                case 4:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::WHITE,
                                                                         FigureType::ROOK);
                    break;
                case -4:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::BLACK,
                                                                         FigureType::ROOK);
                    break;
                case 3:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::WHITE,
                                                                         FigureType::ELEPHANT);
                    break;
                case -3:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::BLACK,
                                                                         FigureType::ELEPHANT);
                    break;
                case 5:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::WHITE,
                                                                         FigureType::QUEUEN);
                    break;
                case -5:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::BLACK,
                                                                         FigureType::QUEUEN);
                    break;
                case 6:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::WHITE,
                                                                         FigureType::KING);
                    break;
                case -6:
                    vectorCells[i * cellWidthCount + j]->setFigureWidget(FigureColor::BLACK,
                                                                         FigureType::KING);
                    break;
                }
            }
        }
    };


    if (playerColor == PlayerChooseColor::WHITE) {
        initBoard(chessBoardStartFigureWhitePosition);
    } else {
        initBoard(chessBoardStartFigureBlackPosition);
    }
}

QPair<int, int> ChessBoard::figurePosition(Cell* cell)
{
    int index = vectorCells.indexOf(cell);
    return QPair<int, int>(index / cellHeightCount, index % cellWidthCount);
}

void ChessBoard::setFigureMotionPositions(Cell* _cell)
{
    QPair<FigureColor, FigureType> figureType = _cell->getFigureType();
    QVector<QPair<int, int>> position
        = gameLogic->parsePlayerMotion(figureType.first, figureType.second, figurePosition(_cell));

    int index = 0;
    for (QPair<int, int> i : position) {
        index = i.first * cellHeightCount + i.second;
        vectorCells.at(index)->setIsMotionCell(true);
        parellelAnimationGroup->addAnimation(vectorCells.at(index)->getPropertyAnimation());
    }

    parellelAnimationGroup->start();
    animationTimer->start(animationTime);
}

void ChessBoard::animationTimerAlarm()
{
    if (isForwardAnimation) {
        parellelAnimationGroup->setDirection(QAbstractAnimation::Forward);
        isForwardAnimation = false;
    } else {
        parellelAnimationGroup->setDirection(QAbstractAnimation::Backward);
        isForwardAnimation = true;
    }
    parellelAnimationGroup->start();
}

void ChessBoard::slotCurrentCellChanged()
{
    Cell* currentCell = qobject_cast<Cell*>(sender());
    parellelAnimationGroup->stop();

    for (int i = 0; i < vectorCells.size(); ++i) {
        if (vectorCells[i]->getIsCurrentCell()) {
            if (vectorCells[i] != currentCell) {
                qDebug() << "Index : " << i;
                vectorCells.at(i)->setIsCurrentCell(false);
                parellelAnimationGroup->removeAnimation(vectorCells.at(i)->getPropertyAnimation());
            }
        } else if (vectorCells[i]->getIsMotionCell()) {
            vectorCells[i]->setIsMotionCell(false);
            parellelAnimationGroup->removeAnimation(vectorCells.at(i)->getPropertyAnimation());
        }
    }

    parellelAnimationGroup->addAnimation(currentCell->getPropertyAnimation());
    setFigureMotionPositions(currentCell);
}

void ChessBoard::resizeEvent(QResizeEvent* _event)
{
    const int cellSize = qMax(_event->size().width(), _event->size().height()) / cellHeightCount;

    for (int i = 0; i < vectorCells.size(); ++i) {
        vectorCells[i]->resize(cellSize, cellSize);
    }
    update();
}
