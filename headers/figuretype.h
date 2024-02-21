#pragma once

#include <QObject>

class FigureType : public QObject
{
    Q_GADGET
public:
    enum class Value
    {
        Circle,
        Triangle,
        Rectangle,
        None
    };
    Q_ENUM(Value)

    static void registerType();
};
