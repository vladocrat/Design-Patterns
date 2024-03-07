#include "figurecontroller.h"

#include <QQuickPaintedItem>
#include <QQmlEngine>
#include <deque>

#include "figuretype.h"
#include "history.h"
#include "boardstate.h"
#include "figurefactory.h"

struct FigureController::impl_t
{
    std::deque<Movable*> items;
    History history;
    Movable* lastChosenObj   { nullptr };
    BoardState* currentState { nullptr };
};

FigureController::FigureController()
{
    createImpl();
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

    auto item = FigureFactory::create(static_cast<FigureType::Value>(t));

    if (!item) return;

    QObject::connect(item, &Movable::openMenu, this, &FigureController::openMenu);
    QObject::connect(item, &Movable::moved, this, &FigureController::saveState);

    item->setBoardX(x);
    item->setBoardY(y);

    QQmlEngine::setObjectOwnership(item, QQmlEngine::CppOwnership);
    impl().items.push_back(item);
    emit objectsChanged();
    saveState();
}

void FigureController::remove()
{
    auto item = std::find(impl().items.begin(), impl().items.end(), impl().lastChosenObj);

    if (item == impl().items.end())
    {
        return;
    }

    impl().items.erase(item);

    emit objectsChanged();
    saveState();
}

void FigureController::saveState()
{
    impl().history.putUndo(new BoardState{ impl().items });
}

void FigureController::openMenu(Movable* item)
{
    impl().lastChosenObj = item;
    emit menuOpened();
}

void FigureController::undo()
{
    if (impl().history.undoIsEmpty())
    {
        return;
    }

    auto state = impl().history.popUndo(new BoardState{ impl().items });
    impl().items = state->restore();

    emit objectsChanged();
}

void FigureController::redo()
{
    if (impl().history.redoIsEmpty())
    {
        return;
    }

    auto state = impl().history.popRedo(new BoardState{ impl().items });

    if (!state)
    {
        return;
    }

    impl().items = state->restore();

    emit objectsChanged();
}

QList<QObject*> FigureController::objects() const
{
    QList<QObject*> list;

    for (const auto& element : impl().items)
    {
        list.append(element);
    }

    return list;
}

void FigureController::registerType()
{
    qmlRegisterSingletonInstance("FigureController", 1, 0, "FigureController", FigureController::instance());
}
