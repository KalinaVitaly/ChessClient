#ifndef STORAGE_H
#define STORAGE_H

#include <QColor>
#include <QMap>
#include <QVector>

const int minWidth = 600;
const int minHeight = 600;
const int cellHeightCount = 8;
const int cellWidthCount = 8;
const int animationTime = 1000;
const QString filePathImage = ":/figureImages/";

enum class CellType { WHITE, BLACK };
enum class FigureColor { WHITE, BLACK, UNKNOWN };
enum class PlayerChooseColor { WHITE, BLACK };
enum class FigureType { ROOK, KING, QUEUEN, PAWN, HORSE, ELEPHANT, UNKNOWN };
enum class FigureMotionType {
    FIRST_MOTION_FORWARD,
    FIRST_MOTION_BACK,
    FORWARD_MOTION,
    BACK_MOTION,
    LEFT_MOTION,
    RIGHT_MOTION,
    RIGHT_FORWARD_PAWN_ATTACK,
    LEFT_FORWARD_PAWN_ATTACK,
    RIGHT_BACK_PAWN_ATTACK,
    LEFT_BACK_PAWN_ATTACK,
    DIAGONAL_MOTION_FORWARD_RIGHT,
    DIAGONAL_MOTION_FORWARD_LEFT,
    DIAGONAL_MOTION_BACK_RIGHT,
    DIAGONAL_MOTION_BACK_LEFT,
    HORIZONTAL_MOTION_RIGHT,
    HORIZONTAL_MOTION_LEFT,
    VERTICAL_MOTION_FORWARD,
    VERTICAL_MOTION_BACK,
    HORSE_MOTION
};

static QMap<FigureType, int> figureMaxElements{
    { FigureType::KING, 1 },  { FigureType::PAWN, 8 },     { FigureType::QUEUEN, 1 },
    { FigureType::HORSE, 2 }, { FigureType::ELEPHANT, 2 }, { FigureType::ROOK, 2 }
};

static QMap<FigureMotionType, QVector<QPair<int, int>>> figuresMotions{
    { FigureMotionType::FORWARD_MOTION, { { 1, 0 } } },
    { FigureMotionType::BACK_MOTION, { { -1, 0 } } },
    { FigureMotionType::LEFT_MOTION, { { 0, -1 } } },
    { FigureMotionType::RIGHT_MOTION, { { 0, 1 } } },
    { FigureMotionType::FIRST_MOTION_FORWARD, { { 2, 0 } } },
    { FigureMotionType::FIRST_MOTION_FORWARD, { { 2, 0 } } },
    { FigureMotionType::FIRST_MOTION_BACK, { { -2, 0 } } },
    { FigureMotionType::RIGHT_FORWARD_PAWN_ATTACK, { { 1, 1 } } },
    { FigureMotionType::LEFT_FORWARD_PAWN_ATTACK, { { 1, -1 } } },
    { FigureMotionType::RIGHT_BACK_PAWN_ATTACK, { { -1, 1 } } },
    { FigureMotionType::LEFT_BACK_PAWN_ATTACK, { { -1, -1 } } },
    { FigureMotionType::DIAGONAL_MOTION_FORWARD_LEFT,
      { { 1, -1 }, { 2, -2 }, { 3, -3 }, { 4, -4 }, { 5, -5 }, { 6, -6 }, { 7, -7 } } },
    { FigureMotionType::DIAGONAL_MOTION_FORWARD_RIGHT,
      { { 1, 1 }, { 2, 2 }, { 3, 3 }, { 4, 4 }, { 5, 5 }, { 6, 6 }, { 7, 7 } } },
    { FigureMotionType::DIAGONAL_MOTION_BACK_RIGHT,
      { { -1, 1 }, { -2, 2 }, { -3, 3 }, { -4, 4 }, { -5, 5 }, { -6, 6 }, { -7, 7 } } },
    { FigureMotionType::DIAGONAL_MOTION_BACK_LEFT,
      { { -1, -1 }, { -2, -2 }, { -3, -3 }, { -4, -4 }, { -5, -5 }, { -6, -6 }, { -7, -7 } } },
    { FigureMotionType::HORIZONTAL_MOTION_RIGHT,
      { { 0, 1 }, { 0, 2 }, { 0, 3 }, { 0, 4 }, { 0, 5 }, { 0, 6 }, { 0, 7 } } },
    { FigureMotionType::HORIZONTAL_MOTION_LEFT,
      { { 0, -1 }, { 0, -2 }, { 0, -3 }, { 0, -4 }, { 0, -5 }, { 0, -6 }, { 0, -7 } } },
    { FigureMotionType::VERTICAL_MOTION_FORWARD,
      { { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 }, { 5, 0 }, { 6, 0 }, { 7, 0 } } },
    { FigureMotionType::VERTICAL_MOTION_BACK,
      { { -1, 0 }, { -2, 0 }, { -3, 0 }, { -4, 0 }, { -5, 0 }, { -6, 0 }, { -7, 0 } } },
    { FigureMotionType::HORSE_MOTION,
      { { 2, 1 }, { 2, -1 }, { 1, 2 }, { 1, -2 }, { -2, 1 }, { -2, -1 }, { -1, 2 }, { -1, -2 } } }
};

