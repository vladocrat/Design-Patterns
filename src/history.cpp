#include "history.h"

#include <deque>

#include "boardstate.h"

namespace Constants
{
constexpr static const size_t MAX_QUEUE_SIZE { 5 };
} //! Constants

struct History::impl_t
{
    std::deque<BoardState*> undoQueue;
    std::deque<BoardState*> redoQueue;
};

History::History()
{
    createImpl();

    putUndo(new BoardState);

    qDebug() << Q_FUNC_INFO;
    qDebug() << "impl.undoQueue.size()" <<impl().undoQueue.size();
    qDebug() << "impl().redoQueue.size()" << impl().redoQueue.size();
}

History::~History()
{

}

bool History::undoIsEmpty() const noexcept
{
    return impl().undoQueue.empty();
}

bool History::redoIsEmpty() const noexcept
{
    return impl().redoQueue.empty();
}

BoardState* History::popUndo(BoardState* currentState) noexcept
{
    if (impl().undoQueue.empty())
    {
        return nullptr;
    }

    if (impl().undoQueue.size() == 1)
    {
        return impl().undoQueue.back();
    }

    putRedo(currentState);
    impl().undoQueue.pop_back();

    return new BoardState { impl().undoQueue.back()->restore() };
}

void History::putUndo(BoardState* state) noexcept
{
    if (impl().undoQueue.size() == Constants::MAX_QUEUE_SIZE)
    {
        impl().undoQueue.pop_front();
    }

    impl().undoQueue.push_back(state);
}

BoardState* History::popRedo(BoardState* currentState) noexcept
{
    if (impl().redoQueue.empty())
    {
        return nullptr;
    }

    auto state = impl().redoQueue.back();
    impl().redoQueue.pop_back();
    putUndo(state);

    return state;
}

void History::putRedo(BoardState* state) noexcept
{
    if (impl().redoQueue.size() == Constants::MAX_QUEUE_SIZE)
    {
        impl().redoQueue.pop_front();
    }

    impl().redoQueue.push_back(state);
}

void History::clear()
{
    impl().undoQueue.clear();
}
