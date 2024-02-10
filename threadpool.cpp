#include "threadpool.h"

#include <QMutexLocker>
#include <QDebug>
#include <QVector>
#include <QMutex>

struct ThreadPool::impl_t
{
    QMutex poolLock;
    QVector<std::shared_ptr<QThread>> pool;
};

ThreadPool* ThreadPool::instance() noexcept
{
    static ThreadPool pl;
    return &pl;
}

void ThreadPool::initialize(size_t poolSize) noexcept
{
    impl().pool.resize(static_cast<int>(poolSize));

    for (int i = 0; i < poolSize; i++)
    {
        impl().pool[i] = std::make_shared<QThread>();
    }
}

ThreadPool::ThreadPool()
{
    createImpl();
}

std::shared_ptr<QThread> ThreadPool::get() noexcept
{
    QMutexLocker locker(&impl().poolLock);

    if (impl().pool.isEmpty())
    {
        return nullptr;
    }

    auto resource = impl().pool.last();

    QObject::connect(resource.get(), &QThread::finished, this, [this, resource](){
        qDebug() << "thread finished, releasing...";
        release(resource);
    });

    impl().pool.removeLast();
    return resource;
}

void ThreadPool::release(const std::shared_ptr<QThread>& thread) noexcept
{
    impl().pool.append(thread);
    emit threadFreed();
}


