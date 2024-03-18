#pragma once

#include <QObject>

#include "pimpl.h"

class DivisionModel;

class DivisionController final : public QObject
{
    Q_OBJECT
public:
    static DivisionController* instance();

    static void registerType();

    Q_INVOKABLE DivisionModel* model();
    Q_INVOKABLE void add();
    Q_INVOKABLE void getDivision(const QString& divisionCode);
    Q_INVOKABLE void removeDivision(const QString& divisionCode);

private:
    DivisionController();
    ~DivisionController();
    Q_DISABLE_COPY_MOVE(DivisionController);

    DECLARE_PIMPL
};

