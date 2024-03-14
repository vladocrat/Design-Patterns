#pragma once

#include <QObject>

#include "pimpl.h"

class Job : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged FINAL)
    Q_PROPERTY(double payment READ payment NOTIFY paymentChanged FINAL)
public:
    Job();
    Job(const QString& name, const double& payment);
    ~Job();

    [[nodiscard]] QString toQString() const;
    [[nodiscard]] QString name() const;
    [[nodiscard]] double payment() const;

signals:
    void nameChanged();
    void paymentChanged();

private:
    DECLARE_PIMPL
};

