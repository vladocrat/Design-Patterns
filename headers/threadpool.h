#pragma once

#include <QThread>
#include <QObject>
#include <QFuture>
#include <QQueue>
#include <QWaitCondition>

#include "downloadworker.h"

class ThreadPool final : public QObject
{
    Q_OBJECT
public:
    friend class DownloadWorker;

    static ThreadPool* instance() noexcept;

    void initialize(size_t poolSize) noexcept;

    void start();
    void stop();
    void enqueue(QRunnable* task);

private:
    ThreadPool() = default;
    ~ThreadPool() = default;
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    bool m_isRunning;
    QWaitCondition m_waitCondition;
    QMutex m_poolLock;
    QVector<QThread*> m_pool;
    QQueue<QRunnable*> m_workQueue;
};

