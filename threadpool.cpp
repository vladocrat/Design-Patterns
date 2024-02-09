#include "threadpool.h"

#include <QMutexLocker>

namespace Constants
{
constexpr static const int POOL_SIZE = 5; //! TODO other way?
} //! Constants

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

std::shared_ptr<QThread> ThreadPool::get() noexcept
{
    QMutexLocker locker(&impl().poolLock);

    if (impl().pool.isEmpty())
    {
        return nullptr;
    }

    auto resource = impl().pool.last();
    impl().pool.removeLast();
    return resource;
}

void ThreadPool::release(std::shared_ptr<QThread>& thread) noexcept
{
    impl().pool.append(thread);
}

ThreadPool::ThreadPool()
{
    createImpl();
}

