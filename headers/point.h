#pragma once

#include <QObject>

#include "pimpl.h"

class Point : public QObject
{
    Q_OBJECT
public:
    Point();
    ~Point();

private:
    DECLARE_PIMPL
};
