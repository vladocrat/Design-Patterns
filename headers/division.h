#pragma once

#include <QString>
#include <QVector>
#include <QObject>

#include "pimpl.h"

class Job;

class Division final : public QObject
{
    Q_OBJECT
public:
    Division();
    ~Division();

    [[nodiscard]] uint32_t code() const;
    [[nodiscard]] QString name() const;
    [[nodiscard]] const QVector<Job*>& jobs() const;

private:
    DECLARE_PIMPL
};

