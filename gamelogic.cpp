#include "gamelogic.h"

#include <QDebug>

GameLogic::GameLogic(QObject* parent)
    : QObject(parent)
{
    setPlayerColor(PlayerChooseColor::WHITE);
    initCurrentGameBoard();
}

QVector<QPair<int, int>> GameLogic::parsePlayerMotion(FigureColor figureColor,
                                                      FigureType figureType,
                                                      const QPair<int, int>& position)
{
    QVector<QPair<int, int>> positions;

    if (figureType == FigureType::PAWN) {
        positions = parsePawnMotion(position, false);
    } else if (figureType == FigureType::HORSE) {
        positions = parseHorseMotion(position);
    } else if (figureType == FigureType::ROOK) {
        positions = parseRookMotion(position);
    } else if (figureType == FigureType::ELEPHANT) {
        positions = parseElephantMotion(position);
    } else if (figureType == FigureType::KING) {
        positions = parseKingMotion(position);
    } else if (figureType == FigureType::QUEUEN) {
        positions = parseQueunMotion(position);
    }

    return positions;
}

void GameLogic::setPlayerColor(PlayerChooseColor _playerColor)
{
    playerColor = _playerColor;
}

QVector<QPair<int, int>> GameLogic::parsePawnMotion(const QPair<int, int>& position,
                                                    bool isPlayerMove)
{
    QVector<QPair<int, int>> positions;
    QVector<QPair<FigureMotionType, QVector<QPair<int, int>>>> figureMotionVector
        = figureMotion[FigureType::PAWN];
    QPair<int, int> pos;
    if (isPlayerMove) {
        for (auto& i : figureMotionVector) {
            if (i.first == FigureMotionType::BACK_MOTION) {

                pos = QPair<int, int>(i.second[0].first + position.first,
                                      i.second[0].second + position.second);

                if (pos.first < cellHeightCount && pos.first >= 0 && pos.second < cellWidthCount
                    && pos.second >= 0 && currentGame[pos.first][pos.second] == 0) {
                    positions.push_back(pos);
                }
                continue;
            } else if (i.first == FigureMotionType::RIGHT_BACK_PAWN_ATTACK
                       || i.first == FigureMotionType::LEFT_BACK_PAWN_ATTACK) {

                pos = QPair<int, int>(i.second[0].first + position.first,
                                      i.second[0].second + position.second);

                if (pos.first < cellHeightCount && pos.first >= 0 && pos.second < cellWidthCount
                    && pos.second >= 0
                    && (currentGame[pos.first][pos.second]
                            * currentGame[position.first][position.second]
                        < 0)) {
                    positions.push_back(pos);
                }
                continue;
            } else if (i.first == FigureMotionType::FIRST_MOTION_BACK) {
                pos = QPair<int, int>(i.second[0].first + position.first,
                                      i.second[0].second + position.second);

                if (pos.first < cellHeightCount && pos.first >= 0 && pos.second < cellWidthCount
                    && pos.second >= 0 && currentGame[pos.first][pos.second] == 0
                    && currentGame[pos.first + 1][pos.second] == 0) {
                    positions.push_back(pos);
                }
                continue;
            }
        }
    } else {
        for (auto& i : figureMotionVector) {
            if (i.first == FigureMotionType::FIRST_MOTION_FORWARD) {
                pos = QPair<int, int>(i.second[0].first + position.first,
                                      i.second[0].second + position.second);

                if (pos.first < cellHeightCount && pos.first >= 0 && pos.second < cellWidthCount
                    && pos.second >= 0 && currentGame[pos.first - 1][pos.second] == 0
                    && currentGame[pos.first][pos.second] == 0) {
                    positions.push_back(pos);
                }
                continue;
            } else if (i.first == FigureMotionType::RIGHT_FORWARD_PAWN_ATTACK
                       || i.first == FigureMotionType::LEFT_FORWARD_PAWN_ATTACK) {

                pos = QPair<int, int>(i.second[0].first + position.first,
                                      i.second[0].second + position.second);

                if (pos.first < cellHeightCount && pos.first >= 0 && pos.second < cellWidthCount
                    && pos.second >= 0
                    && (currentGame[pos.first][pos.second]
                            * currentGame[position.first][position.second]
                        < 0)) {
                    positions.push_back(pos);
                }
                continue;
            } else if (i.first == FigureMotionType::FORWARD_MOTION) {
                pos = QPair<int, int>(i.second[0].first + position.first,
                                      i.second[0].second + position.second);

                if (pos.first < cellHeightCount && pos.first >= 0 && pos.second < cellWidthCount
                    && pos.second >= 0 && currentGame[pos.first][pos.second] == 0
                    && currentGame[pos.first][pos.second] == 0) {
                    positions.push_back(pos);
                }
                continue;
            }
        }
    }

    return positions;
}

