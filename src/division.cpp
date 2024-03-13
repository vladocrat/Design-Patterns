#include "division.h"

#include "job.h"

struct Division::impl_t
{
    uint32_t code { 0 };
    QString name;
    QVector<Job*> jobs;
};

Division::Division()
{
    createImpl();

    for (int i = 0; i < 10; i++)
        impl().jobs.push_back(new Job{});
}

Division::~Division()
{

}

uint32_t Division::code() const
{
    return impl().code;
}

QString Division::name() const
{
    return impl().name;
}

const QVector<Job*>& Division::jobs() const
{
    assert(!impl().jobs.isEmpty());
    return impl().jobs;
}

