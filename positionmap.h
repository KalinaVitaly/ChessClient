#ifndef POSITIONMAP_H
#define POSITIONMAP_H

#include "storage.h"

#include <QLabel>
#include <QPainter>
#include <QResizeEvent>

class PositionMap : public QLabel
{
public:
    explicit PositionMap(QWidget* parent = nullptr);

    void setPositionMap(const QVector<int>& map);

protected:
    void mousePressEvent(QMouseEvent* _event) override;
    void paintEvent(QPaintEvent* _event) override;
    void resizeEvent(QResizeEvent* _event) override;

private:
    void drawRectangle(QPainter* painter, int index);

private:
    QVector<int> posMap;
    int cellWidth;
    int cellHeight;
};

#endif // POSITIONMAP_H
