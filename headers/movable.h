#pragma once

#include <QQuickPaintedItem>

namespace Constants
{
constexpr static const size_t moveThreshold { 10 };
} //! Constants

class Movable : public QQuickPaintedItem
{
    Q_OBJECT
public:
    ~Movable() override = default;

    virtual void setBoardX(float) = 0;
    virtual void setBoardY(float) = 0;

signals:
    void moved();
    void openMenu(Movable*);
};
