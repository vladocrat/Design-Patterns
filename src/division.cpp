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
}

Division::~Division()
{

}

void Division::setCode(uint32_t code)
{
    impl().code = code;
}

void Division::setName(const QString& name)
{
    impl().name = name;
}

void Division::setJobs(const QVector<Job*>& jobs)
{
    impl().jobs = jobs;
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

