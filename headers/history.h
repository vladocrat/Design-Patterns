#pragma once

#include "pimpl.h"

class History
{
public:
    History();
    ~History();

    void pop();
    void put();
    void clear();

private:
    DECLARE_PIMPL
};
