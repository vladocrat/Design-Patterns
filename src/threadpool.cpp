#include "threadpool.h"

#include <QMutexLocker>
#include <QDebug>
#include <QVector>
#include <QMutex>
#include <QQueue>
#include <QWaitCondition>
#include <QThread>

struct ThreadPool::impl_t
{
    bool m_isRunning;
    QWaitCondition m_waitCondition;
    QMutex m_poolLock;
    QVector<QThread*> m_pool;
    QQueue<QRunnable*> m_workQueue;
};

ThreadPool* ThreadPool::instance() noexcept
{
    static ThreadPool pl;
    return &pl;
}

ThreadPool::ThreadPool()
{
    createImpl();
}

ThreadPool::~ThreadPool()
{
    stop();

    for (const auto& thread : qAsConst(impl().m_pool))
    {
        thread->quit();
        thread->wait();
    }
}

void ThreadPool::initialize(size_t poolSize) noexcept
{
    impl().m_pool.resize(static_cast<int>(poolSize));

    for (int i = 0; i < poolSize; i++)
    {
        impl().m_pool[i] = new QThread();

        QObject::connect(impl().m_pool[i], &QThread::started, this, [this]()
        {
            while (impl().m_isRunning && !impl().m_workQueue.isEmpty())
            {
                QMutexLocker locker(&impl().m_poolLock);

                auto task = impl().m_workQueue.dequeue();
                task->run();

                //m_waitCondition.wait(&m_poolLock);
            }
        });

        impl().m_pool[i]->start();
    }
}

void ThreadPool::start() noexcept
{
    QMutexLocker locker(&impl().m_poolLock);

    impl().m_isRunning = true;
    impl().m_waitCondition.wakeAll();
}

void ThreadPool::stop() noexcept
{
    QMutexLocker locker(&impl().m_poolLock);

    impl().m_isRunning = false;
}

void ThreadPool::enqueue(QRunnable* task) noexcept
{
    QMutexLocker locker(&impl().m_poolLock);

    impl().m_workQueue.enqueue(task);
    impl().m_waitCondition.wakeOne();
}
