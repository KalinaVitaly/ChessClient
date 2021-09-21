#include "positionmap.h"

PositionMap::PositionMap(QWidget* parent)
    : QLabel(parent)
{
    // resize(60, 60);
    setMinimumSize(100, 100);
}

void PositionMap::setPositionMap(const QVector<int>& map)
{
    posMap = map;
}

void PositionMap::mousePressEvent(QMouseEvent* _event)
{
    Q_UNUSED(_event)
}

void PositionMap::paintEvent(QPaintEvent* _event)
{
    Q_UNUSED(_event)

    QPainter painter(this);
    QPen pen(Qt::black, 2, Qt::SolidLine);

    for (int i = 0; i < posMap.size(); ++i) {
        drawRectangle(&painter, i);
    }
}

void PositionMap::resizeEvent(QResizeEvent* _event)
{
    int minSize = qMin(_event->size().width(), _event->size().height());
    resize(minSize, minSize);

    cellHeight = minSize / cellHeightCount;
    cellWidth = minSize / cellWidthCount;

    repaint();
}

void PositionMap::drawRectangle(QPainter* painter, int index)
{
    if (posMap[index] > 0 && posMap[index] < 7) {
        painter->setBrush(QBrush("#7d7f7d"));
    } else if (posMap[index] < 0 && posMap[index] > -7) {
        painter->setBrush(QBrush("#cccccc"));
    } else if (posMap[index] == 8) {
        painter->setBrush(QBrush("#0000ff"));
    } else if (posMap[index] == -8) {
        painter->setBrush(QBrush("#f80000"));
    } else {
        painter->setBrush(QBrush("#ffffff"));
    }

    painter->drawRect(cellWidth * (index % cellWidthCount), cellHeight * (index / cellHeightCount),
                      cellWidth, cellHeight);
}
