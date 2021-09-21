#include "cell.h"

#include <QDebug>
#include <QPainter>
#include <QResizeEvent>
#include <QtSvg>

Cell::Cell(CellType type, QWidget* parent)
    : QFrame(parent)
    , figureWidget(nullptr)
    , hoverBackgroundColor(QColor(255, 0, 0, 25))
    , penLineColor(Qt::red)
    , currentPenLineColor(Qt::blue)
    , startCurrentCellBackgroundColor(QColor(64, 224, 208, 100))
    , cellBackgroundColor(QColor(64, 224, 208, 100))
    , finishCurrentCellBackgroundColor(QColor(255, 140, 0, 100))
    , startPossibleMotionBackgroundColor(QColor(0, 155, 0, 15))
    , finishPossibleMotionBackgroundColor(QColor(0, 0, 255, 155))
    , typeCell(type)
    , penLineWidth(2)
    , animationTime(1000)
    , isHover(false)
    , isCurrentCell(false)
    , isMotionCell(false)
{
    setMinimumSize(40, 40);
    setColor();
    animationInit();
}

void Cell::paintEvent(QPaintEvent* _event)
{
    Q_UNUSED(_event)

    QPainter painter(this);
    QRect r = rect();

    painter.setBrush(QBrush(backgroundCellColor));
    painter.fillRect(r, painter.brush());
    painter.setBrush(QBrush(Qt::blue));

    if (isHover) {
        QPen pen = QPen(QBrush(penLineColor), penLineWidth);
        painter.setBrush(QBrush(hoverBackgroundColor));
        painter.setPen(pen);
        painter.drawRect(0, 0, width(), height());
        setFrameStyle(QFrame::Box);
        setLineWidth(penLineWidth);
    }

    if (isCurrentCell) {
        QPen pen = QPen(QBrush(currentPenLineColor), penLineWidth);
        painter.setBrush(QBrush(cellBackgroundColor));
        painter.setPen(pen);
        painter.drawRect(0, 0, width(), height());
        setFrameStyle(QFrame::Box);
        setLineWidth(penLineWidth);
    }

    if (isMotionCell) {
        QPen pen = QPen(QBrush(currentPenLineColor), penLineWidth);
        painter.setBrush(QBrush(cellBackgroundColor));
        painter.setPen(pen);
        painter.drawRect(0, 0, width(), height());
        setFrameStyle(QFrame::Box);
        setLineWidth(penLineWidth);
    }
}

void Cell::setColor()
{
    if (typeCell == CellType::BLACK) {
        backgroundCellColor = QColor(Qt::gray);
    } else {
        backgroundCellColor = QColor(Qt::white);
    }
}

void Cell::animationInit()
{
    cellBackgroundAnimation = new QPropertyAnimation(this);
    cellBackgroundAnimation->setPropertyName("background"); //свойство для анимации
    cellBackgroundAnimation->setTargetObject(this); //свойство какого объекта
    cellBackgroundAnimation->setDuration(animationTime); //продолжительность смен

    isForwardAnimation = false;
}

void Cell::startAnimation(QPropertyAnimation* animation)
{
    if (isForwardAnimation) {
        animation->setDirection(QAbstractAnimation::Forward);
        isForwardAnimation = false;
    } else {
        animation->setDirection(QAbstractAnimation::Backward);
        isForwardAnimation = true;
    }
    animation->start();
}

void Cell::enterEvent(QEvent* _event)
{
    Q_UNUSED(_event);
    isHover = true;
    update();
}

void Cell::leaveEvent(QEvent* _event)
{
    Q_UNUSED(_event);
    isHover = false;
    repaint();
}

void Cell::setIsCurrentCell(bool _isCurrentCell)
{
    isCurrentCell = _isCurrentCell;

    if (!_isCurrentCell) {
        cellBackgroundAnimation->stop();
    }
}

void Cell::setIsMotionCell(bool _isMotionCell)
{
    isMotionCell = _isMotionCell;

    if (_isMotionCell) {
        setCellBackground(startPossibleMotionBackgroundColor);
        cellBackgroundAnimation->setStartValue(startPossibleMotionBackgroundColor);
        cellBackgroundAnimation->setEndValue(finishPossibleMotionBackgroundColor); //в какой
        startAnimation(cellBackgroundAnimation);
        // animationTimer->start(animationTime);
    } else {
        cellBackgroundAnimation->stop();
    }

    update();
}

void Cell::setFigureWidget(FigureColor figureColor, FigureType figureType)
{
    figureWidget = new Figure(this);
    figureWidget->setFigureWidget(figureColor, figureType);
}

bool Cell::getIsCurrentCell()
{
    return isCurrentCell;
}

bool Cell::getIsMotionCell()
{
    return isMotionCell;
}

QPair<FigureColor, FigureType> Cell::getFigureType()
{
    if (figureWidget == nullptr)
        return { FigureColor::UNKNOWN, FigureType::UNKNOWN };

    return figureWidget->getFigureType();
}

QColor Cell::getCellBackground()
{
    return cellBackgroundColor;
}

void Cell::setCellBackground(const QColor& _color)
{

    cellBackgroundColor = _color;

    update();
}

QPropertyAnimation* Cell::getPropertyAnimation()
{
    return cellBackgroundAnimation;
}

void Cell::resizeEvent(QResizeEvent* _event)
{
    if (figureWidget != nullptr) {
        figureWidget->setGeometry(0, 0, _event->size().width(), _event->size().height());
    }
}

void Cell::mouseReleaseEvent(QMouseEvent* _event)
{
    Q_UNUSED(_event)
    isCurrentCell = true;

    setCellBackground(startCurrentCellBackgroundColor);
    cellBackgroundAnimation->setStartValue(startCurrentCellBackgroundColor);
    cellBackgroundAnimation->setEndValue(finishCurrentCellBackgroundColor); //в какой
    cellBackgroundAnimation->setDirection(QAbstractAnimation::Forward);
    //    cellBackgroundAnimation->start();
    //    animationTimer->start(animationTime);
    emit currentCellChanged();
    update();
}
