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
        Code = 0,
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
    Q_INVOKABLE QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void addDivision(Division* division);
    void displayDivision(const uint32_t code);
    void removeDivision(const uint32_t code);

    static void registerType();

private:
    void getCurrentDivision();

    DECLARE_PIMPL
    Q_DISABLE_COPY(DivisionModel)
};

