#pragma once

#include "movable.h"

class FigureFactory
{
public:
    [[nodiscard]] static Movable* create(FigureType::Value) noexcept;

private:
    FigureFactory() = default;
    ~FigureFactory() = default;
    Q_DISABLE_COPY_MOVE(FigureFactory);
};

