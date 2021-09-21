#include "figures/figure.h"

Figure::Figure(QWidget* parent)
    : QSvgWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
}

void Figure::setFigureWidget(FigureColor _figureColor, FigureType _figureType)
{
    type = _figureType;
    color = _figureColor;
    QString fileFigurePath = filePathImage /*":/figureImages/WhitePawn.svg"*/;

    if (_figureColor == FigureColor::BLACK) {
        fileFigurePath += "Black";
    } else if (_figureColor == FigureColor::WHITE) {
        fileFigurePath += "White";
    }

    if (_figureType == FigureType::ELEPHANT) {
        fileFigurePath += "Elephant";
    } else if (_figureType == FigureType::HORSE) {
        fileFigurePath += "Horse";
    } else if (_figureType == FigureType::KING) {
        fileFigurePath += "King";
    } else if (_figureType == FigureType::PAWN) {
        fileFigurePath += "Pawn";
    } else if (_figureType == FigureType::QUEUEN) {
        fileFigurePath += "Queuen";
    } else if (_figureType == FigureType::ROOK) {
        fileFigurePath += "Rook";
    }

    fileFigurePath += ".svg";

    load(fileFigurePath);
    raise();
}

QPair<FigureColor, FigureType> Figure::getFigureType()
{
    return QPair<FigureColor, FigureType>(color, type);
}
