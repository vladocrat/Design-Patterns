#include "job.h"

#include <QString>

struct Job::impl_t
{
    QString name;
    double payment { 0.0 };
};

Job::Job()
{
    createImpl();
}

Job::Job(const QString& name, const double& payment)
{
    createImpl();

    impl().name = name;
    impl().payment = payment;
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

double Job::payment() const
{
    return impl().payment;
}
