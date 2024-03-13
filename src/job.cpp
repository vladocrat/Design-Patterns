#include "job.h"

#include <QString>

struct Job::impl_t
{
    QString name;
    uint32_t payment { 0 };
};

Job::Job()
{
    createImpl();
}

Job::~Job()
{

}

QString Job::toQString() const
{
    return QString{ impl().name }
        .append(" ")
        .append(QString::number(impl().payment));
}

QString Job::name() const
{
    return impl().name;
}

uint32_t Job::payment() const
{
    return impl().payment;
}
