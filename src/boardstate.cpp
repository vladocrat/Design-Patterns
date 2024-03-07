#include "boardstate.h"

#include <QQmlEngine>

#include "figurefactory.h"
#include "figurecontroller.h"

static size_t counter;

struct BoardState::impl_t
{
    std::deque<Movable*> objs;
};

BoardState::BoardState()
{
    createImpl();

    counter++;
    qDebug() << "counter" << counter;
    ix = counter;
}

BoardState::BoardState(const std::deque<Movable*>& boardObjects)
{
    createImpl();

    counter++;
    qDebug() << "counter" << counter;
    ix = counter;

    for (const auto& obj : boardObjects)
    {
        auto newObj = FigureFactory::create(obj->type());

        if (!newObj) continue;

        QObject::connect(newObj, &Movable::moved, FigureController::instance(), &FigureController::saveState);
        QObject::connect(newObj, &Movable::openMenu, FigureController::instance(), &FigureController::openMenu);
        QQmlEngine::setObjectOwnership(newObj, QQmlEngine::CppOwnership);

        newObj->setBoardX(obj->x());
        newObj->setBoardY(obj->y());
        impl().objs.push_back(newObj);
    }
}

BoardState::~BoardState()
{
    for (const auto obj : impl().objs)
    {
        delete obj;
    }
}

bool BoardState::isEmpty() const noexcept
{
    return impl().objs.empty();
}

std::deque<Movable*> BoardState::restore() noexcept
{
    return impl().objs;
}