QVector<QPair<int, int>> GameLogic::parseHorseMotion(const QPair<int, int>& position)
{
    QVector<QPair<int, int>> positions;
    QVector<QPair<FigureMotionType, QVector<QPair<int, int>>>> figureMotionVector
        = figureMotion[FigureType::HORSE];
    QPair<int, int> pos;

    for (auto& i : figureMotionVector[0].second) {
        pos = QPair<int, int>(i.first + position.first, i.second + position.second);

        if (pos.first < cellHeightCount && pos.first >= 0 && pos.second < cellWidthCount
            && pos.second >= 0
            && currentGame[pos.first][pos.second] * currentGame[position.first][position.second]
                <= 0) {
            positions.push_back(pos);
        }
        continue;
    }

    return positions;
}

QVector<QPair<int, int>> GameLogic::parseElephantMotion(const QPair<int, int>& position)
{
    QVector<QPair<int, int>> positions;
    QVector<QPair<FigureMotionType, QVector<QPair<int, int>>>> figureMotionVector
        = figureMotion[FigureType::ELEPHANT];

    for (auto& i : figureMotionVector) {
        positions += parseLineMotion(position, i.second);
    }

    return positions;
}

QVector<QPair<int, int>> GameLogic::parseRookMotion(const QPair<int, int>& position)
{
    QVector<QPair<int, int>> positions;
    QVector<QPair<FigureMotionType, QVector<QPair<int, int>>>> figureMotionVector
        = figureMotion[FigureType::ROOK];

    for (auto& i : figureMotionVector) {
        positions += parseLineMotion(position, i.second);
    }

    return positions;
}

QVector<QPair<int, int>> GameLogic::parseKingMotion(const QPair<int, int>& position)
{
    QVector<QPair<int, int>> positions;
    QVector<QPair<FigureMotionType, QVector<QPair<int, int>>>> figureMotionVector
        = figureMotion[FigureType::KING];

    for (auto& i : figureMotionVector) {
        positions += parseLineMotion(position, i.second);
    }

    return positions;
}

QVector<QPair<int, int>> GameLogic::parseQueunMotion(const QPair<int, int>& position)
{
    QVector<QPair<int, int>> positions;
    QVector<QPair<FigureMotionType, QVector<QPair<int, int>>>> figureMotionVector
        = figureMotion[FigureType::QUEUEN];

    for (auto& i : figureMotionVector) {
        positions += parseLineMotion(position, i.second);
    }

    return positions;
}

QVector<QPair<int, int>> GameLogic::parseLineMotion(const QPair<int, int>& position,
                                                    const QVector<QPair<int, int>>& possibleMotions)
{
    QVector<QPair<int, int>> positions;
    QPair<int, int> pos;

    for (auto& i : possibleMotions) {
        pos = QPair<int, int>(position.first + i.first, position.second + i.second);

        if (pos.first < cellHeightCount && pos.first >= 0 && pos.second < cellWidthCount
            && pos.second >= 0
            && currentGame[pos.first][pos.second] * currentGame[position.first][position.second]
                <= 0) {
            positions.push_back(pos);
        }

        if ((currentGame[pos.first][pos.second] * currentGame[position.first][position.second])
            != 0) {
            break;
        }
    }

    return positions;
}

void GameLogic::initCurrentGameBoard()
{
    if (playerColor == PlayerChooseColor::BLACK) {
        for (int i = 0; i < cellHeightCount; ++i) {
            for (int j = 0; j < cellWidthCount; ++j) {
                currentGame[i][j] = chessBoardStartFigureBlackPosition[i][j];
            }
        }
    } else {
        for (int i = 0; i < cellHeightCount; ++i) {
            for (int j = 0; j < cellWidthCount; ++j) {
                currentGame[i][j] = chessBoardStartFigureWhitePosition[i][j];
            }
        }
    }
}
