#pragma once

#include <QObject>

#include "pimpl.h"

class Job : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name NOTIFY nameChanged FINAL)
    Q_PROPERTY(uint32_t payment READ payment NOTIFY paymentChanged FINAL)
public:
    Job();
    ~Job();

    [[nodiscard]] QString toQString() const;
    [[nodiscard]] QString name() const;
    [[nodiscard]] uint32_t payment() const;

signals:
    void nameChanged();
    void paymentChanged();

private:
    DECLARE_PIMPL
};

