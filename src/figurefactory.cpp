#include "figurefactory.h"

#include "circle.h"
#include "rectangle.h"
#include "triangle.h"

Movable* FigureFactory::create(FigureType::Value t) noexcept
{
    switch (t)
    {
    case FigureType::Value::Circle:
        return new Circle;
    case FigureType::Value::Rectangle:
        return new Rectangle;
    case FigureType::Value::Triangle:
        return new Triangle;
    case FigureType::Value::None:
        return nullptr;
    default:
        Q_UNREACHABLE();
    }

    Q_UNREACHABLE();
}
