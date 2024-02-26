#pragma once

#include "pimpl.h"

class BoardState;

class History
{
public:
    History();
    ~History();

    [[nodiscard]] bool isEmpty() const noexcept;
    [[nodiscard]] BoardState* pop() noexcept;
    void put(BoardState* state) noexcept;
    void clear();

private:
    DECLARE_PIMPL
};
