#pragma once

#include <QQuickPaintedItem>

class Movable : public QQuickPaintedItem
{
    Q_OBJECT
public:
    virtual void setBoardX(float) = 0;
    virtual void setBoardY(float) = 0;

signals:
    void openMenu(Movable*);
};
