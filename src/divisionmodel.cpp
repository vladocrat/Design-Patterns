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

void transfer(QVector<Division*>& to, const QVector<Division*> from)
{
    for (const auto& division : from)
    {
        to.push_back(division);
    }
}

} //! Internal

struct DivisionModel::impl_t
{
    QVector<Division*> displayList;
    QVector<Division*> all;
    QVector<Division*> temp;
    uint32_t currentDivision { 0 };

    ~impl_t()
    {
        for (auto division : qAsConst(displayList))
        {
            division->deleteLater();
        }

        for (auto division : qAsConst(temp))
        {
            division->deleteLater();
        }
    }
};

DivisionModel::DivisionModel()
{
    createImpl();

    QQmlEngine::setObjectOwnership(this, QQmlEngine::CppOwnership);

    auto salesDivison = new Division;
    salesDivison->setCode(1);
    salesDivison->setName("Sales");
    salesDivison->setJobs({new Job{"work", 2.0}});

    impl().displayList.push_back(salesDivison);

    auto subDiv = new Division;
    subDiv->setCode(3);
    subDiv->setName("new name");
    subDiv->setJobs({new Job{"cringe", -1}});

    auto marketingDivision = new Division;
    marketingDivision->setCode(2);
    marketingDivision->setName("Marketing");
    marketingDivision->setJobs({new Job{"marketing work", 59.23}, new Job{"more work", 59.23}});
    marketingDivision->setSubdivisions({subDiv});

    salesDivison->setSubdivisions({marketingDivision});

    impl().displayList.push_back(marketingDivision);
    impl().displayList.push_back(subDiv);

    impl().all = impl().displayList;
}

DivisionModel::~DivisionModel()
{

}

int DivisionModel::columnCount(const QModelIndex& parent = QModelIndex()) const
{
    Q_UNUSED(parent)
    return 4;
}

int DivisionModel::rowCount(const QModelIndex& parent = QModelIndex()) const
{
    Q_UNUSED(parent)
    return impl().displayList.size();
}

QVariant DivisionModel::data(const QModelIndex& index, int role) const
{
    qDebug() << Q_FUNC_INFO;

    if (index.row() < 0 || index.row() >= impl().displayList.count())
    {
        return {};
    }

    const auto getAllData = [this](const QModelIndex& index) -> QVariant const {
        const auto division = impl().displayList.at(index.row());

        if (!division)
        {
            return {};
        }

        switch(Internal::intToRole(index.column()))
        {
        case DivisionModel::Roles::Code:
            return { division->code() };
        case DivisionModel::Roles::Name:
            return { division->name() };
        case DivisionModel::Roles::JobName:
        {
            QStringList ret;

            for (const auto job : division->jobs())
            {
                ret << job->name() << " ";
            }

            return ret.join("\n");
        }
        case DivisionModel::Roles::JobPayment:
        {
            double ret { 0.0 };

            for (const auto job : division->jobs())
            {
                ret += job->payment();
            }

            return ret;
        }
        }

        Q_UNREACHABLE();
    };

    switch (role)
    {
    case Qt::DisplayRole:
        return getAllData(index);
    }

    Q_UNREACHABLE();
}

QHash<int, QByteArray> DivisionModel::roleNames() const
{
    return { {Qt::DisplayRole, "display"} };
}

QVariant DivisionModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch (Internal::intToRole(section))
    {
    case Roles::Code:
        return "Code";
    case Roles::Name:
        return "Name";
    case Roles::JobName:
        return "Job Name";
    case Roles::JobPayment:
        return "Payment";
    }

    Q_UNREACHABLE();
}

void DivisionModel::addDivision(Division* division)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    impl().displayList.append(division);
    endInsertRows();

    impl().all.push_back(division);
}

void DivisionModel::displayDivision(const uint32_t code)
{
    qDebug() << Q_FUNC_INFO;

    if (impl().currentDivision == code)
    {
        return;
    }

    impl().currentDivision = code;
    getCurrentDivision();
}

void removeSubDivs(Division* div, QVector<Division*>& all)
{
    std::for_each(div->subdivisions().begin(), div->subdivisions().end(), [&] (Division* division) {
        removeSubDivs(division, all);

        auto it = div->subdivisions().begin();

        while (it != div->subdivisions().end()) {
            auto iter = std::find_if(all.begin(), all.end(), [&] (Division* allDiv) {
                return (*it)->code() == allDiv->code();
            });

            if (iter != all.end()) {
                all.erase(iter);
            }

            (*it)->deleteLater();
            ++it;
        }
    });

    div->clearSubDivs();
}

void DivisionModel::removeDivision(const uint32_t code)
{
    auto it = std::find_if(impl().all.begin(), impl().all.end(), [code](Division* d) {
        return d->code() == code;
    }); //! Find required divison

    if (it == impl().all.end())
    {
        return;
    }

    beginResetModel();
    removeSubDivs((*it), impl().all); //! Remove all subdivisions for it

    impl().all.erase(it); //! Remove root item from list
    (*it)->deleteLater(); //! Delete the item

    impl().displayList = impl().all;
    endResetModel();
}

void DivisionModel::registerType()
{
    qmlRegisterUncreatableType<DivisionModel>("DivisionModel", 1, 0, "DivisionModel", "Can't create model");
}

void DivisionModel::getCurrentDivision()
{
    if (impl().currentDivision > static_cast<uint32_t>(impl().all.size()))
    {
        return;
    }

    if (impl().currentDivision == 0)
    {
        beginResetModel();
        impl().displayList = impl().all;
        endResetModel();

        return;
    }

    auto it = std::find_if(impl().displayList.begin(), impl().displayList.end(), [=](Division* current) {
        return current->code() == impl().currentDivision;
    });

    if (!it)
    {
        return;
    }

    auto division = *it;
    impl().temp = impl().displayList;
    impl().displayList.clear();

    for (const auto div : division->subdivisions())
    {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        impl().displayList.append(div);
        endInsertRows();
    }
}
