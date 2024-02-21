#include "figuretype.h"

#include <QQmlEngine>

void FigureType::registerType()
{
    qmlRegisterUncreatableType<FigureType>("FigureType", 1, 0, "FigureType", "ENUM_WRAPPER");
}
