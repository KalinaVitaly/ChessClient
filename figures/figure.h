#ifndef FIGURE_H
#define FIGURE_H

#include <QSvgWidget>

#include <storage.h>

class Figure : public QSvgWidget
{
    Q_OBJECT
public:
    Figure(QWidget* parent = nullptr);

public:
    void setFigureWidget(FigureColor _figureColor, FigureType _figureType);

    QPair<FigureColor, FigureType> getFigureType();

private:
    FigureType type;
    FigureColor color;
};

#endif // FIGURE_H
