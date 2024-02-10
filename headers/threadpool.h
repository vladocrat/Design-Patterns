#pragma once

#include <QObject>
#include <QRunnable>

#include "pimpl.h"

class ThreadPool final : public QObject
{
    Q_OBJECT
public:
    static ThreadPool* instance() noexcept;

    void initialize(size_t poolSize) noexcept;

    void start() noexcept;
    void stop() noexcept;
    void enqueue(QRunnable* task) noexcept;

private:
    ThreadPool();
    ~ThreadPool();
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool(ThreadPool&&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    ThreadPool& operator=(ThreadPool&&) = delete;

    DECLARE_PIMPL
};

