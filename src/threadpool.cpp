#include "threadpool.h"

#include <QMutexLocker>
#include <QDebug>
#include <QVector>
#include <QMutex>

ThreadPool* ThreadPool::instance() noexcept
{
    static ThreadPool pl;
    return &pl;
}

ThreadPool::~ThreadPool()
{
    stop();
    for (const auto& thread : qAsConst(m_pool))
    {
        thread->quit();
        thread->wait();
    }
}

void ThreadPool::initialize(size_t poolSize) noexcept
{
    m_pool.resize(static_cast<int>(poolSize));

    for (int i = 0; i < poolSize; i++)
    {
        m_pool[i] = new QThread();

        QObject::connect(m_pool[i], &QThread::started, this, [this]()
        {
            while (m_isRunning && !m_workQueue.isEmpty())
            {
                QMutexLocker locker(&m_poolLock);

                auto task = m_workQueue.dequeue();
                task->run();

                //m_waitCondition.wait(&m_poolLock);
            }
        });

        m_pool[i]->start();
    }
}

void ThreadPool::start()
{
    QMutexLocker locker(&m_poolLock);

    m_isRunning = true;
    m_waitCondition.wakeAll();
}

void ThreadPool::stop()
{
    QMutexLocker locker(&m_poolLock);
    m_isRunning = false;
}

void ThreadPool::enqueue(QRunnable* task)
{
    QMutexLocker locker(&m_poolLock);

    m_workQueue.enqueue(task);
    m_waitCondition.wakeOne();
}

