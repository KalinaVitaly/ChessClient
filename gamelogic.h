#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include "storage.h"

#include <QObject>

class GameLogic : public QObject
{
    Q_OBJECT
public:
    explicit GameLogic(QObject* parent = nullptr);

public:
    QVector<QPair<int, int>> parsePlayerMotion(FigureColor figureColor, FigureType figureType,
                                               const QPair<int, int>& position);

    void setPlayerColor(PlayerChooseColor _playerColor);

private:
    QVector<QPair<int, int>> parsePawnMotion(const QPair<int, int>& position, bool isPlayerMove);
    QVector<QPair<int, int>> parseHorseMotion(const QPair<int, int>& position);
    QVector<QPair<int, int>> parseElephantMotion(const QPair<int, int>& position);
    QVector<QPair<int, int>> parseRookMotion(const QPair<int, int>& position);
    QVector<QPair<int, int>> parseKingMotion(const QPair<int, int>& position);
    QVector<QPair<int, int>> parseQueunMotion(const QPair<int, int>& position);

    QVector<QPair<int, int>> parseLineMotion(const QPair<int, int>& position,
                                             const QVector<QPair<int, int>>& possibleMotions);
    void initCurrentGameBoard();

private:
    PlayerChooseColor playerColor;
    int currentGame[cellHeightCount][cellWidthCount];
signals:
};

#endif // GAMELOGIC_H
