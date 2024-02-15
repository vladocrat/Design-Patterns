#pragma once

#include <QObject>

#include "pimpl.h"

class Saver final : public QObject
{
    Q_OBJECT
public:
    Saver();
    ~Saver() override;

    void setData(QString fileName, QByteArray data);
    QString taskName() const;

public slots:
    void save() noexcept;

signals:
    void error(QString error);
    void saved(QString fileName);

private:
    DECLARE_PIMPL
};

