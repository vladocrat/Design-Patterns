#pragma once

#include "movable.h"
#include "pimpl.h"

class Rectangle : public Movable
{
    Q_OBJECT
public:
    explicit Rectangle(QQuickPaintedItem* parent = nullptr);
    ~Rectangle() override;

    void paint(QPainter* painter) override;

    void setBoardX(float) override;
    void setBoardY(float) override;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    DECLARE_PIMPL
};

