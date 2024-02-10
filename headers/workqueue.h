#pragma once

#include <QMutex>
#include <QMutexLocker>

#include <queue>

template <typename T>
class WorkQueue
{
public:
    void enqueue(const T& t) noexcept
    {
        QMutexLocker locker(&m_lock);
        m_queue.push(t);
    }

    bool dequeue(T& t)
    {
        QMutexLocker locker(&m_lock);

        if (m_queue.empty())
        {
            return false;
        }

        t = std::move(m_queue.front());

        m_queue.pop();
        return true;
    }

    bool isEmpty() const noexcept
    {
        return m_queue.empty();
    }

private:
    std::queue<T> m_queue;
    QMutex m_lock;
};
