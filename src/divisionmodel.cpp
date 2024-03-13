#include "divisionmodel.h"

#include <QQmlEngine>

#include "division.h"
#include "job.h"

namespace Internal
{

DivisionModel::Roles intToRole(int role)
{
    return static_cast<DivisionModel::Roles>(role);
}

int roleToInt(DivisionModel::Roles role)
{
    return static_cast<int>(role);
}

} //! Internal

struct DivisionModel::impl_t
{
    QVector<Division*> list;

    ~impl_t()
    {
        for (int i = 0; i < list.size(); i++)
        {
            if (list[i])
                delete list[i];
        }
    }
};

DivisionModel::DivisionModel()
{
    createImpl();

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);
}

DivisionModel::~DivisionModel()
{

}

int DivisionModel::columnCount(const QModelIndex& parent = QModelIndex()) const
{
    Q_UNUSED(parent)
    auto metaEnumCount = QMetaEnum::fromType<Roles>().keyCount();
    return metaEnumCount;
}

int DivisionModel::rowCount(const QModelIndex& parent = QModelIndex()) const
{
    Q_UNUSED(parent)
    return impl().list.size();
}

QVariant DivisionModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid())
    {
        return {};
    }

    if (index.row() < 0 || index.row() >= impl().list.count())
    {
        return {};
    }

    const auto& division = impl().list.at(index.row());
    const auto& jobs = division->jobs();

    switch (Internal::intToRole(role))
    {
    case DivisionModel::Roles::Code:
        return division->code();
    case DivisionModel::Roles::Name:
        return division->name();
    case DivisionModel::Roles::JobName:
        return 1;//jobs[index.row()]->name();
    case DivisionModel::Roles::JobPayment:
        return 2; //jobs[index.row()]->payment();
    default:
        Q_UNREACHABLE();
    }

    Q_UNREACHABLE();
}

QHash<int, QByteArray> DivisionModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Internal::roleToInt(DivisionModel::Roles::Code)] = "code";
    roles[Internal::roleToInt(DivisionModel::Roles::Name)] = "name";
    roles[Internal::roleToInt(DivisionModel::Roles::JobName)] = "jobName";
    roles[Internal::roleToInt(DivisionModel::Roles::JobPayment)] = "jobPayment";

    return roles;
}

void DivisionModel::addDivision(Division* division)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    impl().list.append(division);
    endInsertRows();
}

void DivisionModel::registerType()
{
    qmlRegisterUncreatableType<DivisionModel>("DivisionModel", 1, 0, "DivisionModel", "Can't create model");
}
