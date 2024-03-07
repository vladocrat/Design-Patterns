#pragma once

#include <QQuickPaintedItem>

#include "figuretype.h"

namespace Constants
{
constexpr static const size_t moveThreshold { 10 };
} //! Constants

class Movable : public QQuickPaintedItem
{
    Q_OBJECT
public:
    ~Movable() override = default;

    FigureType::Value type() const { return m_type; }

    virtual void setBoardX(float) = 0;
    virtual void setBoardY(float) = 0;

signals:
    void moved(Movable*);
    void openMenu(Movable*);

protected:
    FigureType::Value m_type { FigureType::Value::None };
};
