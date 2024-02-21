#include "figurecontroller.h"

#include <QQuickPaintedItem>
#include <QQmlEngine>
#include <deque>

#include "circle.h"
#include "rectangle.h"
#include "triangle.h"
#include "figuretype.h"

namespace Internal
{
Movable* createItem(FigureType::Value t)
{
    qDebug() << t;

    switch (t)
    {
    case FigureType::Value::Circle:
        return new Circle;
    case FigureType::Value::Rectangle:
        return new Rectangle;
    case FigureType::Value::Triangle:
        return new Triangle;
    case FigureType::Value::None:
        return nullptr; //! TODO Throw error?
    default:
        Q_UNREACHABLE();
    }
}
} //! Internal

struct FigureController::impl_t
{
    std::deque<Movable*> items;
};

FigureController::FigureController()
{
    createImpl();

    QObject::connect(this, &FigureController::objectsChanged, this, [this]() {
        qDebug() << impl().items.size();
    });
}

FigureController::~FigureController()
{

}

FigureController* FigureController::instance()
{
    static FigureController fc;
    return &fc;
}

void FigureController::addItem(int t, float x, float y)
{
    qDebug() << Q_FUNC_INFO;
    auto item = Internal::createItem(static_cast<FigureType::Value>(t));

    item->setBoardX(x);
    item->setBoardY(y);

    QQmlEngine::setObjectOwnership(item, QQmlEngine::CppOwnership);
    impl().items.push_back(item);
    emit objectsChanged();
}

QList<QObject*> FigureController::objects() const
{
    qDebug() << Q_FUNC_INFO;
    QList<QObject*> list;

    for (const auto& element : impl().items)
    {
        list.append(element);
    }

    qDebug() << "list.size()" << list.size();
    return list;
}

void FigureController::registerType()
{
    qmlRegisterSingletonInstance("FigureController", 1, 0, "FigureController", FigureController::instance());
}
