#ifndef CELL_H
#define CELL_H

#include "figures/figure.h"
#include "storage.h"

#include <QFrame>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QResizeEvent>

class Cell : public QFrame
{
    Q_OBJECT
    Q_PROPERTY(QColor background READ getCellBackground WRITE setCellBackground)
    QPropertyAnimation* cellBackgroundAnimation;

public:
    explicit Cell(CellType type, QWidget* parent = nullptr);

    bool getIsCurrentCell();
    bool getIsMotionCell();
    QPair<FigureColor, FigureType> getFigureType();
    bool isFigureWidgetSet();
    QColor getCellBackground();

    void setIsCurrentCell(bool _isCurrentCell);
    void setIsMotionCell(bool _isMotionCell);
    void setFigureWidget(FigureColor figureColor, FigureType figureType);
    void setCellBackground(const QColor& _color);

    QPropertyAnimation* getPropertyAnimation();

protected:
    void paintEvent(QPaintEvent* _event) override;
    void enterEvent(QEvent* _event) override;
    void leaveEvent(QEvent* _event) override;
    void resizeEvent(QResizeEvent* _event) override;
    void mouseReleaseEvent(QMouseEvent* _event) override;

private:
    void setColor();
    void animationInit();
    void startAnimation(QPropertyAnimation* animation);


private:
    Figure* figureWidget;
    FigureColor figureColor;
    FigureType figureType;
    QColor backgroundCellColor;
    QColor hoverBackgroundColor;
    QColor penLineColor;
    QColor currentPenLineColor;
    QColor startCurrentCellBackgroundColor;
    QColor cellBackgroundColor;
    QColor finishCurrentCellBackgroundColor;
    QColor startPossibleMotionBackgroundColor;
    QColor finishPossibleMotionBackgroundColor;
    CellType typeCell;
    QPointF centerPoint;
    qreal penLineWidth;
    int animationTime;
    bool isForwardAnimation;
    bool isHover;
    bool isCurrentCell;
    bool isMotionCell;

signals:
    void currentCellChanged();
};

#endif // CELL_H
