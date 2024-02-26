#pragma once

#include <deque>

#include "pimpl.h"
#include "movable.h"

class BoardState
{
public:
    BoardState();
    BoardState(const std::deque<Movable*>&);
    ~BoardState();

    [[nodiscard]] bool isEmpty() const noexcept;
    [[nodiscard]] std::deque<Movable*> restore() noexcept;

private:
    DECLARE_PIMPL
};