static QMap<FigureType, QVector<QPair<FigureMotionType, QVector<QPair<int, int>>>>> figureMotion{
    { FigureType::HORSE,
      { { FigureMotionType::HORSE_MOTION, { figuresMotions[FigureMotionType::HORSE_MOTION] } } } },
    { FigureType::PAWN,
      { { FigureMotionType::FIRST_MOTION_FORWARD,
          { figuresMotions[FigureMotionType::FIRST_MOTION_FORWARD] } },
        { FigureMotionType::FIRST_MOTION_BACK,
          { figuresMotions[FigureMotionType::FIRST_MOTION_BACK] } },
        { FigureMotionType::FORWARD_MOTION, { figuresMotions[FigureMotionType::FORWARD_MOTION] } },
        { FigureMotionType::BACK_MOTION, { figuresMotions[FigureMotionType::BACK_MOTION] } },
        { FigureMotionType::RIGHT_FORWARD_PAWN_ATTACK,
          { figuresMotions[FigureMotionType::RIGHT_FORWARD_PAWN_ATTACK] } },
        { FigureMotionType::LEFT_FORWARD_PAWN_ATTACK,
          { figuresMotions[FigureMotionType::LEFT_FORWARD_PAWN_ATTACK] } },
        { FigureMotionType::RIGHT_BACK_PAWN_ATTACK,
          { figuresMotions[FigureMotionType::RIGHT_BACK_PAWN_ATTACK] } },
        { FigureMotionType::LEFT_BACK_PAWN_ATTACK,
          { figuresMotions[FigureMotionType::LEFT_BACK_PAWN_ATTACK] } } } },
    { FigureType::QUEUEN,
      { { FigureMotionType::FORWARD_MOTION, { figuresMotions[FigureMotionType::FORWARD_MOTION] } },
        { FigureMotionType::BACK_MOTION, { figuresMotions[FigureMotionType::BACK_MOTION] } },
        { FigureMotionType::LEFT_MOTION, { figuresMotions[FigureMotionType::LEFT_MOTION] } },
        { FigureMotionType::RIGHT_MOTION, { figuresMotions[FigureMotionType::RIGHT_MOTION] } } } },
    { FigureType::ELEPHANT,
      { { FigureMotionType::DIAGONAL_MOTION_FORWARD_RIGHT,
          { figuresMotions[FigureMotionType::DIAGONAL_MOTION_FORWARD_RIGHT] } },
        { FigureMotionType::DIAGONAL_MOTION_BACK_RIGHT,
          { figuresMotions[FigureMotionType::DIAGONAL_MOTION_BACK_RIGHT] } },
        { FigureMotionType::DIAGONAL_MOTION_FORWARD_LEFT,
          { figuresMotions[FigureMotionType::DIAGONAL_MOTION_FORWARD_LEFT] } },
        { FigureMotionType::DIAGONAL_MOTION_BACK_LEFT,
          { figuresMotions[FigureMotionType::DIAGONAL_MOTION_BACK_LEFT] } } } },
    { FigureType::ROOK,
      { { FigureMotionType::HORIZONTAL_MOTION_RIGHT,
          { figuresMotions[FigureMotionType::HORIZONTAL_MOTION_RIGHT] } },
        { FigureMotionType::HORIZONTAL_MOTION_LEFT,
          { figuresMotions[FigureMotionType::HORIZONTAL_MOTION_LEFT] } },
        { FigureMotionType::VERTICAL_MOTION_FORWARD,
          { figuresMotions[FigureMotionType::VERTICAL_MOTION_FORWARD] } },
        { FigureMotionType::VERTICAL_MOTION_BACK,
          { figuresMotions[FigureMotionType::VERTICAL_MOTION_BACK] } } } },
    { FigureType::KING,
      { { FigureMotionType::HORIZONTAL_MOTION_RIGHT,
          { figuresMotions[FigureMotionType::HORIZONTAL_MOTION_RIGHT] } },
        { FigureMotionType::HORIZONTAL_MOTION_LEFT,
          { figuresMotions[FigureMotionType::HORIZONTAL_MOTION_LEFT] } },
        { FigureMotionType::VERTICAL_MOTION_FORWARD,
          { figuresMotions[FigureMotionType::VERTICAL_MOTION_FORWARD] } },
        { FigureMotionType::VERTICAL_MOTION_BACK,
          { figuresMotions[FigureMotionType::VERTICAL_MOTION_BACK] } },
        { FigureMotionType::DIAGONAL_MOTION_FORWARD_RIGHT,
          { figuresMotions[FigureMotionType::DIAGONAL_MOTION_FORWARD_RIGHT] } },
        { FigureMotionType::DIAGONAL_MOTION_BACK_RIGHT,
          { figuresMotions[FigureMotionType::DIAGONAL_MOTION_BACK_RIGHT] } },
        { FigureMotionType::DIAGONAL_MOTION_FORWARD_LEFT,
          { figuresMotions[FigureMotionType::DIAGONAL_MOTION_FORWARD_LEFT] } },
        { FigureMotionType::DIAGONAL_MOTION_BACK_LEFT,
          { figuresMotions[FigureMotionType::DIAGONAL_MOTION_BACK_LEFT] } } } }
};

