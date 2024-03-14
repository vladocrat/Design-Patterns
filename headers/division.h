#pragma once

#include <QString>
#include <QVector>
#include <QObject>

#include "pimpl.h"

class Job;

class Division : public QObject
{
    Q_OBJECT
public:
    Division();
    ~Division();

    void setCode(uint32_t code);
    void setName(const QString& name);
    void setJobs(const QVector<Job*>& jobs);

    [[nodiscard]] uint32_t code() const;
    [[nodiscard]] QString name() const;
    [[nodiscard]] const QVector<Job*>& jobs() const;

private:
    DECLARE_PIMPL
};

