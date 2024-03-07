#pragma once

#include "pimpl.h"

class BoardState;

class History
{
public:
    History();
    ~History();

    [[nodiscard]] bool undoIsEmpty() const noexcept;
    [[nodiscard]] bool redoIsEmpty() const noexcept;

    [[nodiscard]] BoardState* popUndo(BoardState* currentState) noexcept;
    void putUndo(BoardState* state) noexcept;

    [[nodiscard]] BoardState* popRedo(BoardState* currentState) noexcept;
    void putRedo(BoardState* state) noexcept;

    void clear();

private:
    DECLARE_PIMPL
};
