#pragma once

#include <QAbstractListModel>

#include "pimpl.h"

class Division;

class DivisionModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    enum class Roles : int
    {
        Code = Qt::UserRole + 1,
        Name,
        JobName,
        JobPayment
    };
    Q_ENUM(Roles)

    DivisionModel();
    ~DivisionModel();

    int columnCount(const QModelIndex& parent) const override;
    int rowCount(const QModelIndex& parent) const override;
    QVariant data(const QModelIndex& index, int role) const override;
    QHash<int, QByteArray> roleNames() const override;

    void addDivision(Division* division);

    static void registerType();

private:
    DECLARE_PIMPL
    Q_DISABLE_COPY(DivisionModel)
};

