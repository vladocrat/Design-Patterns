#include "boardstate.h"

#include "movable.h"

struct BoardState::impl_t
{
    std::deque<Movable*> objs;
};

BoardState::BoardState()
{
    createImpl();
}

BoardState::BoardState(const std::deque<Movable*>& states)
{
    createImpl();

    impl().objs = states;
}

BoardState::~BoardState()
{

}

bool BoardState::isEmpty() const noexcept
{
    return impl().objs.empty();
}

std::deque<Movable*> BoardState::restore() noexcept
{
    return impl().objs;
}
