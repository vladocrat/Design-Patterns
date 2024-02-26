#pragma once

#include <QQuickPaintedItem>

#include "pimpl.h"
#include "movable.h"

class Triangle : public Movable
{
    Q_OBJECT
public:
    explicit Triangle(QQuickPaintedItem* parent = nullptr);
    ~Triangle() override;

    void paint(QPainter* painter) override;

    void setBoardX(float) override;
    void setBoardY(float) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    DECLARE_PIMPL
};
