#include "history.h"

#include <deque>

#include "boardstate.h"

namespace Constants
{
constexpr static const size_t MAX_QUEUE_SIZE { 5 };
} //! Constants

struct History::impl_t
{
    std::deque<BoardState*> queue;
};

History::History()
{
    createImpl();

    impl().queue.push_back(new BoardState);
}

History::~History()
{

}

bool History::isEmpty() const noexcept
{
    return impl().queue.empty();
}

BoardState* History::pop() noexcept
{
    if (impl().queue.empty())
    {
        return nullptr;
    }

    impl().queue.pop_back();

    if (impl().queue.empty())
    {
        impl().queue.push_back(new BoardState);
    }

    return impl().queue.back();
}

void History::put(BoardState* state) noexcept
{
    if (state->isEmpty())
    {
        return;
    }

    if (impl().queue.size() > Constants::MAX_QUEUE_SIZE)
    {
        impl().queue.pop_front();
    }

    impl().queue.push_back(state);
}

void History::clear()
{
    impl().queue.clear();
}
