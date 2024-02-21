#pragma once

#include <QQuickPaintedItem>

#include "pimpl.h"
#include "movable.h"

class Circle : public Movable
{
    Q_OBJECT
public:
    explicit Circle(QQuickPaintedItem* parent = nullptr);
    ~Circle() override;

    void paint(QPainter* painter) override;

    void setBoardX(float) override;
    void setBoardY(float) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    DECLARE_PIMPL

};