// static QMap<FigureType, QVector<QPair<int, int>>> figureMotion;


static int chessBoardStartFigureWhitePosition[cellHeightCount][cellWidthCount]
    = { { -4, -2, -3, -5, -6, -3, -2, -4 }, { -1, -1, -1, -1, -1, -1, -1, -1 },
        { 0, 0, 4, 1, 0, 0, 0, 0 },         { 0, 0, -8, 0, 0, 2, 0, 0 },
        { 0, -6, 0, 3, 0, 0, 8, 0 },        { 0, 0, 0, 0, -1, 1, -5, -1 },
        { 1, 1, 1, 1, 1, 1, 1, 1 },         { 4, 2, 3, 6, 5, 3, 2, 4 } };

static int chessBoardStartFigureBlackPosition[cellHeightCount][cellWidthCount]
    = { { 4, 2, 3, 5, 6, 3, 2, 4 },         { 1, 1, 1, 1, 1, 1, 1, 1 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },         { 0, 0, 0, 0, 0, 0, 0, 0 },
        { 0, 0, 0, 0, 0, 0, 0, 0 },         { 0, 0, 0, 0, 0, 0, 0, 0 },
        { -1, -1, -1, -1, -1, -1, -1, -1 }, { -4, -2, -3, -6, -5, -3, -2, -4 } };

struct choosenCell {
    QColor startColor;
    QColor finishColor;
    QColor currentColor;
};

#endif // STORAGE_H
