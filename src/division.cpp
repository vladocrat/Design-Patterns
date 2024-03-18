#include "division.h"

#include "job.h"

struct Division::impl_t
{
    uint32_t code { 0 };
    QString name;
    QVector<Job*> jobs;
    QVector<Division*> subdivisions;
};

Division::Division()
{
    createImpl();
}

Division::~Division()
{
    for (auto division : qAsConst(impl().subdivisions))
    {
        division->deleteLater();
    }
    impl().subdivisions.clear();

    for (auto job : qAsConst(impl().jobs))
    {
        job->deleteLater();
    }
    impl().jobs.clear();
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

void Division::setSubdivisions(QVector<Division*> subdivisions)
{
    impl().subdivisions = subdivisions;
}

void Division::clearSubDivs()
{
    impl().jobs.clear();
    impl().subdivisions.clear();
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
    return impl().jobs;
}

const QVector<Division*>& Division::subdivisions() const
{
    return impl().subdivisions;
}

